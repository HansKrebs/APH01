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

static uint32_t prAllow = 7;

static MMC_Output_t data_out;



void compass_init(void)
{
	float_t freq = SAMPLE_FREQ;

	MEC_state_t orientation = MEC_ENABLE;
	MEC_state_t virtGyro = MEC_DISABLE;
	MEC_state_t gravity = MEC_DISABLE;
	MEC_state_t linearAcc = MEC_ENABLE;


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

	MotionEC_SetOrientationEnable(orientation);
	MotionEC_SetVirtualGyroEnable(virtGyro);
	MotionEC_SetGravityEnable(gravity);
	MotionEC_SetLinearAccEnable(linearAcc);

	data_out.CalQuality = MMC_CALQSTATUSGOOD;

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


//	POS_MOTION_SENSOR_GetAxes(MAG_LIS2MDL, &MagAxes);


static void sensorCompensation(POS_MOTION_SENSORS no,POS_MOTION_SENSOR_Axes_t *ax)
{
	const POS_MOTION_SENSOR_Axes_t max[POS_MOTION_SENSORS_MAX] = {
	{992	,995	,1018},	//ACC_LSM6DSO = 0,
	{0	,0	,0},	//GYR_LSM6DSO,
	{0	,0	,0},	//MAG_LIS2MDL,
	{1008	,942	,1012}	//ACC_LIS2DW12,
	};
	const POS_MOTION_SENSOR_Axes_t min[POS_MOTION_SENSORS_MAX] = {
	{-1000	,-1013	,-992},	//ACC_LSM6DSO = 0,
	{0	,0	,0},	//GYR_LSM6DSO,
	{0	,0	,0},	//MAG_LIS2MDL,
	{-1005	,-1042	,-995}	//ACC_LIS2DW12,
	};
	POS_MOTION_SENSOR_Axes_t offset;

	offset.x = (max[no].x + min[no].x) / 2;
	offset.y = (max[no].y + min[no].y) / 2;
	offset.z = (max[no].z + min[no].z) / 2;
	ax->x -= offset.x;
	ax->y -= offset.y;
	ax->z -= offset.z;
}

static int32_t GetCalibratedMagAxses(POS_MOTION_SENSORS sensor, POS_MOTION_SENSOR_Axes_t *Axes, int timeMs)
{
	int32_t ret;
	MMC_Input_t data_in;
	float mag_cal_x, mag_cal_y, mag_cal_z;

	static int32_t test = 0;

	/* Get magnetic field X/Y/Z in [uT] */
	ret = POS_MOTION_SENSOR_GetAxes(sensor, Axes);

	//MEMS_Read_MagValue(&data_in.Mag[0], &data_in.Mag[1], &data_in.Mag[2]);
	data_in.Mag[0] = Axes->x;
	data_in.Mag[1] = Axes->y;
	data_in.Mag[2] = Axes->z;
	/* Get current sample time in [ms] */
	data_in.TimeStamp = timeMs;
	/* Magnetometer calibration algorithm update */
	MotionMC_Update(&data_in);
	/* Get the magnetometer calibration coefficients */
	MotionMC_GetCalParams(&data_out);
	/* Apply calibration coefficients */
	mag_cal_x = (int)((data_in.Mag[0] - data_out.HI_Bias[0]) * data_out.SF_Matrix[0][0]
	 + (data_in.Mag[1] - data_out.HI_Bias[1]) * data_out.SF_Matrix[0][1]
	 + (data_in.Mag[2] - data_out.HI_Bias[2]) * data_out.SF_Matrix[0][2]);
	mag_cal_y = (int)((data_in.Mag[0] - data_out.HI_Bias[0]) * data_out.SF_Matrix[1][0]
	 + (data_in.Mag[1] - data_out.HI_Bias[1]) * data_out.SF_Matrix[1][1]
	 + (data_in.Mag[2] - data_out.HI_Bias[2]) * data_out.SF_Matrix[1][2]);
	mag_cal_z = (int)((data_in.Mag[0] - data_out.HI_Bias[0]) * data_out.SF_Matrix[2][0]
	 + (data_in.Mag[1] - data_out.HI_Bias[1]) * data_out.SF_Matrix[2][1]
	 + (data_in.Mag[2] - data_out.HI_Bias[2]) * data_out.SF_Matrix[2][2]);

	if (MMC_CALQSTATUSUNKNOWN != data_out.CalQuality)
	{
		test++;
	}
}

void GetCompassData()
{
	MEC_input_t in;
	MEC_output_t out;

	char printOut[150];

	MEC_state_t orientation = MEC_ENABLE;
	MEC_state_t virtGyro = MEC_DISABLE;
	MEC_state_t gravity = MEC_DISABLE;
	MEC_state_t linearAcc = MEC_ENABLE;

	POS_MOTION_SENSOR_Axes_t AccAxesLsm6dso;
	POS_MOTION_SENSOR_Axes_t GyrAxesLsm6dso;
	POS_MOTION_SENSOR_Axes_t MagAxes;
	POS_MOTION_SENSOR_Axes_t AccAxesLis2dw12;

	GetCalibratedMagAxses(MAG_LIS2MDL, &MagAxes, 100);

//	POS_MOTION_SENSOR_GetAxes(MAG_LIS2MDL, &MagAxes);
	POS_MOTION_SENSOR_GetAxes(ACC_LSM6DSO, &AccAxesLsm6dso);
	POS_MOTION_SENSOR_GetAxes(GYR_LSM6DSO, &GyrAxesLsm6dso);
	POS_MOTION_SENSOR_GetAxes(ACC_LIS2DW12, &AccAxesLis2dw12);

	// LIS2DW12 like LSM6DSO
	int32_t h = AccAxesLis2dw12.x;
	AccAxesLis2dw12.x = -AccAxesLis2dw12.y;
	AccAxesLis2dw12.y = h;


	sensorCompensation(ACC_LSM6DSO, &AccAxesLsm6dso);
	sensorCompensation(ACC_LSM6DSO, &AccAxesLis2dw12);

	setEcParameter(&AccAxesLsm6dso, &MagAxes, &in, 0.1);
	MotionEC_Run(&in, &out);

	MotionEC_GetOrientationEnable(&orientation);
	MotionEC_GetVirtualGyroEnable(&virtGyro);
	MotionEC_GetGravityEnable(&gravity);
	MotionEC_GetLinearAccEnable(&linearAcc);

	printOut[0] = 0;
	size_t len = strlen(printOut);
	if(prAllow & 1)
	{
		sprintf(printOut + len,"euler %2.2f %2.2f %2.2f ",out.euler[0],out.euler[1],out.euler[2]);
	}
	if(prAllow & 2)
	{
		len = strlen(printOut);
		sprintf(printOut + len,"Q %2.2f %2.2f %2.2f %2.2f ",out.quaternion[0],out.quaternion[1],out.quaternion[2],out.quaternion[3]);
	}
	if(prAllow & 4)
	{
		len = strlen(printOut);
		sprintf(printOut + len,"linear %2.2f %2.2f %2.2f ",out.linear[0],out.linear[1],out.linear[2]);
	}
	printf("\n\r%s",printOut);

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


