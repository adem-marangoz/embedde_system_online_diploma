/*
 * US.h
 *
 *  Created on: Dec 23, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#ifndef US_H_
#define US_H_

#include "state.h"


enum
{
	US_busy
}US_state_id;

// Declare states functions US
// Using enum for create a new name function
STATE_define(US_busy); //void ST_US_busy();


void US_Init();
extern void (*US_state)();


#endif /* US_H_ */

