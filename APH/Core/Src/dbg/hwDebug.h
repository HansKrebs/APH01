/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : hwDebug.h
  * @brief          : Header for hwDebug.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HWDEBUG_H
#define __HWDEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
/**
  * @brief  debug pinsn
  */
typedef enum
{
  OUT_TEST_1 = 0,
  OUT_TEST_2,
  OUT_TEST_3,
  OUT_TEST_4,
  OUT_TEST_MAX
}GPIO_DebugPins;
/**
  * @}
  */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Set_Output(GPIO_DebugPins dp, GPIO_PinState st);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __HWDEBUG_H */

/************************ (C) COPYRIGHT H_Krebs ****************END OF FILE****/
