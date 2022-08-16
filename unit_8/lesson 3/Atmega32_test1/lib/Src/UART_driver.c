#include "UART_driver.h"

St_UART_driver UART_Config = {0};

uint8_t Init_Uart(St_UART_driver *_init_uart)
{
    if((_init_uart->BuadRate >= 0) && (_init_uart <= BuadRate_Max))
    {
        UBRRH = (unsigned char)(_init_uart->BuadRate >> 8) ;
        UBRRL = (unsigned char)_init_uart->BuadRate;
    }else
    {
        return 0;
    }
    UCSRB_R->UCSRB_field = ((_init_uart->Communcation_Mode) << TXEN | ((_init_uart->Char_Size & 0x04) << UCSZ2));
	UCSRC = 0b10000000;
	//uint8_t x = ((1 << URSEL) | (_init_uart->Mode << UMSEL) | (_init_uart->Parity << UPM0) | (_init_uart->Stop << USBS) | ((_init_uart->Char_Size & 0x03) << UCSZ0) | (_init_uart->Clk_Polarity << UCPOL));
    return 1;
}