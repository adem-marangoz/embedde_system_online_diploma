/*
 * main.c
 *
 *  Created on: Jan 1, 2022
 *      Author: MAHMMAD_ALNAJJAR
 */


#include "Alarm_driver.h"
#include "main_algoritma.h"
#include "Pressure_sensor_driver.h"
#include "Timer_management_alarm.h"


void setup(void);


void setup(void)
{
	init_Pressure();
	Alarm_init();
}


int main()
{
	setup();
	volatile int x=50;
	while(x)
	{
		x--;
		Pressure_P_fun();
		Main_p_fun();
		Timer_p_fun();
		if(Prev_Alarm_state!=Curr_Alarm_state)
			Alarm_p_fun();

	}
	return 0;
}
