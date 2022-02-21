/*
 * Timer_management_driver.h
 *
 *  Created on: Jan 1, 2022
 *      Author: MAHMMAD_ALNAJJAR
 */

#ifndef TIMER_MANAGEMENT_ALARM_H_
#define TIMER_MANAGEMENT_ALARM_H_

#include "state.h"


enum
{
	Timer_Alarm_Off,
	Timer_Alarm_on
}Timer_state;

Timer_define_f(Timer_Alarm_Off);
Timer_define_f(Timer_Alarm_On);

extern void (*Timer_p_fun)();


#endif /* TIMER_MANAGEMENT_ALARM_H_ */
