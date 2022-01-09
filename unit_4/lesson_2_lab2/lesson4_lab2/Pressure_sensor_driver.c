/*
 * Pressure_sensor.c
 *
 *  Created on: Jan 1, 2022
 *      Author: MAHMMAD_ALNAJJAR
 */


#include "Pressure_sensor_driver.h"


void (*Pressure_P_fun)()=Pressure(Reading_and_sending);
int Get_Pressure_random(int l,int r, int count);

unsigned int Pressure_Value;






void init_Pressure()
{
	Cprint("\n---- Pressure_Init ----\n");
}

Pressure_fun(Reading_and_sending)
{
	Pressure_Value=Get_Pressure_random(15,25,1);
	Cprint("\nPressure_sensor_driver:---> Reading Pressure value = %d ",Pressure_Value);
	Send_pressure_value(Pressure_Value);
	Pressure_P_fun=Pressure(Waiting);

}


Pressure_fun(Waiting)
{
	Cprint("\nPressure_sensor_driver:---> waiting Pressure  value \n");
	volatile static unsigned int counter=0;
	counter++;
	if(counter==5)
	{
		counter=0;
		Pressure_P_fun=Pressure(Reading_and_sending);
		Cprint("Pressure_sensor_driver:---> Ending wait for pressure\n");
	}
}


int Get_Pressure_random(int l,int r, int count)
{
	int i;
	for(i=0;i<count;i++)
	{
		int rand_num=(rand()%(r-l+1))+l;
		return rand_num;
	}
	return 0;
}
