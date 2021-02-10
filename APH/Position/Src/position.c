/*
 * position.c
 *
 *  Created on: 03.02.2021
 *      Author: Hans
 */

#include "stm32f4xx_nucleo.h"
#include "lis2dw12.h"
#include "stdio.h"
#include "position_motion_sensor.h"
#include "compass.h"

static LIS2DW12_Object_t accObj;
static LIS2DW12_Capabilities_t	accCap;


static void motionSensor_Init(void);



void position_Init(void)
{
	motionSensor_Init();
	compass_init();






	/////
//	POS_MOTION_SENSOR_Axes_t AccAxesLsm6dso;
//	POS_MOTION_SENSOR_GetAxes(ACC_LSM6DSO, &AccAxesLsm6dso);
}

void PositionProcess(void)
{
	GetCompassData();
//	POS_MOTION_SENSOR_Axes_t AccAxesLis2dw={0,0,0};
//	POS_MOTION_SENSOR_Axes_t AccAxesLsm6dso={0,0,0};
//	POS_MOTION_SENSOR_Axes_t GyrAxesLsm6dso={0,0,0};
//	POS_MOTION_SENSOR_Axes_t MagAxes={0,0,0};
//	POS_MOTION_SENSOR_GetAxes(ACC_LIS2DW12, &AccAxesLis2dw);
//	POS_MOTION_SENSOR_GetAxes(MAG_LIS2MDL, &MagAxes);
//	POS_MOTION_SENSOR_GetAxes(ACC_LSM6DSO, &AccAxesLsm6dso);
//	POS_MOTION_SENSOR_GetAxes(GYR_LSM6DSO, &GyrAxesLsm6dso);
//
//	printf("\n\rACC x = %5d y = %5d z = %5d MAG x = %5d y = %5d z = %5d",(int)AccAxesLis2dw.x,(int)AccAxesLis2dw.y,(int)AccAxesLis2dw.z,(int)MagAxes.x,(int)MagAxes.y,(int)MagAxes.z);
//	printf("\n\rACC x = %5d y = %5d z = %5d GYR x = %5d y = %5d z = %5d\n\r",(int)AccAxesLsm6dso.x,(int)AccAxesLsm6dso.y,(int)AccAxesLsm6dso.z,(int)GyrAxesLsm6dso.x,(int)GyrAxesLsm6dso.y,(int)GyrAxesLsm6dso.z);
}

/**
  * @brief  Initialize the accelerometer and  magnetometer
  * @retval None
  */
