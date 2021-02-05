/*
 * position_motion_sensor.h
 *
 *  Created on: 03.02.2021
 *      Author: Hans
 */

#ifndef INC_POSITION_MOTION_SENSOR_H_
#define INC_POSITION_MOTION_SENSOR_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "position_conf.h"
#include "motion_sensor.h"


typedef struct
{
  int32_t x;
  int32_t y;
  int32_t z;
} POS_MOTION_SENSOR_Axes_t;

typedef struct
{
  int16_t x;
  int16_t y;
  int16_t z;
} POS_MOTION_SENSOR_AxesRaw_t;

typedef enum
{
  ACC_LIS2DW12 = 0,
  MAG_LIS2MDL,
  POS_MOTION_SENSORS_MAX
} POS_MOTION_SENSORS;

/* Motion Sensor instance Info */
/*
typedef struct
{
  uint8_t  Acc;
  uint8_t  Gyro;
  uint8_t  Magneto;
  uint8_t  LowPower;
  uint32_t GyroMaxFS;
  uint32_t AccMaxFS;
  uint32_t MagMaxFS;
  float    GyroMaxOdr;
  float    AccMaxOdr;
  float    MagMaxOdr;
} POS_MOTION_SENSOR_Capabilities_t;

typedef struct
{
  uint32_t Functions;
} POS_MOTION_SENSOR_Ctx_t;
*/

/** @addtogroup POS_MOTION_SENSOR_Exported_Functions POS_MOTION_SENSOR Exported Functions
 * @{
 */

int32_t POS_MOTION_SENSOR_Init(void);
int32_t POS_MOTION_SENSOR_DeInit(POS_MOTION_SENSORS sensor);
int32_t POS_MOTION_SENSOR_ReadID(POS_MOTION_SENSORS sensor, uint8_t *Id);
int32_t POS_MOTION_SENSOR_Enable(POS_MOTION_SENSORS sensor);
int32_t POS_MOTION_SENSOR_Disable(POS_MOTION_SENSORS sensor);
int32_t POS_MOTION_SENSOR_GetAxes(POS_MOTION_SENSORS sensor, POS_MOTION_SENSOR_Axes_t *Axes);
int32_t POS_MOTION_SENSOR_GetAxesRaw(POS_MOTION_SENSORS sensor, POS_MOTION_SENSOR_AxesRaw_t *Axes);
int32_t POS_MOTION_SENSOR_GetSensitivity(POS_MOTION_SENSORS sensor, float *Sensitivity);
int32_t POS_MOTION_SENSOR_GetOutputDataRate(POS_MOTION_SENSORS sensor, float *Odr);
int32_t POS_MOTION_SENSOR_SetOutputDataRate(POS_MOTION_SENSORS sensor, float Odr);
int32_t POS_MOTION_SENSOR_GetFullScale(POS_MOTION_SENSORS sensor, int32_t *Fullscale);
int32_t POS_MOTION_SENSOR_SetFullScale(POS_MOTION_SENSORS sensor, int32_t Fullscale);

/**
 * @}
 */


#ifdef __cplusplus
}
#endif


#endif /* INC_POSITION_MOTION_SENSOR_H_ */
