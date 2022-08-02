/*
*@author 	Adem Alnajjar
*@data		24.11.2021
*/
#include "Stm32f10xx_GPIO.h"
#include "Stm32f10xx_EXTI.h"
#include "Stm32f10xx_RCC.h"
#include "Stm32f10xx_AFIO.h"
#include "Stm32f10xx_Address.h"
#include <stdio.h>

void config(void);


int main(void)
{
    config(); // config RCC and GPIO
    volatile uint32_t counter;
    while (1)
    {
        while(Read_pin(GPIOA,GPIO_PIN_1) == GPIO_PIN_SET)
        {
            if(Read_pin(GPIOA,GPIO_PIN_1) == GPIO_PIN_RESET)
            {
                Toggle_pin(GPIOB,GPIO_PIN_1);
                break;
            }
        }
        if(Read_pin(GPIOA,GPIO_PIN_13) == GPIO_PIN_SET)
        {
            Toggle_pin(GPIOB,GPIO_PIN_13);
        }
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
    GPIO_InitTypeDef gpioconfig= {0};
    gpioconfig.Pin = GPIO_PIN_1 | GPIO_PIN_13; 
    gpioconfig.Mode = GPIO_MODE_INPUT_FLOATING;
    gpioconfig.Speed = GPIO_SPEED_FREQ_IN;
    Init_GPIO(GPIOA, &gpioconfig);

    /*Config GPIOB Pin_1 and Pin_13 As Output*/
    gpioconfig.Pin = GPIO_PIN_1 | GPIO_PIN_13;
    gpioconfig.Speed = GPIO_SPEED_FREQ_2MHZ;
    gpioconfig.Mode = GPIO_MODE_OUTPUT_PP;
    Init_GPIO(GPIOB, &gpioconfig);

}
