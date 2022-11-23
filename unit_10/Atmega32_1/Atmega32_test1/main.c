/*
 * Atmega32_test1.c
 *
 * Created: 5/19/2022 9:23:52 AM
 * Author : MAHMMAD_ALNAJJAR
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include "UART_driver.h"
#define F_CPU 8000000UL


extern void program(void);
extern void init(void);

int main(void)
{
    /* Replace with your application code */
	init();
	
	while (1)
	{
		program();
	}
    return 0;
}
