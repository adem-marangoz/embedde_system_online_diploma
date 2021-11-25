#include "uart.h"

char buffer[30]="You Can do it";
int main()
{
	UART_send(buffer);
	return 0;
}