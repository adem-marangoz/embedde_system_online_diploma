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
#include "Stm32f10xx_Flash.h"
#include "Stm32f10xx_AFIO.h"
#include "update_Firmware.h"
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
GPIO_InitTypeDef LEDS2 = {0};
static void goto_app(void);

// #define MAJOR       (uint8_t)1
// #define MINOR       (uint8_t)2
uint16_t BL_Version[3] = {'1','.', '2'};
//==============================================================================


//--------------------------------- FUNCTIONS ----------------------------------

void config_Drives_and_Perpherals(void)
{
    /* Enable AFIO and GPIOA Clock */
    __Flash_Prefetch_Buffer_Enable();   // Enable Prefetch Buffer 
    __APB2ENR_AFIOEN_En();              // Enable Alterntif Clock
    __AFIO_REMAP_SWJ_NOJTAG();          // Enable SW-DP and Disable JTAG-DP
    __APB1ENR_PWREN_EN();               // Enable Power Control
    __APB2ENR_IOPAEN_En();              // Enable GPIOA Clock
    __APB2ENR_IOPBEN_En();              // Enable GPIOA Clock
    __APB2ENR_IOPCEN_En();              // Enable GPIOA Clock
    __APB2ENR_AFIOEN_En();              // Enable Alterntif Clock
    

    //____________________________ Systick Config ______________________________
    Systick_API.Clock_Source = Processor_Clock_AHB;
    Systick_API.Current_Value = 0;
    Systick_API.Enable_Interrupt = Enable_Systick_Req;
    Systick_API.Reload_Value = 7999;
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
    uart1_config.interrupt = 0;
    uart1_config.P_Rx_CallBack = NULL;
    Init_Uart(&uart1_config);
    //==========================================================================
    
    // _________________________ Config UART2_Driver ___________________________
    uart2_config.baudrate = (uint32_t)115200;
    uart2_config.Hw_Flow_CTRL = CTS_RTS_None;
    uart2_config.Mode = Enable_RX_Tx;
    uart2_config.Parity = Parity_None;
    uart2_config.Stop_bit = Stop_1_bit;
    uart2_config.Word_Len = Payload_8_bit;
    uart2_config.UARTx = UART3;
    uart2_config.interrupt = 0;
    uart2_config.P_Rx_CallBack = NULL;
    Init_Uart(&uart2_config);

    //==========================================================================

    //______________________________ LEDS Configs ______________________________
    LEDS.Pin = GPIO_PIN_13;
    LEDS.Speed = GPIO_SPEED_FREQ_2MHZ;
    LEDS.Mode = GPIO_MODE_OUTPUT_PP ;
    Init_GPIO(GPIOC,&LEDS);
    //==========================================================================
    
    //____________________________ Button Configs ______________________________
    // LEDS2.Pin = GPIO_PIN_7;
    // LEDS2.Speed = GPIO_SPEED_INPUT_Mode;
    // LEDS2.Mode = GPIO_MODE_INPUT ;
    // Init_GPIO(GPIOB,&LEDS2);
    //==========================================================================


    
    Send_Text_Uart(&uart2_config,"\r\nBlinking 6s\r\n", Enable);
    Set_pin(GPIOC,GPIO_PIN_13);
    Delay_ms(1000);
    Reset_pin(GPIOC,GPIO_PIN_13);
    Delay_ms(1000);
    Set_pin(GPIOC,GPIO_PIN_13);
    Delay_ms(1000);
    Reset_pin(GPIOC,GPIO_PIN_13);
    Delay_ms(1000);
    Set_pin(GPIOC,GPIO_PIN_13);
    Delay_ms(1000);
    Reset_pin(GPIOC,GPIO_PIN_13);
    Delay_ms(1000);
   
}


/**
 * @brief The function of interrupting the data entered by the UART1
 * @param UARTx : data structure for UART API
 */
void Rx_Uart1(St_Uart_API *UARTx)
{
    Send_Text_Uart(&uart1_config,"Received data by uart1 ...\r\n", Enable);
}


/**
 * @brief The function of interrupting the data entered by the UART2
 * @param UARTx : data structure for UART API
 */
void Rx_Uart2(St_Uart_API *UARTx)
{
    Send_Text_Uart(&uart1_config,"Received data by uart2 ...\r\n", Enable);
}

/**
 * @brief infinite loop
 */
void Infinite_loop()
{
    Send_Text_Uart(&uart1_config,"Starting Boot Mode ...\r\n", Enable);
    Send_Text_Uart(&uart1_config,"Bootloader Version:\t", Enable);
    Send_Char_Uart(uart1_config.UARTx,BL_Version, Enable);
    Send_Char_Uart(uart1_config.UARTx,&BL_Version[1], Enable);
    Send_Char_Uart(uart1_config.UARTx,&BL_Version[2], Enable);
    Send_Text_Uart(&uart1_config,"\r\n", Enable);

    update_firmware();

    goto_app();
    while(1)
    {
    }
    
}


static void goto_app(void)
{
    Send_Text_Uart(&uart1_config,"Finally Jump to application ...\r\n", Enable);
    void (*app_reset_handler)(void) = (void*)(*((volatile uint32_t*)(0x08004400 + 4U)));

    if(app_reset_handler == (void*)0xFFFFFFFF)
    {
        Send_Text_Uart(&uart1_config,"Invalid Application HALT...\r\n", Enable);
        while(1);
    }
    // Toggle_pin(GPIOA, LEDS.Pin);
    app_reset_handler();

}



//==============================================================================


//------------------------------- DATA STRUCTURE -------------------------------

//==============================================================================