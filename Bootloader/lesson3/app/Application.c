/**
 * @file Application.C
 * @author adem alnajjar (adem.alnajjar@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */


//------------------------------- INCLUDE FILES --------------------------------
#include "Application.h"
#include "defines.h"	
#include <string.h>
#include <stdio.h>
//==============================================================================


//----------------------------- EXTERNAL OBJECTES ------------------------------
St_Uart_API uart1_config = {0};
St_Uart_API uart2_config = {0};
//==============================================================================


//------------------------------- LOCAL OBJECTS --------------------------------
void Rx_Uart1(St_Uart_API *UARTx);
void Rx_Uart2(St_Uart_API *UARTx);
GPIO_InitTypeDef LEDS = {0};

#define MAJOR       1
#define MINOR       1
const uint8_t BL_Version[2] = {MAJOR,MINOR};
//==============================================================================


//--------------------------------- FUNCTIONS ----------------------------------

void config_Drives_and_Perpherals(void)
{
    /* Enable AFIO and GPIOA Clock */
    __APB2ENR_IOPAEN_En(); // Enable GPIOA Clock
    __APB2ENR_IOPCEN_En(); // Enable GPIOA Clock
    __APB2ENR_AFIOEN_En(); // Enable Alterntif Clock
    

    //____________________________ Systick Config ______________________________
    Systick_API.Clock_Source = Processor_Clock_AHB;
    Systick_API.Current_Value = 0;
    Systick_API.Enable_Interrupt = Disable_Systick_Req;
    Systick_API.Reload_Value = Microsecond_Prescale;
    Init_Systick();
    //==========================================================================

    // _________________________ Config UART1_Driver ___________________________
    uart1_config.baudrate = (uint32_t)115200;
    uart1_config.Hw_Flow_CTRL = CTS_RTS_None;
    uart1_config.Mode = Enable_RX_Tx;
    uart1_config.Parity = Parity_None;
    uart1_config.Stop_bit = Stop_1_bit;
    uart1_config.Word_Len = Payload_8_bit;
    uart1_config.UARTx = UART1;
    uart1_config.interrupt = En_RX_Inter;
    uart1_config.P_Rx_CallBack = Rx_Uart1;
    Init_Uart(&uart1_config);

    //==========================================================================

    //______________________________ LEDS Configs ______________________________
    LEDS.Pin = GPIO_PIN_13;
    LEDS.Speed = GPIO_SPEED_FREQ_2MHZ;
    LEDS.Mode = GPIO_MODE_OUTPUT_PP ;
    Init_GPIO(GPIOC,&LEDS);
    //==========================================================================

}


/**
 * @brief The function of interrupting the data entered by the RFID1
 * @param UARTx : data structure for UART API
 */
void Rx_Uart1(St_Uart_API *UARTx)
{

}

/**
 * @brief infinite loop
 */
void Infinite_loop()
{
   Reset_pin(GPIOC,GPIO_PIN_13);
   delay_us(10000);
   Set_pin(GPIOC,GPIO_PIN_13);
   delay_us(10000);
  
}



//==============================================================================


//------------------------------- DATA STRUCTURE -------------------------------

//==============================================================================