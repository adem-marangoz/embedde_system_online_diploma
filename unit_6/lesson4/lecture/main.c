/*
*@author 	Adem Alnajjar
*@data		24.11.2021
*/
#include "Stm32f10xx_GPIO.h"
#include "Stm32f10xx_EXTI.h"
#include "Stm32f10xx_RCC.h"
#include "Stm32f10xx_AFIO.h"
#include <stdio.h>

void config(void);


int main(void)
{
    config(); // config RCC and GPIO
    Set_pin(GPIOA,GPIO_PIN_13);
    while (1)
    {
        Reset_pin(GPIOA,GPIO_PIN_13);
    }
    return 0;
}


void config(void)
{
    /* Enable AFIO and GPIOA Clock */
    __APB2ENR_AFIOEN_En(); // Enable alternatif Clock
    __APB2ENR_IOPAEN_En(); // Enable GPIOA Clock
    
    /*Config GPIOA Pin 13 As Output*/
    GPIO_InitTypeDef gpioconfig= {0};
    gpioconfig.Pin = GPIO_PIN_13; 
    gpioconfig.Mode = GPIO_MODE_OUTPUT_PP;
    gpioconfig.Speed = GPIO_SPEED_FREQ_2MHZ;
    Init_GPIO(GPIOA, &gpioconfig);

    /*Config GPIOA Pin 0 As Input Interrupt Rising Edge*/
    gpioconfig.Pin = GPIO_PIN_0;
    gpioconfig.Speed = GPIO_SPEED_FREQ_IN;
    gpioconfig.Mode = GPIO_MODE_IT_RISING;
    Init_GPIO(GPIOA, &gpioconfig);

    /*Enable Line0 Interrupt By GPIOA*/
    __NVIC_EnableIRQ(EXTI0_IRQn);
}


/*EXTI0 Line0 Interrupt Handler Function*/
void EXTI0_Handler(void)
{
    Set_pin(GPIOA,GPIO_PIN_13);
    /*Clear Pending Bit*/
    EXTI_EXTI_Clear_Handler(GPIO_PIN_0);
}