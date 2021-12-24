/*
 * CA.c
 *
 *  Created on: Dec 23, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include "DC.h"
//Varibles
int DC_speed=0;


// STATE Pointer to function
void (*DC_state)();


void DC_init()
{
	Cprint("-------- DC init -------- \n");
}


void DC_motor_Set(int s)
{
	DC_speed=s;
	DC_state=STATE(DC_busy);
	Cprint("CA -----------speed = %d ---------->DC \n",DC_speed);
}

/**
 * In this function, the motor speed is sent to the
 * DC_motor_Set function based on the value set from the US_Set_distance function.
 */
STATE_define(DC_busy)
{
	//state_Name
	DC_state_id=DC_busy;

	//State_Action
	DC_state=DC_idle;
	//Event_Check
	Cprint("Busy_State -------> DC_motor Speed = %d \n",DC_speed);
}

/**
 * In this function, the motor speed is sent to the
 * DC_motor_Set function based on the value set from the US_Set_distance function.
 */
STATE_define(DC_idle)
{
	//state_Name
	DC_state_id=DC_idle;

	//State_Action
	//Event_Check
	Cprint("Idle_State -------> DC_motor Speed = %d \n",DC_speed);

}







