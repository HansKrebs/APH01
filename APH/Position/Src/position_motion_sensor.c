/*
 * position_motion_sensor.c
 *
 *  Created on: 03.02.2021
 *      Author: Hans
 */

/* Includes ------------------------------------------------------------------*/
#include "position_motion_sensor.h"
#include "position_conf.h"
#include "lis2dw12.h"
#include "lis2mdl.h"
#include "lsm6dso.h"

/** @defgroup POS_MOTION_SENSOR_Private_Function_Prototypes IKS01A3 MOTION SENSOR Private Function Prototypes
 * @{
 */
static int32_t LIS2DW12_0_Probe(POS_MOTION_SENSORS sensor);
static int32_t LIS2MDL_0_Probe(POS_MOTION_SENSORS sensor);
static int32_t LSM6DSO_0_Probe(POS_MOTION_SENSORS sensor);

/**
 * @}
 */
/** @defgroup POS_MOTION_SENSOR_Exported_Variables IKS01A3 MOTION SENSOR Exported Variables
 * @{
 */
extern void
*PosMotionCompObj[POS_MOTION_SENSORS_MAX]; /* This "redundant" line is here to fulfil MISRA C-2012 rule 8.4 */
void *PosMotionCompObj[POS_MOTION_SENSORS_MAX];



/** @defgroup POS_MOTION_SENSOR_Private_Variables IKS01A3 MOTION SENSOR Private Variables
 * @{
 */

/* We define a jump table in order to get the correct index from the desired function. */
/* This table should have a size equal to the maximum value of a function plus 1.      */
static MOTION_SENSOR_FuncDrv_t *PosMotionFuncDrv[POS_MOTION_SENSORS_MAX];
static MOTION_SENSOR_CommonDrv_t *PosMotionDrv[POS_MOTION_SENSORS_MAX];

/**
 * @}
 */

/**
 * @brief  Initializes the motion sensors
 * @retval BSP status
 */
#include "position.h"
int32_t POS_MOTION_SENSOR_Init(void)
{
  int32_t ret = BSP_ERROR_NONE;

  ret = LIS2DW12_0_Probe(ACC_LIS2DW12);
  if (BSP_ERROR_NONE == ret)
  {
	  ret = LIS2MDL_0_Probe(MAG_LIS2MDL);
  }

  if (BSP_ERROR_NONE == ret)
  {
	  ret = LSM6DSO_0_Probe(GYR_LSM6DSO);
  }
  return ret;
}

/**
 * @brief  Deinitialize Motion sensor
 * @param  Instance Motion sensor instance
 * @retval BSP status
 */
