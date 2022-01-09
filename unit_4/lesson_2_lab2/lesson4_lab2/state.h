/*
 * state.h
 *
 *  Created on: Jan 1, 2022
 *      Author: MAHMMAD_ALNAJJAR
 */

#ifndef STATE_H_
#define STATE_H_

#include <stdio.h>

#define Cprint(...)	{fflush(stdin);\
					fflush(stdout);\
					printf(__VA_ARGS__);\
					fflush(stdin);\
					fflush(stdout);\
					}

typedef enum
{
	false,
	true
}bool;

#define Pressure_fun(pressure_state)	void Pr_##pressure_state()
#define Pressure(pressure_state)		Pr_##pressure_state

#define Al_fun(Main_state)				void Algoritma_##Main_state()
#define Al_d(Main_state)				Algoritma_##Main_state

#define Timer_define_f(Timer_ST)		void Timer_##Timer_ST()
#define Timer_define(Timer_ST)			Timer_##Timer_ST

#define Alarm_define_f(Alarm)			void Al_##Alarm()
#define Alarm_define(Alarm)				Al_##Alarm

void Send_pressure_value(unsigned int p);
void Timer_starting();
void Alarm_on_off_fun(bool alarm_state);

#endif /* STATE_H_ */
