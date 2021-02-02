/*
 * fastTaskk.c
 *
 *  Created on: 29.01.2021
 *      Author: Hans
 */
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "dbg/hwDebug.h"
#include "fastTask.h"
#include "cmsis_os.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

static osEventFlagsId_t ntFlag = NULL;

void initFastTask(osEventFlagsId_t normTaskEventHandle)
{
	ntFlag = normTaskEventHandle;
}

/* USER CODE BEGIN Header_StartFastTask */
/**
* @brief Function implementing the fastTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartFastTask */
void StartFastTask(void *argument)
{
  /* USER CODE BEGIN StartFastTask */
  uint32_t cnt = 0;
  uint32_t loop = 0;
  uint32_t test = 0;

  while (ntFlag == NULL)
  {
	  osDelay(1);
  }
 /* Infinite loop */

  for(;;)
  {
  	Set_Output(OUT_TEST_1, 1);
  	for(loop = 0; loop < 2000; loop++)
  	{
  		test = test + 3;
  	}
  	if(test > 3000)
  		test = 0;
  	else
  		test = 7;
  	Set_Output(OUT_TEST_1, 0);

  	Set_Output(OUT_TEST_2, 1);
    osDelay(1);
  	Set_Output(OUT_TEST_2, 0);
    cnt++;
    if (cnt >= 10)
    {
    	cnt = 0;
    	osEventFlagsSet(ntFlag,1);
    }
  }
  /* USER CODE END StartFastTask */
}


