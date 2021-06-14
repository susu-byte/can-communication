#include "defines.h"
#include "Can_int2.h"

/**********************************Note**********************************************
 * https://www.ni.com/en-vn/innovations/white-papers/06/controller-area-network--can--overview.html#section--552354600
 * https://nguyenquanicd.blogspot.com/2017/06/cancontroller-area-networkbai-3-cac.html
 * https://www.youtube.com/watch?v=nyef9xoZjqc
 * https://community.st.com/s/question/0D50X00009XkhRbSAJ/stm32-can-acceptance-mask
 * The number of filters assigned to CAN1 and CAN2 is defined in the CAN_FMR register which by default is set to 14 which is the start of the CAN2 filters.
 * This can be set to 28 which would mean no filters to CAN2 and all 28 to CAN1 or if set to 0 all 28 filters are assigned to CAN2.
 * \CAN 1,2 cell init  //CAN bus clock is 42Mhz = APB1 = sys/4
 * \Bitrate = CAN_CLK/(CAN_Prescaler * (CAN_BS1 + CAN_BS2 + CAN_SJW))
 * 11bit \addressing mode filter (0x0000 - 0x07FF)
************************************************************************************/
CanTxMsg		CAN1_TxMessage;
CanRxMsg		CAN1_RxMessage;
mCANbuffer	can1_buffer;
/*****************************CAN Configuration******************************
 * \Baudrate:
 * \Filter mode:
 * \IDs address be accepts: 
 *      label_master
 *      label_slave 
*****************************************************************************/
void CAN1_Configure( void )
{ 
  CAN_InitTypeDef         CAN_InitStructure;
  CAN_FilterInitTypeDef   CAN_FilterInitStructure;	
  GPIO_InitTypeDef        GPIO_InitStructure;
	
  uint16_t NVIC_Priority_Number;
  
  // Enable GPIO clock
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1);

  // Configure CAN 1 RX and TX pins
  GPIO_InitStructure.GPIO_Pin = CAN_Rx_Pin | CAN_Tx_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  CAN_DeInit(CAN1);

  CAN_InitStructure.CAN_TTCM = DISABLE;	// time-triggered communication mode = DISABLED
  CAN_InitStructure.CAN_ABOM = DISABLE; // automatic bus-off management mode = DISABLED
  CAN_InitStructure.CAN_AWUM = DISABLE; // automatic wake-up mode = DISABLED
  CAN_InitStructure.CAN_NART = DISABLE; // non-automatic retransmission mode = ENABLE (To prevent endless spam)
  CAN_InitStructure.CAN_RFLM = DISABLE; // receive FIFO locked mode = DISABLED
  CAN_InitStructure.CAN_TXFP = DISABLE; // transmit FIFO priority = DISABLED
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
  CAN_InitStructure.CAN_BS1 = CAN_BS1_14tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_6tq;
  CAN_InitStructure.CAN_Prescaler=2;		// 1 Mbit/s
	/*
  CAN_InitStructure.CAN_Prescaler=4;		// 500 kbit/s
  CAN_InitStructure.CAN_Prescaler=5;		// 400 kbit/s
  CAN_InitStructure.CAN_Prescaler=8;		// 250 kbit/s
  CAN_InitStructure.CAN_Prescaler=10;		// 200 kbit/s
  CAN_InitStructure.CAN_Prescaler=16;		// 125 kbit/s
	*/
	
  CAN_Init(CAN1, &CAN_InitStructure);

  // CAN filter init
  CAN_FilterInitStructure.CAN_FilterNumber = 0;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;;
  CAN_FilterInitStructure.CAN_FilterScale =CAN_FilterScale_16bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = label_master<<5;
  CAN_FilterInitStructure.CAN_FilterIdLow = label_slave<<5; 
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);

  // Enable FIFO0 message pending Interrupt */
  CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE);
  CAN_ITConfig(CAN1, CAN_IT_FF0, ENABLE);  
  NVIC_Priority_Number = NVIC_EncodePriority(0,1,0);
  NVIC_SetPriority(CAN1_RX0_IRQn,NVIC_Priority_Number);
  NVIC_EnableIRQ(CAN1_RX0_IRQn); 		
}

void mCANwrite(int _IDstd,mCANbuffer* _data,uint8_t _length)
{
	uint32_t uwCounter = 0;
  uint8_t TransmitMailbox = 0;
	uint8_t i = 0;
	
	// transmit
  CAN1_TxMessage.StdId =  _IDstd;
  CAN1_TxMessage.RTR = CAN_RTR_DATA;
  CAN1_TxMessage.IDE = CAN_ID_STD;
	CAN1_TxMessage.DLC = _length;
	for(i=0; i< _length ; i++){
		CAN1_TxMessage.Data[i] = _data->CanData_Tx.mb[i];
	}
  TransmitMailbox = CAN_Transmit(CAN1, &CAN1_TxMessage);
  while((CAN_TransmitStatus(CAN1, TransmitMailbox)  !=  CANTXOK) && (uwCounter  !=  0xFFFF)){
    uwCounter++;
  }
  uwCounter = 0;
  while((CAN_MessagePending(CAN1, CAN_FIFO0) < 1) && (uwCounter  !=  0xFFFF)){
    uwCounter++;
  }
}




/******************************Example mode in CAN Config****************************************
  -----------------------------------Configure CAN filter to accept 4 messages-----------------------------------------		
  The Ids address CAN just have 11 bit ( 0x000 -> 0x7FF).
  The maximum iDs accept in mode IdList is 4!!!
  In this example, we choose four filters are created to receive SID 123, 124, 125 and 126
  The register Filter in stm have 2 register 32 bit, we scale 32 bit by 2 register 16bit
  So that, we have 4 register 16bit. Because the id address in CAN just have 11bit, so we must
  shift 5 bit to left
  
  CAN_FilterInitStructure.CAN_FilterNumber = 0;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_16bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x123 <<5
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x124 <<5
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x125 <<5
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x126 <<5
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
  
  ---------------------------------------Configure CAN filter to accept all messages------------------------
  CAN_FilterInitStructure.CAN_FilterNumber = 0;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;;
  CAN_FilterInitStructure.CAN_FilterScale =CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x000;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x00;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x000; 
  *----------------------------------------------------------------------------*/

