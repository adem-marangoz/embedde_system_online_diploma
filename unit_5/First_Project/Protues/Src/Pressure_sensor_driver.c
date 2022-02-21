/*
 * Pressure_sensor.c
 *
 *  Created on: Jan 1, 2022
 *      Author: MAHMMAD_ALNAJJAR
 */


#include "Pressure_sensor_driver.h"


void (*Pressure_P_fun)()=Pressure(Reading_and_sending);
unsigned int Pressure_Value;






void init_Pressure()
{
	SET_BIT(APB2ENR, 2);
	GPIOA_CRL &= 0xFF0FFFFF;
	GPIOA_CRL |= 0x00000000;
	//Cprint("\n---- Pressure_Init ----\n");
}

Pressure_fun(Reading_and_sending)
{
	Pressure_Value=(GPIOA_IDR & 0xFF);
	//Cprint("\nPressure_sensor_driver:---> Reading Pressure value = %d ",Pressure_Value);
	Send_pressure_value(Pressure_Value);
	Pressure_P_fun=Pressure(Waiting);

}


Pressure_fun(Waiting)
{
	//Cprint("\nPressure_sensor_driver:---> waiting Pressure  value \n");
	volatile static unsigned int counter=0;
	counter++;
	if(counter==50000)
	{
		counter=0;
		Pressure_P_fun=Pressure(Reading_and_sending);
		//Cprint("Pressure_sensor_driver:---> Ending wait for pressure\n");
	}
}

