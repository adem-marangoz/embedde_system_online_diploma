/*
 * US.c
 *
 *  Created on: Dec 23, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include "US.h"
//Varibles
int US_distance=0;


// STATE Pointer to function
void (*US_state)();
int US_Get_distance_random(int l,int r, int count);


void US_Init()
{
	Cprint("-------- US init -------- \n");
}


STATE_define(US_busy)
{
	//state_Name
	US_state_id=US_busy;

	//Event_Check
	US_distance=US_Get_distance_random(45,55,1);/* Generate a random value */

	Cprint("US_busy ---------> distance = %d   \n",US_distance);

	US_Set_distance(US_distance); /* Send Distance value to CA*/
	US_state=STATE(US_busy);
}


int US_Get_distance_random(int l,int r, int count)
{
	int i;
	for(i=0;i<count;i++)
	{
		int rand_num=(rand()%(r-l+1))+l;
		return rand_num;
	}
	return 0;
}
