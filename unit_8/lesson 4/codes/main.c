/*
*@author 	Adem Alnajjar
*@data		24.11.2021
*/
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


void config(void);
void Exti15_CallBack(void);
extern void _delay_ms(uint32_t time);
LCD_16_2 Lcd_config={0};
St_Key_pad key_pad_config = {0};
St_7_segment seven_config = {0};
St_Uart_API uart1_config = {0};


uint16_t Rx_Buff[10] = {0};
uint16_t test = 0x61;

int main(void)
{
    config(); // config RCC and GPIO
    volatile uint32_t counter;
    Write_Character(&Lcd_config,'A');
    Write_Character(&Lcd_config,'B');
    Write_Character(&Lcd_config,'C');
    uint32_t counter1 = 0;
    Display_seven_segment(&seven_config,counter);
    uint16_t Tx_Buff[] = {'Y','O','U',' ','C', 'A','N',' ','D','O',' ','I','T'};
    Send_String_Uart(UART1, Tx_Buff,Enable);

    while (1)
    {
        Check_Prass_Button(&key_pad_config);
        if(counter1 > 9)
            counter1 = 0;
        Display_seven_segment(&seven_config,counter1);
        counter1++;
        _delay_ms(100);
    }    
    return 0;
}


void config(void)
{
    /* Enable AFIO and GPIOA Clock */
    __APB2ENR_IOPAEN_En(); // Enable alternatif Clock
    __APB2ENR_IOPBEN_En(); // Enable GPIOA Clock
    __APB2ENR_AFIOEN_En();
    
    /*Config GPIOA Pin_1 and Pin_13 As input floating*/

    Lcd_config.Data_Port = GPIOB;
	Lcd_config.Enable_Port = GPIOA;
	Lcd_config.RS_Port = GPIOA;
	Lcd_config.R_W_Port = GPIOA;
	Lcd_config.Enable_Pin = GPIO_PIN_0;
	Lcd_config.R_W_Pin = GPIO_PIN_1;
	Lcd_config.RS_Pin = GPIO_PIN_2;
    Lcd_config.Data_Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    LCD_init(&Lcd_config);

    key_pad_config.input.Port = GPIOA;
    key_pad_config.input.Pins = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
    key_pad_config.output.Port = GPIOA;
    key_pad_config.output.Pins = GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;

    Key_pad_init(&key_pad_config);

    seven_config.Port = GPIOB;
    seven_config.Pins = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
    init_seven_segment(&seven_config);


    uart1_config.baudrate = (uint32_t)115200;
    uart1_config.Hw_Flow_CTRL = CTS_RTS_None;
    uart1_config.Mode = Enable_RX_Tx;
    uart1_config.Parity = Parity_None;
    uart1_config.Stop_bit = Stop_1_bit;
    uart1_config.Word_Len = Payload_8_bit;
    uart1_config.UARTx = UART1;
    uart1_config.interrupt = En_RX_Inter ;
    Init_Uart(&uart1_config);

    St_EXTI_config exti_config1 = {0};
    exti_config1.EXTI_State = EXTI_Enable;
    exti_config1.EXTI_Trigger = FALLING_EDGE_Trigger;
    exti_config1.P_IRQ_CallBack = Exti15_CallBack;
    exti_config1.EXTI_Pin = EXTI0PA15;
    Init_EXTI(&exti_config1);


}

void Exti15_CallBack(void)
{
    Write_String_with_coordinator(&Lcd_config,"IRQ9 is Active",1,Seconde_R);
}
