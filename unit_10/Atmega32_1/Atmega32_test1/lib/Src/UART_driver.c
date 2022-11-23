#include "UART_driver.h"
#include "GPIO.h"
#include "avr/interrupt.h"
#include "LCD_16_2.h"

St_UART_driver UART_Config = {0};
extern volatile LCD_16_2 Lcd_config;
/**
 * @brief           This function is used to initialize the Uart Peripheral
 * @param[in]       _init_uart: UART data structure containing the uart parameters specified by the user 
 * @return uint8_t  0 : Fail
 *                  1 : Success
 */
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

/**
 * @brief       Used to send a character through Uart
 * @param[in]   msg: Character value   
 */
void Uart_send(unsigned int msg)
{
    while(!(UCSRA_R->UCSRA_field & (1<<UDRE)));

    UCSRB_R->UCSRB_bits.TXB8_b = 0;
    if(msg & 0x100)
        UCSRB_R->UCSRB_bits.TXB8_b = 1;

    UDR = (unsigned char)msg;
}


/**
 * @brief       Used to send a string through Uart     
 * @param[in]   msg : Contain The first address of String  
 */
void Uart_Send_String(unsigned char *msg)
{
    for(int i = 0 ; *msg != '\0' ; msg++)
    {
        Uart_send(*msg);
    }
}

/**
 * @brief   Used to Receiv Data form UART by polling
 * @return  unsigned char: return received value 
 */
unsigned char *Uart_Receive(St_UART_driver *_init_uart)
{
    uint8_t index = 0;
    unsigned char status, resh, resl;
    
    while(_init_uart->msg[index] != '#')
    {
        
        while(!(UCSRA_R->UCSRA_field & (1 << RXC)));

        status = UCSRA_R->UCSRA_field;
        resh = UCSRB_R->UCSRB_field;
        resl = UDR;

        if(status & ((1 << FE)|(1 << DOR)|(1 << PE)))
            return -1;
        resh = (resh >> 1) & 0x01;
        if((index == 15) || (_init_uart->msg[index] == '#')){index = 0;}
        _init_uart->msg[index] = ((resh << 8) | resl);
        if(_init_uart->msg[index] == '#') {return &_init_uart->msg[index];}
        index++;
    }
    

    
}

ISR(USART_RXC_vect)
{
    Uart_Receive(&UART_Config);
}


ISR(USART_TXC_vect)
{

}


ISR(USART_UDRE_vect)
{
    UCSRB_R->UCSRB_bits.UDRIE_b = 0;
}