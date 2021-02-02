/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : hwDebug.c
  * @brief          : Debug functions
  ******************************************************************************
  * @attention
  *
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "hwDebug.h"

typedef struct
{
	GPIO_TypeDef* PORT; uint16_t PIN;
}gpioPin;

gpioPin dpArray[OUT_TEST_MAX] =
{

		{ OUT_TEST_1_GPIO_Port, OUT_TEST_1_Pin },
		{ OUT_TEST_2_GPIO_Port, OUT_TEST_2_Pin },
		{ OUT_TEST_3_GPIO_Port, OUT_TEST_3_Pin },
		{ OUT_TEST_4_GPIO_Port, OUT_TEST_4_Pin }
};





void Set_Output(GPIO_DebugPins dp, GPIO_PinState st)
{
	HAL_GPIO_WritePin(dpArray[dp].PORT, dpArray[dp].PIN, st);
}

/************************ (C) COPYRIGHT H_Krebs ****************END OF FILE****/
