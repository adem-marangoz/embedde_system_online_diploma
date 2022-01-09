/*
 * main_algoritma.h
 *
 *  Created on: Jan 1, 2022
 *      Author: MAHMMAD_ALNAJJAR
 */

#ifndef MAIN_ALGORITMA_H_
#define MAIN_ALGORITMA_H_

#include "state.h"

enum
{
	Data_waiting,
	Calculate_data
}Main_Al_State;

Al_fun(Data_waiting);
Al_fun(Calculate_data);

extern void (*Main_p_fun)();


#endif /* MAIN_ALGORITMA_H_ */
