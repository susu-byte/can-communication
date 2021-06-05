/**
  ******************************************************************************
  * @file    
  * @author  Pham Ngoc Tran
  * @version V1.3.0
  * @date    30-May-2021
  * @brief   Header for timer.c module
  ******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMER_H
#define __TIMER_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void ITTimer_Config(void);
void DLTimer_Config(void);
void delay_ms(u32 milliSeconds);
void delay_us(u32 microSeconds);
#endif /* __TIMER_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
