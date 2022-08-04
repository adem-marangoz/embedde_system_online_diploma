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
#include <stdio.h>

void config(void);

LCD_16_2 Lcd_config={0};



int main(void)
{
    config(); // config RCC and GPIO
    volatile uint32_t counter;
    Write_Character(&Lcd_config,'A');
    Write_Character(&Lcd_config,'B');
    Write_Character(&Lcd_config,'D');
    while (1)
    {
        
        for(counter = 0; counter < 100000; counter++);
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
}
