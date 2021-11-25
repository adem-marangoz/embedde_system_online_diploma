#include "uart.h"

#define UARTDR	*((volatile unisgned int*)(unisgned int*)(0x101f1000))
void UART_send(char _P_arr*)
{
	while(*_P_arr!='\0')
	{
		UARTDR=(unisgned int)(*_P_arr);
		*_P_arr++;
	}
}