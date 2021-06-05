/**
  ******************************************************************************
  * @file    
  * @author  Pham Ngoc Tran
  * @version V1.3.0
  * @date    30-May-2021
  * @brief   Header for led.c module
  ******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H
#define __LED_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported variables ------------------------------------------------------------*/
extern char LED_Status;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void LEDConfig(void);
char readLEDStatus(void);
#endif /* __LED_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
