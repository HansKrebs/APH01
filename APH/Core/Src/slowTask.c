/*
 * slowTask.c
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
#include "app_mems.h"
//#include "stm32f4xx_nucleo.h"
#include "compass.h"
#include "position.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
static osEventFlagsId_t stFlag = NULL;


void initSlowTask(osEventFlagsId_t slowTaskEventHandle)
{
	stFlag = slowTaskEventHandle;
}

void StartSlowTask(void *argument)
{
  /* USER CODE BEGIN 5 */

	uint32_t cnt;
	uint32_t blink;
	//TaskHandle_t stHandle = xTaskGetHandle( "slowTask" );

	while (stFlag == NULL)
    {
	  osDelay(1);
	}

	initCompass(57); //TODO



  /* Infinite loop */
  for(;;)
  {
	  osEventFlagsWait (stFlag,1, 0, 150);
	  osEventFlagsClear(stFlag,1);
	  if(blink & 8)
	  {
		  BSP_LED_On(LED_GREEN);
	  }
	  else
	  {
		  BSP_LED_Off(LED_GREEN);
	  }
	  //Set_Output(OUT_TEST_4,blink & 1);
	  cnt++;
	  blink++;
	  Set_Output(OUT_TEST_4, 1);
	  PositionProcess();
	  Set_Output(OUT_TEST_4, 0);
	  if(cnt >= 10)
	  {
//		  Set_Output(OUT_TEST_4, 1);
////		  printf("\n\n\n\rHallo\n\n\r");
		  cnt= 0;
//		  SetCompassData();
//		  PositionProcess();
////		  MX_MEMS_Process();
//		  Set_Output(OUT_TEST_4, 0);
	  }




  }
  /* USER CODE END 5 */
}

