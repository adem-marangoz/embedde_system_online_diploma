/*
 * Atmega32_test1.c
 *
 * Created: 5/19/2022 9:23:52 AM
 * Author : MAHMMAD_ALNAJJAR
 */ 

#include <avr/io.h>
#include <avr/delay.h>
extern void program(void);
extern void init(void);

int main(void)
{
	
    /* Replace with your application code */
	init();
	while (1)
	{
		program();
		_delay_ms(1000);
	}
    return 0;
}






