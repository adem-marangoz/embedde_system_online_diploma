#include "uart.h"
#include "uart2.h"
unsigned char buffer[30]="You-Can-do-it: ";
unsigned char const buffer2[14]="Yarab Saidni";
unsigned char buffer3[12]="Adem Marangoz";
void main(void)
{
	UART_send(buffer);
	uart2_send(buffer3);
	
}