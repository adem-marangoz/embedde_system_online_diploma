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
static void goto_app(void);

#define MAJOR       1
#define MINOR       2
uint16_t BL_Version[3] = {MAJOR,'.',MINOR};
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
    __APB2ENR_IOPCEN_En();              // Enable GPIOA Clock
    


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
    
    // _________________________ Config UART2_Driver ___________________________
    uart1_config.baudrate = (uint32_t)115200;
    uart1_config.Hw_Flow_CTRL = CTS_RTS_None;
    uart1_config.Mode = Enable_RX_Tx;
    uart1_config.Parity = Parity_None;
    uart1_config.Stop_bit = Stop_1_bit;
    uart1_config.Word_Len = Payload_8_bit;
    uart1_config.UARTx = UART2;
    uart1_config.interrupt = En_RX_Inter;
    uart1_config.P_Rx_CallBack = Rx_Uart2;
    Init_Uart(&uart1_config);

    //==========================================================================

    //______________________________ LEDS Configs ______________________________
    LEDS.Pin = GPIO_PIN_13;
    LEDS.Speed = GPIO_SPEED_FREQ_2MHZ;
    LEDS.Mode = GPIO_MODE_OUTPUT_PP ;
    Init_GPIO(GPIOC,&LEDS);
    //==========================================================================
    
    //____________________________ Button Configs ______________________________
    LEDS.Pin = GPIO_PIN_7;
    LEDS.Speed = GPIO_SPEED_INPUT_Mode;
    LEDS.Mode = GPIO_MODE_INPUT ;
    Init_GPIO(GPIOB,&LEDS);
    //==========================================================================


    //____________________________ Systick Config ______________________________
    Systick_API.Clock_Source = Processor_Clock_AHB;
    Systick_API.Current_Value = 0;
    Systick_API.Enable_Interrupt = Disable_Systick_Req;
    Systick_API.Reload_Value = 7999;
    Init_Systick();
    //==========================================================================
}


/**
 * @brief The function of interrupting the data entered by the UART1
 * @param UARTx : data structure for UART API
 */
void Rx_Uart1(St_Uart_API *UARTx)
{

}


/**
 * @brief The function of interrupting the data entered by the UART2
 * @param UARTx : data structure for UART API
 */
void Rx_Uart2(St_Uart_API *UARTx)
{

}

/**
 * @brief infinite loop
 */
void Infinite_loop()
{
    Send_Text_Uart(&uart1_config,"Starting Boot Mode\r\n", Enable);
    Send_Text_Uart(&uart1_config,"Bootloader Version:", Enable);
    Send_Char_Uart(uart1_config.UARTx,BL_Version, Enable);
    Send_Char_Uart(uart1_config.UARTx,&BL_Version[1], Enable);
    Send_Char_Uart(uart1_config.UARTx,&BL_Version[2], Enable);


    Send_Text_Uart(&uart1_config,"Press OTA Pin for update App firmware\r\n", Enable);
    GPIO_PinState OTA_Pin;
    uint32_t end_tick = Get_Tick() + 3000; // Wait 3 seconde for press OTA Pin
    
    do
    {
        OTA_Pin = Read_pin(GPIOC,GPIO_PIN_13);
        uint32_t start_tick = Get_Tick();

        if((OTA_Pin != GPIO_PIN_RESET) || (start_tick > end_tick))
        {
            break;
        }
    } while (1);
    
    /* Start the Firmawre or Application Update */
    if(OTA_Pin == GPIO_PIN_SET)
    {
        Send_Text_Uart(&uart1_config,"starting Firmware Downaload\r\n", Enable);

        

    }


   goto_app();
  
}


static void goto_app(void)
{
    void (*app_reset_handler)(void) = (void*)(*((volatile uint32_t*)(0x08002400 + 4U)));

    // Toggle_pin(GPIOA, LEDS.Pin);
    app_reset_handler();

}



//==============================================================================


//------------------------------- DATA STRUCTURE -------------------------------

//==============================================================================