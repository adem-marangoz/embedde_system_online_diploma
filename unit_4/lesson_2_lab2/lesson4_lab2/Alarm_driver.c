/*
 * Alarm_driver.c
 *
 *  Created on: Jan 1, 2022
 *      Author: MAHMMAD_ALNAJJAR
 */

#include "Alarm_driver.h"



enum E_Alarm_State Prev_Alarm_state;
enum E_Alarm_State Curr_Alarm_state;

void (*Alarm_p_fun)()=Alarm_define(Alarm_Off);


void Alarm_init()
{
	Prev_Alarm_state=Alarm_Off;
	Curr_Alarm_state=Alarm_Off;
	Alarm_p_fun=Alarm_define(Alarm_Off);
	Cprint("--- Alarm Init ----\n")
}


Alarm_define_f(Alarm_Off)
{
	Prev_Alarm_state=Alarm_Off;
	Curr_Alarm_state=Alarm_Off;
	Cprint("\nAlarm_driver:==== Led is Off ====\n");
}


Alarm_define_f(Alarm_On)
{
	Prev_Alarm_state=Alarm_On;
	Curr_Alarm_state=Alarm_On;
	Cprint("\nAlarm_driver:==== Led is On ====\n");
}


void Alarm_on_off_fun(bool alarm_state)
{
	Prev_Alarm_state=Alarm_Off;
	Curr_Alarm_state=Alarm_On;
	(alarm_state== false)?  (Alarm_p_fun= Alarm_define(Alarm_Off)):(Alarm_p_fun= Alarm_define(Alarm_On));

}
