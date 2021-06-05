/**
  ******************************************************************************
  * @file    
  * @author  Pham Ngoc Tran
  * @version V1.3.0
  * @date    30-May-2021
  * @brief   Header for main.c module
  ******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONTROL_H
#define __CONTROL_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Exported types ------------------------------------------------------------*/
typedef struct {
	char LED_Status;
	char Mode;
} board;

extern board B1;
extern board B2;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __CONTROL_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
