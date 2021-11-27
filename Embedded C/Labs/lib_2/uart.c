#include "uart.h"

#define UARTDR	*((volatile unsigned int* const)(unsigned int *)(0x101f1000))
void UART_send(unsigned char* _P_arr)
{
	while(*_P_arr!='\0')
	{
		UARTDR=(unsigned int)(*_P_arr);
		*_P_arr++;
	}
}