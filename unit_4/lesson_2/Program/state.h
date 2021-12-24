/*
 * state.h
 *
 *  Created on: Dec 23, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#ifndef STATE_H_
#define STATE_H_

#include <stdio.h>
#include <stdlib.h>

#define Cprint(...)	{fflush(stdin);\
					fflush(stdout);\
					printf(__VA_ARGS__);\
					fflush(stdin);\
					fflush(stdout);\
					}

#define STATE_define(_statFUN_) void ST_##_statFUN_()
#define STATE(_statFUN_)  ST_##_statFUN_

// states connection
void US_Set_distance(int d);
void DC_motor_Set(int s);


#endif /* STATE_H_ */
