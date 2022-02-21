/*
 * Pressure_sensor_drive.h
 *
 *  Created on: Jan 1, 2022
 *      Author: MAHMMAD_ALNAJJAR
 */

#ifndef PRESSURE_SENSOR_DRIVER_H_
#define PRESSURE_SENSOR_DRIVER_H_

#include "state.h"


enum
{
	Reading_and_sending,
	Waiting
}Pressure_state;

void init_Pressure();
Pressure_fun(Reading_and_sending);
Pressure_fun(Waiting);

extern void (*Pressure_P_fun)();

#endif /* PRESSURE_SENSOR_DRIVER_H_ */
