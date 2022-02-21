/*
 * main_algroritma.c
 *
 *  Created on: Jan 1, 2022
 *      Author: MAHMMAD_ALNAJJAR
 */


#include "main_algoritma.h"

unsigned int Pressure_Value;
unsigned int Threshold=20;

void (*Main_p_fun)()=Al_d(Data_waiting);


Al_fun(Data_waiting)
{
	//Cprint("\nmain_algoritma:---> Data waiting --->");
}


Al_fun(Calculate_data)
{
	//Cprint("\nmain_algoritma:---> Calculated Data \n");
	if(Pressure_Value>Threshold)
	{
		//Cprint("main_algoritma:---> Pressure High Detected\n");
		Timer_starting();
	}
	Main_p_fun=Al_d(Data_waiting);
}


void Send_pressure_value(unsigned int p)
{
	Pressure_Value=p;
	//Cprint("\nmain_algoritma:---> Data Received ");
	Main_p_fun=Al_d(Calculate_data);
}
