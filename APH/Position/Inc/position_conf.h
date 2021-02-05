/*
 * position_config.h
 *
 *  Created on: 03.02.2021
 *      Author: Hans
 */
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_bus.h"
#include "stm32f4xx_nucleo_errno.h"


#ifndef INC_POSITION_CONF_H_
#define INC_POSITION_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif

/* USER CODE BEGIN 1 */
/* USER CODE END 1 */

#define POS_I2C_Init BSP_I2C1_Init
#define POS_I2C_DeInit BSP_I2C1_DeInit
#define POS_I2C_ReadReg BSP_I2C1_ReadReg
#define POS_I2C_WriteReg BSP_I2C1_WriteReg
#define POS_GetTick BSP_GetTick

#ifdef __cplusplus
}
#endif


#endif /* INC_POSITION_CONF_H_ */
