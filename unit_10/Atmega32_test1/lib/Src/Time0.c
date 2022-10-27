/**
 * @file Time0.c
 * @author adem alnajjar (adem.marangoz@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//_________________________________ INCLUDES ___________________________________
#include "Time0.h"
#include <avr/io.h>
#include "GPIO.h"
#include <time.h>
#include "avr/interrupt.h"

//==============================================================================


//_______________________________ GLOBAL FUNCTIONS _____________________________

uint8_t Timer0_Init(St_Timer0_API *Timerx)
{

    // Timer Comapare value 
    OCR0 = (uint8_t)0x00;
    OCR0 |= Timerx->Compare_Time;

    // Enable/Disable Interrupt
    TIMSK |= Timerx->Interrupt;

    // Init counter value
    TCNT0 = Timerx->init_counter_value;
    
    // Config Timer0
    TCCR0 |= (Timerx->Mode) | (Timerx->Com_Mode) | (Timerx->CLK_Mode);
    
    return 1;
}


uint8_t Change_Timer_Mode(St_Timer0_API *Timerx)
{
    TCCR0 &= ~(PWM_Fast);
    TCCR0 |= Timerx->Mode;
    
    return 1;
}





uint8_t En_Dis_Interrupt(St_Timer0_API *Timerx)
{
    TIMSK |= Timerx->Interrupt;
    
    return 1;
}


uint8_t Timer0_Stop(St_Timer0_API *Timerx)
{
    TCCR0 &= ~(External_CLK_T1_Rising_Edge);

    return 1;
}


uint8_t Set_Compare_Value(St_Timer0_API *Timerx, uint8_t *Com_val)
{ 
    OCR0 = (uint8_t)0x00;
    OCR0 = *Com_val;

    return 1;
}


uint8_t Timer0_Get_Compare_Val(St_Timer0_API *Timerx, uint8_t *Com_val)
{
    *Com_val = OCR0;
    return 1;
}

uint8_t Timer0_Set_Counter_Val(St_Timer0_API *Timerx, uint8_t *Count_val)
{ 
    TCNT0 = *Count_val;

    return 0;
}

uint8_t Timer0_Get_Counter_Val(St_Timer0_API *Timerx, uint8_t *Count_val)
{
    *Count_val = TCNT0;

    return 1;
}



ISR(TIMER0_COMP_vect)
{
    counter++;
}


ISR(TIMER0_OVF_vect)
{
    
}


//==============================================================================