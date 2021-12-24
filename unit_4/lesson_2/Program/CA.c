/*
 * CA.c
 *
 *  Created on: Dec 23, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include "CA.h"
//Varibles
int CA_speed=0, CA_distance=0, CA_threshold=50;


// STATE Pointer to function
void (*CA_state)();

STATE_define(CA_Waiting)
{
	//state_Name
	CA_state_id=CA_Waiting;

	//State_Action
	CA_speed=0;
	DC_motor_Set(CA_speed);
	//Event_Check
	Cprint("CA_Waiting ------> CA_Speed = %d ",CA_speed);
}

STATE_define(CA_Driving)
{
	//state_Name
		CA_state_id=CA_Driving;
		CA_speed=30;
		//State_Action
		DC_motor_Set(CA_speed);

		//Event_Check
		Cprint("CA_Driving ------> CA_Speed = %d ",CA_speed);

}

/* This function is used here because the CA file is
 * the intermediate file between the US and DC and
 * because the US function has an output function
 * then the input function will be in the CA
 * This function determines the condition of the motor based on the value of the distance sensor
 */
void US_Set_distance(int d)
{
	CA_distance=d;
	(CA_distance<= CA_threshold)?  (CA_state= STATE(CA_Waiting)):(CA_state= STATE(CA_Driving));
	Cprint("US -----------> CA Distance = %d \n",CA_distance);


}
