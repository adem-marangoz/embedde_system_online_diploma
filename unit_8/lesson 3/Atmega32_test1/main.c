/*
 * Atmega32_test1.c
 *
 * Created: 5/19/2022 9:23:52 AM
 * Author : MAHMMAD_ALNAJJAR
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include "UART_driver.h"

extern void program(void);
extern void init(void);

void uuart_send(unsigned char ch)
{
	while(!(UCSRA & (1 << UDRE)));
	UDR = ch;
}

int main(void)
{
    /* Replace with your application code */
	init();
	// UCSRB = 1 << TXEN;
	// UCSRC = (1 << UCSZ1) | ( 1 << UCSZ0) | (1 << URSEL);
	// UBRRL = 0x33;
	
	while (1)
	{
		// char str[] = "You can do it \n\r";
		// for(unsigned char i = 0; str[i] != '\0';i++)
		// {
			
		// 	uuart_send(str[i]);
		// 	_delay_ms(1000);	
		// }
		program();
		//_delay_ms(1000);
	}
    return 0;
}






