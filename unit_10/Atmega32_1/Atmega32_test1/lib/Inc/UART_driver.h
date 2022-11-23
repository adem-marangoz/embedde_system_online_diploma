/**
 * @file UART_driver.h
 * @author adem alnajjar (adem.marangoz95@gmail.com)
 * @brief This header is used to define bits and registers and the API for UART
 * @version 0.1
 * @date 2022-09-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include "Common.h"
#include <avr/io.h>


#define BuadRate_Max            4095


/*UCSRA Register made to be access by field and bit*/
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



/*UCSRB Register made to be access by field and bit*/
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


/*UCSRC Register made to be access by field and bit*/
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


/*@En_Uart_Mode : In this Enumeration for select UART mode Asyn or Syn*/
typedef enum
{
    Asynchronous = 0,
    synchronous
}En_Uart_Mode;

/*@En_Communcation_Mode : In this Enumeration for select Uart mode : Rx,Tx or both*/
typedef enum
{
    Half_Duplex_Transimit = 1,
    Half_Duplex_Receive,
    Full_Duplex
}En_Communcation_Mode;


/*@En_Parity_Mode : In this enumeration using for select parity bit in frame*/
typedef enum
{
    Disable = 0,
    Even_Parity = 2,
    Odd_Parity
}En_Parity_Mode;


/*@En_Stop_Mode : In this enumeration using for select stop bit in frame*/
typedef enum
{
    One_bit = 0,
    Two_bit
}En_Stop_Mode;

/*@En_Charachter_Size : In this enumeration using for select data size of frame*/
typedef enum
{
    Five_bit = 0,
    Six_bit,
    Seven_bit,
    Eight_bit,
    Night_bit = 7
}En_Charachter_Size;

/*@En_Clock_Polarity : In this enumeration using for select XCK detecting data mode for Syn mode*/
typedef enum
{
    Rising_Edge = 0,
    Falling_Edge
}En_Clock_Polarity;

/*@En_Uart_speed: In this enumeration using for select Uart Speed*/
typedef enum
{
    Normal_Speed = 16,
    Double_Speed = 8
}En_Uart_speed;


enum
{
    Dis_Interrupt = 0,
    En_Interrupt
}En_Interrupt_state;

//=============================== UART API =====================================
typedef struct 
{
    En_Uart_Mode Mode;                      /*!< Specifies the UART mode to be configured.
                                                This parameter can be any value of @ref En_Uart_Mode */
    En_Stop_Mode Stop;                      /*!< Specifies the UART Frame stop bit to be configured.
                                                This parameter can be any value of @ref En_Stop_Mode*/
    En_Charachter_Size Char_Size;           /*!< Specifies the UART Charachter size to be configured.
                                                This parameter can be any value of @ref En_Charachter_Size */
    En_Clock_Polarity Clk_Polarity;         /*!< Specifies the UART XCK clock polarity to be configured.
                                                This parameter can be any value of @ref En_Clock_Polarity */
    En_Parity_Mode Parity;                  /*!< Specifies the UART parity to be configured.
                                                This parameter can be any value of @ref En_Parity_Mode */
    En_Communcation_Mode Communcation_Mode; /*!< Specifies the UART Asyn or Syn to be configured.
                                                This parameter can be any value of @ref En_Communcation_Mode */
    En_Uart_speed Speed;                    /*!< Specifies the UART Speed normal or double to be configured.
                                                This parameter can be any value of @ref En_Uart_speed */
    unsigned int BuadRate;                  /*!< Specifies the UART buard rate to be configured*/

    unsigned char *msg;                     /*Specifies the Uart receive firs address*/
}St_UART_driver;
//==============================================================================


//====================== Interrupt Enable/Disable Macro ========================
/*Enable Rx Complate interrupt*/
#define Rx_Complate_Inter_En()                  UCSRB_R->UCSRB_bits.RXCIE_b = 1            
/*Disable Rx Complate interrupt*/
#define Rx_Complate_Inter_Dis()                 UCSRB_R->UCSRB_bits.RXCIE_b = 0

/*Enable Tx Complate interrupt*/
#define Tx_Complate_inter_En()                  UCSRB_R->UCSRB_bits.TXCIE_b = 1
/*Disable Tx Complate interrupt*/
#define Tx_Complate_inter_Dis()                 UCSRB_R->UCSRB_bits.TXCIE_b = 0

/*Enable Uart Data Empty*/
#define Uart_Data_Empty_En()                    UCSRB_R->UCSRB_bits.UDRIE_b = 1
/*Disable Uart Data Empty*/
#define Uart_Data_Empty_Dis()                   UCSRB_R->UCSRB_bits.UDRIE_b = 0
//==============================================================================


//============================= Function Deceration ============================
extern St_UART_driver UART_Config;
uint8_t Init_Uart(St_UART_driver *_init_uart);
void Uart_send(unsigned int msg);
void Uart_Send_String(unsigned char *msg);
unsigned char *Uart_Receive(St_UART_driver *_init_uart);

//==============================================================================

#endif