int32_t POS_MOTION_SENSOR_DeInit(POS_MOTION_SENSORS sensor)
{
  int32_t ret;

  if (sensor >= POS_MOTION_SENSORS_MAX)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (PosMotionDrv[sensor]->DeInit(PosMotionCompObj[sensor]) != BSP_ERROR_NONE)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
 * @brief  Get WHOAMI value
 * @param  sensor Motion sensor instance
 * @param  Id WHOAMI value
 * @retval BSP status
 */
int32_t POS_MOTION_SENSOR_ReadID(POS_MOTION_SENSORS sensor, uint8_t *Id)
{
  int32_t ret;

  if (sensor >= POS_MOTION_SENSORS_MAX)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (PosMotionDrv[sensor]->ReadID(PosMotionCompObj[sensor], Id) != BSP_ERROR_NONE)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
 * @brief  Enable Motion sensor
 * @param  Sensor Motion sensor instance
 * @retval BSP status
 */
int32_t POS_MOTION_SENSOR_Enable(POS_MOTION_SENSORS sensor)
{
  int32_t ret;

  if (sensor >= POS_MOTION_SENSORS_MAX)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (PosMotionFuncDrv[sensor]->Enable(PosMotionCompObj[sensor]) != BSP_ERROR_NONE)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
 * @brief  Disable Motion sensor
 * @param  Sensor Motion sensor instance
 * @retval BSP status
 */
int32_t POS_MOTION_SENSOR_Disable(POS_MOTION_SENSORS sensor)
{
  int32_t ret;
  if (sensor >= POS_MOTION_SENSORS_MAX)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (PosMotionFuncDrv[sensor]->Disable(PosMotionCompObj[sensor]) != BSP_ERROR_NONE)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
 * @brief  Get motion sensor axes data
 * @param  Sensor Motion sensor instance
 * @param  Axes pointer to axes data structure
 * @retval BSP status
 */
int32_t POS_MOTION_SENSOR_GetAxes(POS_MOTION_SENSORS sensor, POS_MOTION_SENSOR_Axes_t *Axes)
{
  int32_t ret;

  if (sensor >= POS_MOTION_SENSORS_MAX)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    if (PosMotionFuncDrv[sensor]->GetAxes(PosMotionCompObj[sensor], Axes) != BSP_ERROR_NONE)
    {
      ret = BSP_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = BSP_ERROR_NONE;
    }
  }

  return ret;
}

/**
 * @brief  Get motion sensor axes raw data
 * @param  Sensor Motion sensor instance
 * @param  Axes pointer to axes raw data structure
 * @retval BSP status
 */
int32_t POS_MOTION_SENSOR_GetAxesRaw(POS_MOTION_SENSORS sensor, POS_MOTION_SENSOR_AxesRaw_t *Axes)
{
  int32_t ret;

  if (sensor >= POS_MOTION_SENSORS_MAX)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    if (PosMotionFuncDrv[sensor]->GetAxesRaw(PosMotionCompObj[sensor], Axes) != BSP_ERROR_NONE)
    {
      ret = BSP_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = BSP_ERROR_NONE;
    }
  }
  return ret;
}

/**
 * @brief  Get motion sensor sensitivity
 * @param  Sensor Motion sensor instance
 * @param  Sensitivity pointer to sensitivity read value
 * @retval BSP status
 */
int32_t POS_MOTION_SENSOR_GetSensitivity(POS_MOTION_SENSORS sensor, float *Sensitivity)
{
  int32_t ret;

  if (sensor >= POS_MOTION_SENSORS_MAX)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    if (PosMotionFuncDrv[sensor]->GetSensitivity(PosMotionCompObj[sensor], Sensitivity) != BSP_ERROR_NONE)
    {
      ret = BSP_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = BSP_ERROR_NONE;
    }
  }

  return ret;
}


/**
 * @brief  Get motion sensor Output Data Rate
 * @param  Sensor Motion sensor instance
 * @param  Odr pointer to Output Data Rate read value
 * @retval BSP status
 */
int32_t POS_MOTION_SENSOR_GetOutputDataRate(POS_MOTION_SENSORS sensor, float *Odr)
{
  int32_t ret;

  if (sensor >= POS_MOTION_SENSORS_MAX)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    if (PosMotionFuncDrv[sensor]->GetOutputDataRate(PosMotionCompObj[sensor], Odr) != BSP_ERROR_NONE)
    {
      ret = BSP_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = BSP_ERROR_NONE;
    }
  }

  return ret;
}

/**
 * @brief  Get motion sensor Full Scale
 * @param  Sensor Motion sensor instance
 * @param  Fullscale pointer to Fullscale read value
 * @retval BSP status
 */
int32_t POS_MOTION_SENSOR_GetFullScale(POS_MOTION_SENSORS sensor, int32_t *Fullscale)
{
  int32_t ret;

  if (sensor >= POS_MOTION_SENSORS_MAX)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    if (PosMotionFuncDrv[sensor]->GetFullScale(PosMotionCompObj[sensor], Fullscale) != BSP_ERROR_NONE)
    {
      ret = BSP_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = BSP_ERROR_NONE;
    }
  }

  return ret;
}

/**
 * @brief  Set motion sensor Output Data Rate
 * @param  Sensor Motion sensor instance
 * @param  Odr Output Data Rate value to be set
 * @retval BSP status
 */
int32_t POS_MOTION_SENSOR_SetOutputDataRate(POS_MOTION_SENSORS sensor, float Odr)
{
  int32_t ret;

  if (sensor >= POS_MOTION_SENSORS_MAX)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    if (PosMotionFuncDrv[sensor]->SetOutputDataRate(PosMotionCompObj[sensor], Odr) != BSP_ERROR_NONE)
    {
      ret = BSP_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = BSP_ERROR_NONE;
    }
  }

  return ret;
}

/**
 * @brief  Set motion sensor Full Scale
 * @param  Sensor Motion sensor instance
 * @param  Fullscale Fullscale value to be set
 * @retval BSP status
 */
