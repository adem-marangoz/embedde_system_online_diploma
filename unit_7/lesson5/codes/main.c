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
#include <stdio.h>


void config(void);
extern void _delay_ms(uint32_t time);
LCD_16_2 Lcd_config={0};
St_Key_pad key_pad_config = {0};
St_7_segment seven_config = {0};


int main(void)
{
    config(); // config RCC and GPIO
    volatile uint32_t counter;
    Write_Character(&Lcd_config,'A');
    Write_Character(&Lcd_config,'B');
    Write_Character(&Lcd_config,'C');
    uint32_t counter1 = 0;
    Display_seven_segment(&seven_config,counter);
    while (1)
    {
        Check_Prass_Button(&key_pad_config);
        if(counter1 > 9)
            counter1 = 0;
        Display_seven_segment(&seven_config,counter1);
        counter1++;
        _delay_ms(10);
    }    
    return 0;
}


void config(void)
{
    /* Enable AFIO and GPIOA Clock */
    __APB2ENR_IOPAEN_En(); // Enable alternatif Clock
    __APB2ENR_IOPBEN_En(); // Enable GPIOA Clock
    
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
    key_pad_config.output.Pins = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;

    Key_pad_init(&key_pad_config);

    seven_config.Port = GPIOB;
    seven_config.Pins = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
    init_seven_segment(&seven_config);
}
