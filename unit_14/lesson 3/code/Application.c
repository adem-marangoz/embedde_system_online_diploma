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
#include "Stm32f10xx_AFIO.h"
#include "Arm_CortexM4.h"
#include <string.h>
#include <stdio.h>
//==============================================================================


//----------------------------- EXTERNAL OBJECTES ------------------------------

//==============================================================================


//------------------------------- LOCAL OBJECTS --------------------------------
void Exti15_CallBack(void);
uint8_t Interrupt_Flag = 0;
//==============================================================================


//--------------------------------- FUNCTIONS ----------------------------------

void config_Drives_and_Perpherals(void)
{
    /* Enable AFIO and GPIOA Clock */
    __APB2ENR_AFIOEN_En();              // Enable Alterntif Clock
    __APB2ENR_IOPAEN_En();              // Enable GPIOA Clock

    /* Config GPIOA pin 1 as input interrupt rising edge*/
    GPIO_InitTypeDef gpioconfig= {0};
    gpioconfig.Pin = GPIO_PIN_0;
    gpioconfig.Speed = GPIO_SPEED_INPUT_Mode;
    gpioconfig.Mode = GPIO_MODE_IT_RISING;
    Init_GPIO(GPIOA, &gpioconfig);
   
    St_EXTI_config exti_config1 = {0};
    exti_config1.EXTI_State = EXTI_Enable;
    exti_config1.EXTI_Trigger = RISING_EDGE_Trigger;
    exti_config1.P_IRQ_CallBack = Exti15_CallBack;
    exti_config1.EXTI_Pin = EXTI0PA0;
    Init_EXTI(&exti_config1);
}


/**
 * @brief infinite loop
 */
int8_t Val1 = 3;
void Infinite_loop()
{

    Access_level(non_privileged);
    while(1)
    {
        if(Interrupt_Flag) {Interrupt_Flag = 0;}
    }
    
}

void Exti15_CallBack(void)
{
    Interrupt_Flag = 1;
    Access_level(privileged);
}


//==============================================================================


//------------------------------- DATA STRUCTURE -------------------------------

//==============================================================================