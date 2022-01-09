/*
 * Alarm_driver.h
 *
 *  Created on: Jan 1, 2022
 *      Author: MAHMMAD_ALNAJJAR
 */

#ifndef ALARM_DRIVER_H_
#define ALARM_DRIVER_H_


#include "state.h"

enum E_Alarm_State
{
	Alarm_Off,
	Alarm_On
};

extern enum E_Alarm_State Prev_Alarm_state;
extern enum E_Alarm_State Curr_Alarm_state;

void Alarm_init();
Alarm_define_f(Alarm_Off);
Alarm_define_f(Alarm_On);

extern void (*Alarm_p_fun)();

#endif /* ALARM_DRIVER_H_ */