int32_t POS_MOTION_SENSOR_SetFullScale(POS_MOTION_SENSORS sensor, int32_t Fullscale)
{
	  int32_t ret;

	  if (sensor >= POS_MOTION_SENSORS_MAX)
	  {
	    ret = BSP_ERROR_WRONG_PARAM;
	  }
	  else
	  {
	    if (PosMotionFuncDrv[sensor]->SetFullScale(PosMotionCompObj[sensor], Fullscale) != BSP_ERROR_NONE)
	    {
	      ret = BSP_ERROR_COMPONENT_FAILURE;
	    }
	    else
	    {
	      ret = BSP_ERROR_NONE;
	    }
	  }

	  return ret;
}

/**
 * @}
 */

/** @defgroup POS_MOTION_SENSOR_Private_Functions IKS01A3 MOTION SENSOR Private Functions
 * @{
 */
/**
 * @brief  Register Bus IOs for instance 0 if component ID is OK
 * @retval BSP status
 */
static int32_t LSM6DSO_0_Probe(POS_MOTION_SENSORS sensor)
{
  LSM6DSO_IO_t            io_ctx;
  uint8_t                 id;
  static LSM6DSO_Object_t lsm6dso_obj_0;
  int32_t ret = BSP_ERROR_NONE;

  /* Configure the accelero driver */
  io_ctx.BusType     = LSM6DSO_I2C_BUS; /* I2C */
  io_ctx.Address     = LSM6DSO_I2C_ADD_H;
  io_ctx.Init        = POS_I2C_Init;
  io_ctx.DeInit      = POS_I2C_DeInit;
  io_ctx.ReadReg     = POS_I2C_ReadReg;
  io_ctx.WriteReg    = POS_I2C_WriteReg;
  io_ctx.GetTick     = POS_GetTick;

  if (LSM6DSO_RegisterBusIO(&lsm6dso_obj_0, &io_ctx) != LSM6DSO_OK)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else if (LSM6DSO_ReadID(&lsm6dso_obj_0, &id) != LSM6DSO_OK)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else if (id != LSM6DSO_ID)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
	PosMotionCompObj[ACC_LSM6DSO] = &lsm6dso_obj_0;
	PosMotionCompObj[GYR_LSM6DSO] = &lsm6dso_obj_0;
	/* The second cast (void *) is added to bypass Misra R11.3 rule */
	PosMotionDrv[ACC_LSM6DSO] = (MOTION_SENSOR_CommonDrv_t *)(void *)&LSM6DSO_COMMON_Driver;
	PosMotionDrv[GYR_LSM6DSO] = (MOTION_SENSOR_CommonDrv_t *)(void *)&LSM6DSO_COMMON_Driver;

	/* The second cast (void *) is added to bypass Misra R11.3 rule */
	PosMotionFuncDrv[ACC_LSM6DSO] = (MOTION_SENSOR_FuncDrv_t *)(void *)&LSM6DSO_ACC_Driver;
	PosMotionFuncDrv[GYR_LSM6DSO] = (MOTION_SENSOR_FuncDrv_t *)(void *)&LSM6DSO_GYRO_Driver;

	if (PosMotionDrv[ACC_LSM6DSO]->Init(PosMotionCompObj[ACC_LSM6DSO]) != LSM6DSO_OK)
	{
		ret = BSP_ERROR_COMPONENT_FAILURE;
	}
	else if (PosMotionDrv[GYR_LSM6DSO]->Init(PosMotionCompObj[GYR_LSM6DSO]) != LSM6DSO_OK)
	{
		ret = BSP_ERROR_COMPONENT_FAILURE;
	}
	else
	{
		ret = BSP_ERROR_NONE;
		if (PosMotionFuncDrv[ACC_LSM6DSO]->Enable(PosMotionCompObj[ACC_LSM6DSO]) != LSM6DSO_OK)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
		else if (PosMotionFuncDrv[GYR_LSM6DSO]->Enable(PosMotionCompObj[GYR_LSM6DSO]) != LSM6DSO_OK)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
	}
  }
	  return ret;
}

/**
 * @brief  Register Bus IOs for instance 1 if component ID is OK
 * @retval BSP status
 */
