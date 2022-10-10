/*
*@author 	Adem Alnajjar
*@data		24.11.2021
*/

//_________________________________ Include Files ______________________________
#include "Stm32f10xx_GPIO.h"
#include "Stm32f10xx_EXTI.h"
#include "Stm32f10xx_RCC.h"
#include "Stm32f10xx_AFIO.h"
#include "Stm32f10xx_Address.h"
#include "LCD_Driver.h"
#include "Key_pad_Driver.h"
#include "Seven_Segment.h"
#include "Stm32f10x_UART.h"
#include <stdio.h>
#include "Stm32f10x_SPI.h"
#include "Stm32f10xx_I2C.h"
#include "EEPROM.h"

//==============================================================================


//______________________________ Generic Macro _________________________________
#define SPI_Maseter_En              1

//==============================================================================


//_____________________ Generica Function & Data Structure _____________________
void config(void);
void Exti15_CallBack(void);
extern void _delay_ms(uint32_t time);

    //______________________ Data Structre of Drives ___________________________
    LCD_16_2 Lcd_config={0};
    St_Key_pad key_pad_config = {0};
    St_7_segment seven_config = {0};
    St_Uart_API uart1_config = {0};
    St_SPI_API spi1_config = {0};
    St_SPI_API spi2_config = {0};
    St_SPI_API spi3_config = {0};
    St_I2C_API i2c1_config = {0};
    St_I2C_API i2c2_config = {0};
    //==========================================================================

uint16_t Rx_Buff[10] = {0};
// uint16_t test = 0x61;

//==============================================================================

int main(void)
{
    config(); // config RCC and GPIO

    Write_Character(&Lcd_config, 'D');
    while (1)
    {
        
    }
    
    return 1;
}


void config(void)
{
    /* Enable AFIO and GPIOA Clock */
    __APB2ENR_IOPAEN_En(); // Enable GPIOA Clock
    __APB2ENR_IOPBEN_En(); // Enable GPIOB Clock
    __APB2ENR_AFIOEN_En(); // Enable Alterntif Clock
    


    //___________________________ Config EEPROM ________________________________
    // EEPORM_Init(); 
    //==========================================================================


    //_________________________ Config LCD_Driver ______________________________
    Lcd_config.Data_Port = GPIOB;
	Lcd_config.Enable_Port = GPIOA;
	Lcd_config.RS_Port = GPIOA;
	Lcd_config.R_W_Port = GPIOA;
	Lcd_config.Enable_Pin = GPIO_PIN_0;
	Lcd_config.R_W_Pin = GPIO_PIN_1;
	Lcd_config.RS_Pin = GPIO_PIN_2;
    Lcd_config.Data_Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    LCD_init(&Lcd_config);
    //==========================================================================


    //_________________________ Config KeyPad_Driver ___________________________
    // key_pad_config.input.Port = GPIOA;
    // key_pad_config.input.Pins = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
    // key_pad_config.output.Port = GPIOA;
    // key_pad_config.output.Pins = GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
    // Key_pad_init(&key_pad_config);
    //==========================================================================


    //_________________________ Config 7_Segment_Driver ________________________
    // seven_config.Port = GPIOB;
    // seven_config.Pin_D[0] = GPIO_PIN_0;
    // seven_config.Pin_D[1] = GPIO_PIN_4;
    // seven_config.Pin_D[2] = GPIO_PIN_7;
    // seven_config.Pin_D[3] = GPIO_PIN_5;
    // init_seven_segment(&seven_config);
    //==========================================================================


    // _________________________ Config UART_Driver ____________________________
    // uart1_config.baudrate = (uint32_t)115200;
    // uart1_config.Hw_Flow_CTRL = CTS_RTS_None;
    // uart1_config.Mode = Enable_RX_Tx;
    // uart1_config.Parity = Parity_None;
    // uart1_config.Stop_bit = Stop_1_bit;
    // uart1_config.Word_Len = Payload_8_bit;
    // uart1_config.UARTx = UART1;
    // uart1_config.interrupt = En_RX_Inter ;
    // Init_Uart(&uart1_config);
    //==========================================================================


    //________________________ Config EXTI Pin Driver __________________________
    // St_EXTI_config exti_config1 = {0};
    // exti_config1.EXTI_State = EXTI_Enable;
    // exti_config1.EXTI_Trigger = FALLING_EDGE_Trigger;
    // exti_config1.P_IRQ_CallBack = Exti15_CallBack;
    // exti_config1.EXTI_Pin = EXTI0PA15;
    // Init_EXTI(&exti_config1);
    //==========================================================================


    //__________________________ Config SPI_Driver _____________________________
    // spi1_config.SPI_Inst = SPI1 ;
    // spi1_config.SPI_Mode = Full_Duplex;
    // spi1_config.BaudRate = FPCLK_div_8;
    // #if (SPI_Maseter_En == 1)
    //     spi1_config.Master_Select = SPI_Master;
    // #else
    //     spi1_config.Master_Select = SPI_Slave;
    // #endif
    // //spi1_config.Half_duplex_Mode = ;
    // spi1_config.NSS_Hardware_Mode = NSS_Hardware_Output_Dis_MultiMaster_En;
    // spi1_config.Slave_Select_Software = Software_Mang_Enable;
    // spi1_config.Frame_format = MSB_Trans;
    // spi1_config.Data_Legnth_format = Data_8_bit;
    // spi1_config.CLK_Phase_Polarity = Setup_Fall_Sample_Ris;
    // spi1_config.Rx_Tx_interrupt = SPI_interrupt_Dis;
    // Init_SPI(&spi1_config);
    //==========================================================================


    // _________________ Config NSS PIN As a Normal Pin ________________________
    // GPIO_InitTypeDef gpio_config = {0};
    // gpio_config.Pin = GPIO_PIN_4;
    // #if (SPI_Maseter_En == 1)
    //     gpio_config.Speed = GPIO_SPEED_FREQ_10MHZ;
    //     gpio_config.Mode = GPIO_MODE_OUTPUT_PP ;
    //     Init_GPIO(GPIOA,&gpio_config);
    //     Set_pin(GPIOA, GPIO_PIN_4);
    // #else
    //     gpio_config.Speed = GPIO_SPEED_INPUT_Mode;
    //     gpio_config.Mode = GPIO_MODE_AF_INPUT;
    // #endif
    //==========================================================================
}

// void Exti15_CallBack(void)
// {
//     Write_String_with_coordinator(&Lcd_config,"IRQ9 is Active",1,Seconde_R);
// }
