/*
 * CA.h
 *
 *  Created on: Dec 23, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#ifndef CA_H_
#define CA_H_

#include "state.h"


enum
{
	CA_Waiting,
	CA_Driving
}CA_state_id;

// Declare states functions CA
// Using enum for create a new name function
STATE_define(CA_Waiting); //void ST_CA_Waiting();
STATE_define(CA_Driving); //void ST_CA_Driving();

extern void (*CA_state)();


#endif /* CA_H_ */