static void motionSensor_Init(void)
{
//  displayFloatToInt_t out_value_odr;
//  int i;

	  /* Initialize Virtual COM Port */
	  BSP_COM_Init(COM1);


	POS_MOTION_SENSOR_Init();

#if (USE_IKS01A3_MOTION_SENSOR_LIS2DW12_0 == 1)
    case IKS01A3_LIS2DW12_0:
      if (LIS2DW12_0_Probe(Functions) != BSP_ERROR_NONE)
      {
        return BSP_ERROR_NO_INIT;
      }
      if (MotionDrv[Instance]->GetCapabilities(MotionCompObj[Instance], (void *)&cap) != BSP_ERROR_NONE)
      {
        return BSP_ERROR_UNKNOWN_COMPONENT;
      }
      if (cap.Acc == 1U)
      {
        component_functions |= MOTION_ACCELERO;
      }
      if (cap.Gyro == 1U)
      {
        component_functions |= MOTION_GYRO;
      }
      if (cap.Magneto == 1U)
      {
        component_functions |= MOTION_MAGNETO;
      }
      break;
#endif


//	LIS2DW12_Init(&accObj);
	LIS2DW12_GetCapabilities(&accObj, &accCap);

/*
  IKS01A3_MOTION_SENSOR_Init(IKS01A3_LIS2DW12_0, MOTION_ACCELERO);

  IKS01A3_MOTION_SENSOR_Init(IKS01A3_LIS2MDL_0, MOTION_MAGNETO);

  for(i = 0; i < IKS01A3_MOTION_INSTANCES_NBR; i++)
  {
    IKS01A3_MOTION_SENSOR_GetCapabilities(i, &MotionCapabilities[i]);
    snprintf(dataOut, MAX_BUF_SIZE,
             "\r\nMotion Sensor Instance %d capabilities: \r\n ACCELEROMETER: %d\r\n GYROSCOPE: %d\r\n MAGNETOMETER: %d\r\n LOW POWER: %d\r\n",
             i, MotionCapabilities[i].Acc, MotionCapabilities[i].Gyro, MotionCapabilities[i].Magneto, MotionCapabilities[i].LowPower);
    printf("%s", dataOut);
    floatToInt(MotionCapabilities[i].AccMaxOdr, &out_value_odr, 3);
    snprintf(dataOut, MAX_BUF_SIZE, " MAX ACC ODR: %d.%03d Hz, MAX ACC FS: %d\r\n", (int)out_value_odr.out_int,
             (int)out_value_odr.out_dec, (int)MotionCapabilities[i].AccMaxFS);
    printf("%s", dataOut);
    floatToInt(MotionCapabilities[i].GyroMaxOdr, &out_value_odr, 3);
    snprintf(dataOut, MAX_BUF_SIZE, " MAX GYRO ODR: %d.%03d Hz, MAX GYRO FS: %d\r\n", (int)out_value_odr.out_int,
             (int)out_value_odr.out_dec, (int)MotionCapabilities[i].GyroMaxFS);
    printf("%s", dataOut);
    floatToInt(MotionCapabilities[i].MagMaxOdr, &out_value_odr, 3);
    snprintf(dataOut, MAX_BUF_SIZE, " MAX MAG ODR: %d.%03d Hz, MAX MAG FS: %d\r\n", (int)out_value_odr.out_int,
             (int)out_value_odr.out_dec, (int)MotionCapabilities[i].MagMaxFS);
    printf("%s", dataOut);
  }

  IKS01A3_ENV_SENSOR_Init(IKS01A3_HTS221_0, ENV_TEMPERATURE | ENV_HUMIDITY);

  IKS01A3_ENV_SENSOR_Init(IKS01A3_LPS22HH_0, ENV_TEMPERATURE | ENV_PRESSURE);

  IKS01A3_ENV_SENSOR_Init(IKS01A3_STTS751_0, ENV_TEMPERATURE);

  for(i = 0; i < IKS01A3_ENV_INSTANCES_NBR; i++)
  {
    IKS01A3_ENV_SENSOR_GetCapabilities(i, &EnvCapabilities[i]);
    snprintf(dataOut, MAX_BUF_SIZE,
             "\r\nEnvironmental Sensor Instance %d capabilities: \r\n TEMPERATURE: %d\r\n PRESSURE: %d\r\n HUMIDITY: %d\r\n LOW POWER: %d\r\n",
             i, EnvCapabilities[i].Temperature, EnvCapabilities[i].Pressure, EnvCapabilities[i].Humidity, EnvCapabilities[i].LowPower);
    printf("%s", dataOut);
    floatToInt(EnvCapabilities[i].TempMaxOdr, &out_value_odr, 3);
    snprintf(dataOut, MAX_BUF_SIZE, " MAX TEMP ODR: %d.%03d Hz\r\n", (int)out_value_odr.out_int,
             (int)out_value_odr.out_dec);
    printf("%s", dataOut);
    floatToInt(EnvCapabilities[i].PressMaxOdr, &out_value_odr, 3);
    snprintf(dataOut, MAX_BUF_SIZE, " MAX PRESS ODR: %d.%03d Hz\r\n", (int)out_value_odr.out_int,
             (int)out_value_odr.out_dec);
    printf("%s", dataOut);
    floatToInt(EnvCapabilities[i].HumMaxOdr, &out_value_odr, 3);
    snprintf(dataOut, MAX_BUF_SIZE, " MAX HUM ODR: %d.%03d Hz\r\n", (int)out_value_odr.out_int, (int)out_value_odr.out_dec);
    printf("%s", dataOut);
  }
  */
}


#if (USE_IKS01A3_MOTION_SENSOR_LIS2DW12_0 == 1)
    case IKS01A3_LIS2DW12_0:
      if (LIS2DW12_0_Probe(Functions) != BSP_ERROR_NONE)
      {
        return BSP_ERROR_NO_INIT;
      }
      if (MotionDrv[Instance]->GetCapabilities(MotionCompObj[Instance], (void *)&cap) != BSP_ERROR_NONE)
      {
        return BSP_ERROR_UNKNOWN_COMPONENT;
      }
      if (cap.Acc == 1U)
      {
        component_functions |= MOTION_ACCELERO;
      }
      if (cap.Gyro == 1U)
      {
        component_functions |= MOTION_GYRO;
      }
      if (cap.Magneto == 1U)
      {
        component_functions |= MOTION_MAGNETO;
      }
      break;
#endif

#if (USE_IKS01A3_MOTION_SENSOR_LIS2MDL_0 == 1)
    case IKS01A3_LIS2MDL_0:
      if (LIS2MDL_0_Probe(Functions) != BSP_ERROR_NONE)
      {
        return BSP_ERROR_NO_INIT;
      }
      if (MotionDrv[Instance]->GetCapabilities(MotionCompObj[Instance], (void *)&cap) != BSP_ERROR_NONE)
      {
        return BSP_ERROR_UNKNOWN_COMPONENT;
      }
      if (cap.Acc == 1U)
      {
        component_functions |= MOTION_ACCELERO;
      }
      if (cap.Gyro == 1U)
      {
        component_functions |= MOTION_GYRO;
      }
      if (cap.Magneto == 1U)
      {
        component_functions |= MOTION_MAGNETO;
      }
      break;
#endif
