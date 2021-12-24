/*
 * main.c
 *
 *  Created on: Dec 23, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */
#include "CA.h"
#include "US.h"
#include "DC.h"

void inti()
{
	// Inti all the drivers
	US_Init();
	DC_init();
	// Inti IRQ ....
	// Inti HAL US_Driver DC_Driver
	// Inti Blocks
	// Set States pointers for each Block
	DC_state=STATE(DC_idle);
	CA_state=STATE(CA_Waiting);
	US_state=STATE(US_busy);




}


int main()
{
	inti();
	while(1)
	{
		US_state();
		CA_state();
		DC_state();
	}
	return 0;
}
