#include "uart2.h"


#define UARTDR2	*((volatile unsigned int* const)(unsigned int *)(0x101f1000))
void uart2_send(unsigned char* _P_arr)
{
	while(*_P_arr!='\0')
	{
		UARTDR2=(unsigned int)(*_P_arr);
		*_P_arr++;
	}
}