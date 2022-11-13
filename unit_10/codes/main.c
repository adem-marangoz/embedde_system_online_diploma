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
#include "Stm32f10xx_Timers.h"
#include "Stm32_f10xx_Systick.h"
#include "EEPROM_25xx256.h"

//==============================================================================


//______________________________ Generic Macro _________________________________
#define SPI_Maseter_En              1

//==============================================================================


//_____________________ Generica Function & Data Structure _____________________
void config(void);
void Exti15_CallBack(void);
extern void _delay_ms(uint32_t time);

    //______________________ Data Structre of Drives ___________________________
    
    GPIO_InitTypeDef LEDS = {0};
    LCD_16_2 Lcd_config={0};
    St_Key_pad key_pad_config = {0};
    St_7_segment seven_config = {0};
    St_Uart_API uart1_config = {0};
    St_Uart_API uart2_config = {0};
    St_SPI_API spi1_config = {0};
    St_SPI_API spi2_config = {0};
    St_SPI_API spi3_config = {0};
    St_I2C_API i2c1_config = {0};
    St_I2C_API i2c2_config = {0};
    GPIO_InitTypeDef NSS_EEPROM = {0};
    GPIO_InitTypeDef NSS_ATmega1 = {0};
    GPIO_InitTypeDef NSS_ATmega2 = {0};
    St_EEPROM_25xx256_Typedef EEPORM_25xx_config = {0};
    //==========================================================================

// uint16_t Rx_Buff[14] = {0};

//==============================================================================
int main(void)
{
    config(); // config RCC and GPIO
    // uint16_t Tx_Buff[] = {'Y','O','U',' ','C', 'A','N',' ','D','O',' ','I','T'};
    // uint16_t test[] = {'A' , 'D', 'E', 'D', ' ', 'M', 'A', 'R', 'A', 'N', 'G', 'O', 'Z'};
    // // Send_String_Uart(UART1, Tx_Buff,Enable);
    // Enable_Write_EEPROM_25xx(&EEPORM_25xx_config);
    // delay_us(10000);
    // // Write_Byte_EEPROM_25xx(&EEPORM_25xx_config, 0x0002, 0xFF);
    // Write_Bytes_EEPROM_25xx(&EEPORM_25xx_config, 0x0002, 13, Tx_Buff);
    // delay_us(10000);
    // Read_Byte_EEPROM_25xx(&EEPORM_25xx_config, 0x0002, 13, Rx_Buff);
    // Send_String_Uart(UART1, Rx_Buff,Enable);


    while (1)
    {
        // Send_String_Uart(UART1, Tx_Buff,Enable);
        // _delay_ms(100);
    }    

    return 1;
}


