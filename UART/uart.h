/**
  ******************************************************************************
  * @file    
  * @author  Pham Ngoc Tran
  * @version V1.3.0
  * @date    30-May-2021
  * @brief   Header for uart.c module
  ******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H
#define __UART_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported constants --------------------------------------------------------*/
extern const int BUFF_SIZE_TX;
extern const int BUFF_SIZE_RX;
extern const int BaudRate;
/* Exported variables ------------------------------------------------------------*/
extern char RXBuffer[];
extern char TXBuffer[];
/* Exported functions ------------------------------------------------------- */
void USART_DMA_Config(void);
void sendData(void);
#endif /* __UART_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
