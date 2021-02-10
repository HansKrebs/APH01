/*
 * compass.c
 *
 *  Created on: 02.02.2021
 *      Author: Hans
 */


#include "compass.h"
#include "position_motion_sensor.h"
#include "stdio.h"


#include "stm32f4xx_nucleo.h"
#include "lis2dw12.h"








#include "motion_ec.h"
#include "motion_ac.h"
#include "motion_mc.h"
#include "motion_gc.h"
#include "motion_fx.h"



#define VERSION_STR_LENG 35
#define SAMPLE_FREQ 10

/*** Initialization ***/
static char lib_version_ec[VERSION_STR_LENG];
static char lib_version_ac[VERSION_STR_LENG];
static char lib_version_fx[VERSION_STR_LENG];
static char lib_version_gc[VERSION_STR_LENG];
static char lib_version_mc[VERSION_STR_LENG];




void compass_init(void)
{
	float_t freq = SAMPLE_FREQ;

	/* E-Compass API initialization function */
	MotionEC_Initialize(&freq);
	MotionGC_Initialize(&freq);
	MotionAC_Initialize(1);

	MotionMC_Initialize(100,1);
	MotionFX_initialize();
	/* Optional: Get version */
	MotionEC_GetLibVersion(lib_version_ec);
	MotionAC_GetLibVersion(lib_version_ac);
	MotionGC_GetLibVersion(lib_version_gc);
	MotionMC_GetLibVersion(lib_version_mc);
	MotionFX_GetLibVersion(lib_version_fx);

	printf("\n\r%s",lib_version_ec);
	printf("\n\r%s",lib_version_ac);
	printf("\n\r%s",lib_version_gc);
	printf("\n\r%s",lib_version_mc);
	printf("\n\r%s",lib_version_fx);

}

static void setEcParameter(POS_MOTION_SENSOR_Axes_t *acc, POS_MOTION_SENSOR_Axes_t *mag, MEC_input_t *in, float timeS)
{
	in->acc[0] = (float)((float)acc->x) / 1000;
	in->acc[1] = (float)acc->y / 1000;
	in->acc[2] = (float)acc->z / 1000;

	in->mag[0] = (float)mag->x / 50;
	in->mag[1] = (float)mag->y / 50;
	in->mag[2] = (float)mag->z / 50;

	in->deltatime_s = timeS;
}

void GetCompassData()
{
	MEC_input_t in;
	MEC_output_t out;

	POS_MOTION_SENSOR_Axes_t AccAxesLsm6dso = {0,0,0};
	POS_MOTION_SENSOR_Axes_t GyrAxesLsm6dso = {0,0,0};
	POS_MOTION_SENSOR_Axes_t MagAxes = {0,0,0};

	POS_MOTION_SENSOR_GetAxes(MAG_LIS2MDL, &MagAxes);
	POS_MOTION_SENSOR_GetAxes(ACC_LSM6DSO, &AccAxesLsm6dso);
	POS_MOTION_SENSOR_GetAxes(GYR_LSM6DSO, &GyrAxesLsm6dso);
//
//	printf("\n\rACC x = %5d y = %5d z = %5d MAG x = %5d y = %5d z = %5d",(int)AccAxesLis2dw.x,(int)AccAxesLis2dw.y,(int)AccAxesLis2dw.z,(int)MagAxes.x,(int)MagAxes.y,(int)MagAxes.z);
	printf("\n\rACC x = %5d y = %5d z = %5d GYR x = %5d y = %5d z = %5d MAG x = %5d y = %5d z = %5d\n\r",(int)AccAxesLsm6dso.x,(int)AccAxesLsm6dso.y,(int)AccAxesLsm6dso.z,(int)GyrAxesLsm6dso.x,(int)GyrAxesLsm6dso.y,(int)GyrAxesLsm6dso.z,(int)MagAxes.x,(int)MagAxes.y,(int)MagAxes.z);

	setEcParameter(&AccAxesLsm6dso, &MagAxes, &in, 0.1);
	MotionEC_Run(&in, &out);

	printf("\n\rQ %2.2f %2.2f %2.2f %2.2f",out.quaternion[0],out.quaternion[1],out.quaternion[2],out.quaternion[3]);

	//LIS2DW12_ACC_GetAxes();

}

///////////////////////////

char MotionAC_LoadCalFromNVM (unsigned short intdataSize, unsigned int *data)
{
	return 0;

}
char MotionAC_SaveCalInNVM (unsigned short intdataSize, unsigned int *data)
{
	return 0;
}

char MotionMC_LoadCalFromNVM (unsigned short intdataSize, unsigned int *data)
{
	return 0;

}
char MotionMC_SaveCalInNVM (unsigned short intdataSize, unsigned int *data)
{
	return 0;
}


