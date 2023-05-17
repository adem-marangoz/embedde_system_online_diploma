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
extern unsigned int _stack_top;
//==============================================================================


//------------------------------- LOCAL OBJECTS --------------------------------
void Exti15_CallBack(void);
int Task_A(int a, int b, int c);
int Task_B(int a, int b, int c, int d);
void Init_Os(void);
uint8_t Interrupt_Flag = 0;

#define MSP_Size            512
#define Task_A_Size         100
#define Task_B_Size         100

// Main Stack
uint32_t _S_MSP = &_stack_top;
uint32_t _E_MSP = 0;

// Task A
uint32_t _S_Task_A = 0;
uint32_t _E_Task_A = 0;
uint8_t Task_A_Flag = 0;

// Task B
uint32_t _S_Task_B = 0;
uint32_t _E_Task_B = 0;
uint8_t Task_B_Flag = 0;

//==============================================================================


//--------------------------------- FUNCTIONS ----------------------------------

int Task_A(int a, int b, int c)
{
    return (a + b + c);
}


int Task_B(int a, int b, int c, int d)
{
    return (a + b + c + d);
}


void Init_Os(void)
{
    _E_MSP = (_S_MSP - (uint32_t)MSP_Size);             // End Address of MSP
    _S_Task_A = (_E_MSP - (uint32_t)8);                 // Start address of Task A
    _E_Task_A = (_S_Task_A - (uint32_t)Task_A_Size);    // End address of Task A
    _S_Task_B = (_E_Task_A - (uint32_t)8);              // Start address of Task B
    _E_Task_B = (_E_Task_B - (uint32_t)Task_B_Size);    // End address of Task B

    while(1)
    {
        __asm("nop");
        if(Task_A_Flag == 1)
        {   
            Set_PSP_Add(_S_Task_A);                 // Set PSP value -> Task A
            Switch_SP(PSP_SP);                      // Set SP -> PSP
            Access_level(Access_unprivileged);      // privilgied -> unpriviliged
            Task_A_Flag = Task_A(1,2,3);            // Call Task A
            SVC_Exception;                          // unpriviligied -> priviliged
            Switch_SP(MSP_SP);                      // Set SP -> MSP
            Task_A_Flag = 0;                        // Clear Task A flag
        }else if(Task_B_Flag == 1)
        {
            Set_PSP_Add(_S_Task_B);                 // Set PSP value -> Task B
            Switch_SP(PSP_SP);                      // Set SP -> PSP
            Access_level(Access_unprivileged);      // privilgied -> unpriviliged
            Task_B_Flag = Task_B(1,2,3,4);          // Call Task B
            SVC_Exception;                          // unpriviligied -> priviliged
            Switch_SP(MSP_SP);                      // Set SP -> MSP
            Task_B_Flag = 0;                        // Clear Task B flag
        }

    }
}

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
void Infinite_loop()
{
    Init_Os();
    
}

void Exti15_CallBack(void)
{
    if(Interrupt_Flag == 0)
    {
        Task_A_Flag = 1;
        Interrupt_Flag = 1;
    }else
    {
        Task_B_Flag = 1;
        Interrupt_Flag = 0;
    }
}

void SVCall_Handler()
{
    Access_level(Access_privileged);
}


//==============================================================================


//------------------------------- DATA STRUCTURE -------------------------------

//==============================================================================