static int32_t LIS2DW12_0_Probe(POS_MOTION_SENSORS sensor)
{
  LIS2DW12_IO_t            io_ctx;
  uint8_t                  id;
  static LIS2DW12_Object_t lis2dw12_obj_0;
  int32_t ret = BSP_ERROR_NONE;

  /* Configure the accelero driver */
  io_ctx.BusType     = LIS2DW12_I2C_BUS; /* I2C */
  io_ctx.Address     = LIS2DW12_I2C_ADD_H;
  io_ctx.Init        = POS_I2C_Init;
  io_ctx.DeInit      = POS_I2C_DeInit;
  io_ctx.ReadReg     = POS_I2C_ReadReg;
  io_ctx.WriteReg    = POS_I2C_WriteReg;
  io_ctx.GetTick     = POS_GetTick;

  if (LIS2DW12_RegisterBusIO(&lis2dw12_obj_0, &io_ctx) != LIS2DW12_OK)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else if (LIS2DW12_ReadID(&lis2dw12_obj_0, &id) != LIS2DW12_OK)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else if (id != LIS2DW12_ID)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    PosMotionCompObj[ACC_LIS2DW12] = &lis2dw12_obj_0;
    /* The second cast (void *) is added to bypass Misra R11.3 rule */
    PosMotionDrv[ACC_LIS2DW12] = (MOTION_SENSOR_CommonDrv_t *)(void *)&LIS2DW12_COMMON_Driver;

	/* The second cast (void *) is added to bypass Misra R11.3 rule */
	PosMotionFuncDrv[ACC_LIS2DW12] = (MOTION_SENSOR_FuncDrv_t *)(void *)&LIS2DW12_ACC_Driver;

	if (PosMotionDrv[ACC_LIS2DW12]->Init(PosMotionCompObj[ACC_LIS2DW12]) != LIS2DW12_OK)
	{
		ret = BSP_ERROR_COMPONENT_FAILURE;
	}
	else
	{
		ret = BSP_ERROR_NONE;
		if (PosMotionFuncDrv[ACC_LIS2DW12]->Enable(PosMotionCompObj[ACC_LIS2DW12]) != LSM6DSO_OK)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
	}
  }
  return ret;
}


/**
 * @brief  Register Bus IOs for instance 1 if component ID is OK
 * @retval BSP status
 */
static int32_t LIS2MDL_0_Probe(POS_MOTION_SENSORS sensor)
{

  LIS2MDL_IO_t            io_ctx;
  uint8_t                 id;
  static LIS2MDL_Object_t lis2mdl_obj_0;
  int32_t                 ret = BSP_ERROR_NONE;

  /* Configure the magneto driver */
  io_ctx.BusType     = LIS2MDL_I2C_BUS; /* I2C */
  io_ctx.Address     = LIS2MDL_I2C_ADD;
  io_ctx.Init        = POS_I2C_Init;
  io_ctx.DeInit      = POS_I2C_DeInit;
  io_ctx.ReadReg     = POS_I2C_ReadReg;
  io_ctx.WriteReg    = POS_I2C_WriteReg;
  io_ctx.GetTick     = POS_GetTick;

  if (LIS2MDL_RegisterBusIO(&lis2mdl_obj_0, &io_ctx) != LIS2MDL_OK)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else if (LIS2MDL_ReadID(&lis2mdl_obj_0, &id) != LIS2MDL_OK)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else if (id != LIS2MDL_ID)
  {
    ret = BSP_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {

    PosMotionCompObj[MAG_LIS2MDL] = &lis2mdl_obj_0;
    /* The second cast (void *) is added to bypass Misra R11.3 rule */
    PosMotionDrv[MAG_LIS2MDL] = (MOTION_SENSOR_CommonDrv_t *)(void *)&LIS2MDL_COMMON_Driver;
    /* The second cast (void *) is added to bypass Misra R11.3 rule */
    PosMotionFuncDrv[MAG_LIS2MDL] = (MOTION_SENSOR_FuncDrv_t *)(void *)&LIS2MDL_MAG_Driver;

    if (PosMotionDrv[MAG_LIS2MDL]->Init(PosMotionCompObj[MAG_LIS2MDL]) != LIS2MDL_OK)
    {
      ret = BSP_ERROR_COMPONENT_FAILURE;
    }
	else
	{
		ret = BSP_ERROR_NONE;
		if (PosMotionFuncDrv[MAG_LIS2MDL]->Enable(PosMotionCompObj[MAG_LIS2MDL]) != LSM6DSO_OK)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}
	}
  }
  return ret;
}

