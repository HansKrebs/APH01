/*
 * normalTask.c
 *
 *  Created on: 29.01.2021
 *      Author: Hans
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cmsis_os.h"
#include "dbg/hwDebug.h"
//#include "slowTask.h"
#include "stdio.h"
//#include "app_mems.h"
//#include "stm32f4xx_nucleo.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
static osEventFlagsId_t ntFlag = NULL;
static osEventFlagsId_t stFlag = NULL;


void initNormalTask(osEventFlagsId_t normTaskEventHandle, osEventFlagsId_t slowTaskEventHandle)
{
	ntFlag = normTaskEventHandle;
	stFlag = slowTaskEventHandle;
}


/* USER CODE BEGIN Header_StartNormalTask */
/**
  * @brief  Function implementing the normalTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartNormalTask */
void StartNormalTask(void *argument)
{
  /* USER CODE BEGIN 5 */

	uint32_t cnt;
	uint32_t blink;



    while ((ntFlag == NULL) || (stFlag == NULL))
	{
    	osDelay(1);
	}


  /* Infinite loop */
  for(;;)
  {
	  osEventFlagsWait (ntFlag,1, 0, 15);
	  osEventFlagsClear(ntFlag,1);
	  cnt++;
	  blink++;
	  Set_Output(OUT_TEST_3,blink & 1);
	  if(cnt >= 10)
	  {
		  cnt = 0;
		  osEventFlagsSet(stFlag,1);
	  }
  }
  /* USER CODE END 5 */
}


