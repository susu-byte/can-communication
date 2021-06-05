/**
  ******************************************************************************
  * @file    
  * @author  Pham Ngoc Tran
  * @version V1.3.0
  * @date    30-May-2021
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "main.h"
#include "control.h"
#include "Can_Int.h"
#include "defines.h"

mChecksum		Checksum;
board 			B1;
board				B2;

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{

}
void EXTI0_IRQHandler(void){
	//viet o day
	EXTI->PR = EXTI_Line0;
}
void TIM3_IRQHandler(void){
		if (TIM_GetITStatus(TIM3, TIM_FLAG_Update) == SET){
			readLEDStatus();
			sendData();
		}	
		TIM_ClearITPendingBit (TIM3, TIM_FLAG_Update);
}
// 50ms send CAN data to Board2
void TIM4_IRQHandler(void){
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET){
		can1_buffer.FrameLable_Tx = label_master;
		can1_buffer.CanData_Tx.mb[0] = 'E';
		can1_buffer.CanData_Tx.mb[1] = 'S';
		can1_buffer.CanData_Tx.mb[2] = 'M';
		can1_buffer.CanData_Tx.mb[3] = B1.Mode;
		//checksum CAN_Tx
		for( int i = 0; i < 4; i++){
			Checksum.Tx += can1_buffer.CanData_Tx.mb[i];
		}
		can1_buffer.CanData_Tx.mb[4] = Checksum.Tx;
		can1_buffer.CanData_Tx.mb[5] = '$';
		mCANwrite(can1_buffer.FrameLable_Tx,&can1_buffer,6);
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
  }
}

void DMA1_Stream1_IRQHandler(void){ //nhan gia tri
		char checksum_Rx = 0;
		DMA_ClearITPendingBit(DMA1_Stream1, DMA_IT_TCIF1); //clear IT flag which is 1 when RXBuffer is full
		if(RXBuffer[0]=='E' && RXBuffer[1]=='S'){
			for (int k = 0; k<3; k++){
				checksum_Rx += RXBuffer[k];
			}
			if (checksum_Rx == RXBuffer[3]){
				//Cap nhat mode o day
			}	
		}
}




/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