void config(void)
{
    /* Enable AFIO and GPIOA Clock */
    __APB2ENR_IOPAEN_En(); // Enable GPIOA Clock
    __APB2ENR_IOPBEN_En(); // Enable GPIOB Clock
    __APB2ENR_AFIOEN_En(); // Enable Alterntif Clock
    

    //____________________________ Systick Config ______________________________
    Systick_API.Clock_Source = Processor_Clock_AHB;
    Systick_API.Current_Value = 0;
    Systick_API.Enable_Interrupt = Disable_Systick_Req;
    Systick_API.Reload_Value = Microsecond_Prescale;
    Init_Systick();
    
    //==========================================================================


    //_________________________ Config LCD_Driver ______________________________
    Lcd_config.Data_Port = GPIOA;
	Lcd_config.Enable_Port = GPIOB;
	Lcd_config.RS_Port = GPIOB;
	Lcd_config.R_W_Port = GPIOB;
	Lcd_config.Enable_Pin = GPIO_PIN_0;
	Lcd_config.R_W_Pin = GPIO_PIN_1;
	Lcd_config.RS_Pin = GPIO_PIN_3;
    #ifdef LCD_8_Bit
    Lcd_config.Data_Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    // Lcd_config.Data_Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10;
    #endif
    #ifdef LCD_4_Bit
    // Lcd_config.Data_Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    Lcd_config.Data_Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    #endif
    LCD_init(&Lcd_config);
    //==========================================================================


    //_________________________ Config KeyPad_Driver ___________________________
    key_pad_config.Soruce.Port = GPIOB;
    key_pad_config.Soruce.Pins = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    key_pad_config.Drain.Port = GPIOA;
    key_pad_config.Drain.Pins = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4;
    Key_pad_init(&key_pad_config);
    //==========================================================================


    //_________________________ Config 7_Segment_Driver ________________________
    seven_config.Port = GPIOA;
    seven_config.Pin_D[0] = GPIO_PIN_0;
    seven_config.Pin_D[1] = GPIO_PIN_1;
    seven_config.Pin_D[2] = GPIO_PIN_11;
    seven_config.Pin_D[3] = GPIO_PIN_12;
    init_seven_segment(&seven_config);
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
    Init_Uart(&uart1_config);
    //==========================================================================
    
    // _________________________ Config UART2_Driver ___________________________
    uart2_config.baudrate = (uint32_t)115200;
    uart2_config.Hw_Flow_CTRL = CTS_RTS_None;
    uart2_config.Mode = Enable_RX_Tx;
    uart2_config.Parity = Parity_None;
    uart2_config.Stop_bit = Stop_1_bit;
    uart2_config.Word_Len = Payload_8_bit;
    uart2_config.UARTx = UART2;
    uart2_config.interrupt = En_RX_Inter;
    Init_Uart(&uart2_config);
    //==========================================================================

    //__________________________ Config SPI_Driver _____________________________
    spi1_config.SPI_Inst = SPI1 ;
    spi1_config.SPI_Mode = Full_Duplex;
    spi1_config.BaudRate = FPCLK_div_4;
    #if (SPI_Maseter_En == 1)
        spi1_config.Master_Select = SPI_Master;
    #else
        spi1_config.Master_Select = SPI_Slave;
    #endif
    //spi1_config.Half_duplex_Mode = ;
    spi1_config.NSS_Hardware_Mode = NSS_Hardware_Output_Dis_MultiMaster_En;
    spi1_config.Slave_Select_Software = Software_Mang_Enable;
    spi1_config.Frame_format = MSB_Trans;
    spi1_config.Data_Legnth_format = Data_8_bit;
    spi1_config.CLK_Phase_Polarity = Sample_Ris_Setup_Fall;
    spi1_config.Rx_Tx_interrupt = SPI_interrupt_Dis;
    Init_SPI(&spi1_config);
    //==========================================================================

    // _________________ Config NSS PIN As a Normal Pin ________________________
    NSS_EEPROM.Pin = GPIO_PIN_8;
    #if (SPI_Maseter_En == 1)
        NSS_EEPROM.Speed = GPIO_SPEED_FREQ_2MHZ;
        NSS_EEPROM.Mode = GPIO_MODE_OUTPUT_PP ;
        Init_GPIO(GPIOB,&NSS_EEPROM);
        Set_pin(GPIOB, NSS_EEPROM.Pin);
    #else
        NSS_EEPROM.Speed = GPIO_SPEED_INPUT_Mode;
        NSS_EEPROM.Mode = GPIO_MODE_AF_INPUT;
    #endif
    //==========================================================================
    
    //_____________________________ NSS Atmega32_1 _____________________________
    NSS_ATmega1.Pin = GPIO_PIN_9;
    NSS_ATmega1.Speed = GPIO_SPEED_FREQ_2MHZ;
    NSS_ATmega1.Mode = GPIO_MODE_OUTPUT_PP ;
    Init_GPIO(GPIOB,&NSS_ATmega1);
    Set_pin(GPIOB, NSS_ATmega1.Pin);
    //==========================================================================

    //_____________________________ NSS Atmega32_2 _____________________________
    NSS_ATmega2.Pin = GPIO_PIN_10;
    NSS_ATmega2.Speed = GPIO_SPEED_FREQ_2MHZ;
    NSS_ATmega2.Mode = GPIO_MODE_OUTPUT_PP ;
    Init_GPIO(GPIOB,&NSS_ATmega2);
    Set_pin(GPIOB, NSS_ATmega2.Pin);
    //==========================================================================

    //______________________________ LEDS Configs ______________________________
    LEDS.Pin = GPIO_PIN_8 | GPIO_PIN_11;
    LEDS.Speed = GPIO_SPEED_FREQ_2MHZ;
    LEDS.Mode = GPIO_MODE_OUTPUT_PP ;
    Init_GPIO(GPIOA,&LEDS);
    //==========================================================================

    //__________________________ Config EEPORM 25xx ____________________________
    EEPORM_25xx_config.EEPROM_SPI = &spi1_config;
    EEPORM_25xx_config.GPIOx = GPIOA;
    EEPORM_25xx_config.NSS_Pin = GPIO_PIN_4;
    //==========================================================================

    //___________________________ Config EEPROM ________________________________
    // EEPORM_Init(); 
    //==========================================================================

    // ___________________________ Config Timer ________________________________
    // tim1_config.Instance = TIM1;
    // tim1_config.Prescaler = 0;
    // tim1_config.CounterMode = TIM_COUNTERMODE_UP;
    // tim1_config.Period = 0xFFFF;
    // tim1_config.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    // tim1_config.RepetitionCounter = 0;
    // tim1_config.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    // Init_Timer(&tim1_config);
    //==========================================================================


    //___________________________ Config Pin_Out _______________________________
    // GPIO_InitTypeDef gpio_pin_out = {0};
    // gpio_pin_out.Mode = GPIO_MODE_OUTPUT_PP;
    // gpio_pin_out.Speed = GPIO_SPEED_FREQ_10MHZ;
    // gpio_pin_out.Pin = GPIO_PIN_14;
    // Init_GPIO(GPIOA,&gpio_pin_out);
    //==========================================================================

    //________________________ Config EXTI Pin Driver __________________________
    // St_EXTI_config exti_config1 = {0};
    // exti_config1.EXTI_State = EXTI_Enable;
    // exti_config1.EXTI_Trigger = FALLING_EDGE_Trigger;
    // exti_config1.P_IRQ_CallBack = Exti15_CallBack;
    // exti_config1.EXTI_Pin = EXTI0PA15;
    // Init_EXTI(&exti_config1);
    //==========================================================================

}

// void Exti15_CallBack(void)
// {
//     Write_String_with_coordinator(&Lcd_config,"IRQ9 is Active",1,Seconde_R);
// }
