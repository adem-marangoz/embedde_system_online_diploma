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
	SET_BIT(APB2ENR, 2);
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x22222222;
	Prev_Alarm_state=Alarm_Off;
	Curr_Alarm_state=Alarm_Off;
	Alarm_p_fun=Alarm_define(Alarm_Off);
	//Cprint("--- Alarm Init ----\n")
}


Alarm_define_f(Alarm_Off)
{
	SET_BIT(GPIOA_ODR,13);
	Prev_Alarm_state=Alarm_Off;
	Curr_Alarm_state=Alarm_Off;
	//Cprint("\nAlarm_driver:==== Led is Off ====\n");
}


Alarm_define_f(Alarm_On)
{
	RESET_BIT(GPIOA_ODR,13);
	Prev_Alarm_state=Alarm_On;
	Curr_Alarm_state=Alarm_On;
	//Cprint("\nAlarm_driver:==== Led is On ====\n");
}


void Alarm_on_off_fun(bool alarm_state)
{
	Prev_Alarm_state=Alarm_Off;
	Curr_Alarm_state=Alarm_On;
	(alarm_state== false)?  (Alarm_p_fun= Alarm_define(Alarm_Off)):(Alarm_p_fun= Alarm_define(Alarm_On));

}
