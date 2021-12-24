/*
 * CA.h
 *
 *  Created on: Dec 23, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#ifndef DC_H_
#define DC_H_

#include "state.h"


enum
{
	DC_idle,
	DC_busy
}DC_state_id;

// Declare states functions CA
// Using enum for create a new name function
STATE_define(DC_idle); //void ST_CA_Waiting();
STATE_define(DC_busy); //void ST_CA_Driving();


void DC_init();
extern void (*DC_state)();


#endif /* DC_H_ */

