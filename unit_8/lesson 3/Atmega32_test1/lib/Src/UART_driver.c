#include "UART_driver.h"
#include "GPIO.h"


St_UART_driver UART_Config = {0};


uint8_t Init_Uart(St_UART_driver *_init_uart)
{   
    if((_init_uart->BuadRate >= 0) && (_init_uart <= BuadRate_Max))
    {
		long pay = (long)(_init_uart->BuadRate)*_init_uart->Speed;
        unsigned int baud = ((8000000/pay) - 1);
        UBRRH = (unsigned char)(baud >> 8) ;
        UBRRL = (unsigned char)baud;
    }else
    {
        return 0;
    }
    UCSRA_R->UCSRA_field = ((_init_uart->Speed & 0x08) << U2X);
    UCSRB_R->UCSRB_field = ((_init_uart->Communcation_Mode) << TXEN | ((_init_uart->Char_Size & 0x04) << UCSZ2));
	uint8_t x = ((1 << URSEL) | (_init_uart->Mode << UMSEL) | (_init_uart->Parity << UPM0) | (_init_uart->Stop << USBS) | ((_init_uart->Char_Size & 0x03) << UCSZ0) | (_init_uart->Clk_Polarity << UCPOL));
    UCSRC_R->UCSRC_field = x;

    

    return 1;
}

void Uart_send(unsigned char msg)
{
    while(!(UCSRA_R->UCSRA_field & (1<<UDRE)));

    UDR = msg;
}