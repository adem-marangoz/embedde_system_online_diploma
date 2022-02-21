/*
 * Timer_management_driver.c
 *
 *  Created on: Jan 1, 2022
 *      Author: MAHMMAD_ALNAJJAR
 */

#include "Timer_management_alarm.h"

volatile static unsigned int counter1=0;


void (*Timer_p_fun)()=Timer_define(Timer_Alarm_Off);

Timer_define_f(Timer_Alarm_Off)
{
	//Cprint("\nTimer_management_alarm:---> Timer is Off ---");
	Alarm_on_off_fun(false);
}


Timer_define_f(Timer_Alarm_On)
{
	counter1++;
	if(counter1==50003)
	{
		counter1=0;
		Timer_p_fun=Timer_define(Timer_Alarm_Off);
		Timer_p_fun();
		//Cprint("\nTimer_management_alarm:---> Ending 60s for Timer ");
	}
}


void Timer_starting()
{
	//Cprint("Timer_management_alarm:---> Timer is On ---->\n");
	Timer_p_fun=Timer_define(Timer_Alarm_On);
	Alarm_on_off_fun(true);
	counter1=0;
}
