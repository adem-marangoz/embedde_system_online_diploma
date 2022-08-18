#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include "Common.h"
#include <avr/io.h>


typedef union
{
    __IO uint8_t UCSRA_field;
    struct 
    {   
        __IO uint8_t MPCM_b   :1;     /*Multi-processor Communication Mode*/
        __IO uint8_t U2X_b    :1;     /*Double the USART Transmission Speed*/
        __IO uint8_t PE_b     :1;     /*Parity Error*/
        __IO uint8_t DOR_b    :1;     /*Data OverRun*/
        __IO uint8_t FE_b     :1;     /*Frame Error*/
        __IO uint8_t UDRE_b   :1;     /*USART Data Register Empty*/
        __IO uint8_t TXC_b    :1;     /*USART Transmit Complete*/
        __IO uint8_t RXC_b    :1;     /*USART Receive Complete*/
    }UCSRA_bits;
}UCSRA_Register;




typedef union
{
    __IO uint8_t UCSRB_field;
    struct 
    {   
        __IO uint8_t TXB8_b   :1;     /*Transmit Data Bit 8*/     
        __IO uint8_t RXB8_b   :1;     /*Receive Data Bit 8*/
        __IO uint8_t UCSZ2_b  :1;     /*Character Size*/
        __IO uint8_t TXEN_b   :1;     /*Transmitter Enable*/
        __IO uint8_t RXEN_b   :1;     /*Receiver Enable*/
        __IO uint8_t UDRIE_b  :1;     /*USART Data Register Empty Interrupt Enable*/
        __IO uint8_t TXCIE_b  :1;     /*TX Complete Interrupt Enable*/
        __IO uint8_t RXCIE_b  :1;     /*RX Complete Interrupt Enable*/
    }UCSRB_bits;
}UCSRB_Register;



typedef union
{
    __IO uint8_t UCSRC_field;
    struct 
    {   
        __IO uint8_t UCPOL_b  :1;     /*Clock Polarity*/
        __IO uint8_t UCSZ0_b  :1;     /*Charachter Size*/
        __IO uint8_t UCSZ1_b  :1;     /*Charachter Size*/
        __IO uint8_t USBS_b   :1;     /*Stop Mode*/
        __IO uint8_t UPM0_b   :1;     /*Parity Mode*/
        __IO uint8_t UPM1_b   :1;     /*Parity Mode*/
        __IO uint8_t UMSEL_b  :1;     /*UART Mode Select*/
        __IO uint8_t URSEL_b  :1;     /*Register Select*/ 
    }UCSRC_bits;
}UCSRC_Register;





#define UCSRA_R         ((volatile UCSRA_Register*)0x2B)
#define UCSRB_R         ((volatile UCSRB_Register*)0x2A)
#define UCSRC_R         ((volatile UCSRC_Register*)0x40)

typedef enum
{
    Asynchronous = 0,
    synchronous
}En_Uart_Mode;

typedef enum
{
    Half_Duplex_Transimit = 1,
    Half_Duplex_Receive,
    Full_Duplex
}En_Communcation_Mode;


typedef enum
{
    Disable = 0,
    Even_Parity = 2,
    Odd_Parity
}En_Parity_Mode;

typedef enum
{
    One_bit = 0,
    Two_bit
}En_Stop_Mode;

typedef enum
{
    Five_bit = 0,
    Six_bit,
    Seven_bit,
    Eight_bit,
    Night_bit = 7
}En_Charachter_Size;

typedef enum
{
    Rising_Edge = 0,
    Falling_Edge
}En_Clock_Polarity;


typedef enum
{
    Normal_Speed = 16,
    Double_Speed = 8
}En_Uart_speed;

typedef struct 
{
    En_Uart_Mode Mode;
    En_Stop_Mode Stop;
    En_Charachter_Size Char_Size;
    En_Clock_Polarity Clk_Polarity;
    En_Parity_Mode Parity;
    En_Communcation_Mode Communcation_Mode;
    En_Uart_speed Speed;
    unsigned int BuadRate;
}St_UART_driver;



#define BuadRate_Max            4095

extern St_UART_driver UART_Config;
uint8_t Init_Uart(St_UART_driver *_init_uart);
void Uart_send(uint8_t msg);

#endif