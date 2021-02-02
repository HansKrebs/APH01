/*
 * compass.c
 *
 *  Created on: 02.02.2021
 *      Author: Hans
 */


#include "compass.h"
#include "lis2dw12.h"


static uint32_t test = 0;

void initCompass(uint32_t cInit)
{
	test = cInit;
}

void SetCompassData()
{
	//LIS2DW12_ACC_GetAxes();

}

