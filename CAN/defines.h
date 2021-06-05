#ifndef DEFINES_H
#define DEFINES_H

#include "stm32f4xx.h"
#include "stm32f4xx_can.h"
#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>


#define label_master 0x001
#define label_slave 0x100

/*****************Define Pin**********************
 * if re-define, you must config more GPIO_PinSource
 * and check the AF your new pin in each library
 *************************************************/
#define CAN_Rx_Pin GPIO_Pin_11 //PA11
#define CAN_Tx_Pin GPIO_Pin_12 //PA12

/*******************CAN Struct*******************

*************************************************/
typedef union{
	float mf[2];	
	double md;
	uint8_t mb[8];
} mCANdata;			

typedef enum{
	sts_new_data,
	sts_data_lost,
	sts_no_flag
} mDatastatus;

typedef struct{
	mDatastatus mCANsts;
	uint16_t FrameLable_Rx;
	mCANdata CanData_Rx;
  uint16_t FrameLable_Tx;
  mCANdata CanData_Tx;
} mCANbuffer;

/*******************UART Struct*******************

*************************************************/
typedef struct _uart_buffer_{
	 uint16_t counter;
	 bool flag;
	 bool error;
	 char mbuff_rx[100];
	 char mbuff_tx[100];
} mUARTbuffer;
	
/*******************Define Checksum*******************

*************************************************/
typedef struct{
	char Rx;
	char Tx;
} mChecksum;

/*********************Convert Data*******************

*****************************************************/
typedef union {
	float f;
	unsigned char bytes[sizeof(float)];
} mFloat;

typedef union {
    double d;
    unsigned char bytes[sizeof(double)];
} mDouble;

/*********************Define Struct*******************

*****************************************************/
extern CanTxMsg CAN1_TxMessage;
extern CanRxMsg CAN1_RxMessage;
extern mCANbuffer can1_buffer;

extern mUARTbuffer uart_buffer_u1;
extern mUARTbuffer uart_buffer_u3;
extern mUARTbuffer uart_buffer_u6;

extern mChecksum  Checksum;

#endif







