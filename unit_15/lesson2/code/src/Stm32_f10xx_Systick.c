/**
 * @file Stm32_f10xx_Systick.c
 * @author adem alnajjar (adem.alnajjar95@gmail.com)
 * @brief Systim Timer Driver
 * @version 0.1
 * @date 2022-10-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */


//------------------------------- Include File ---------------------------------
#include "Stm32_f10xx_Systick.h"
#include "Stm32f10xx_RCC.h"
#include "Stm32f10xx_EXTI.h"
#include "Scheduler.h"
//==============================================================================


//------------------------------- Global Objects -------------------------------
St_Systick_API Systick_API = {0};
TickFreq_Typedef uTick_Freq = TICK_FREQ_1KHZ;
volatile uint32_t uTick;
//==============================================================================


//------------------------------ Globla Function -------------------------------

/**
 * @brief This function used to Initalization Systick
 */
void Init_Systick(void)
{
    
    if((Systick_API.Reload_Value == Microsecond_Prescale) || (Systick_API.Reload_Value == Milisecond_Prescale))
    {
        SysTick->STK_LOAD = Get_HCLK_Freq()/Systick_API.Reload_Value;
    }else
    {
        SysTick->STK_LOAD = Systick_API.Reload_Value;
    }
    SysTick->STK_VAL = Systick_API.Current_Value;

    // Config clock source and interrupt and Enable Systick
    SysTick->STK_CTRL = Systick_API.Enable_Interrupt | Systick_API.Clock_Source | ENABLE_Systick;
    
    if(Systick_API.Enable_Interrupt == Enable_Systick_Req)
    {
        NVIC_EnableIRQ(SysTick_IRQn);
    }
}


void Delay_ms(uint32_t ms)
{
    uint32_t tickstart = Get_Tick();
    uint32_t wait = ms;

    /* Add a freq to guarantee minimum wait */
    if (wait < Max_Delay)
    {
        wait += (uint32_t)(uTick_Freq);
    }

    while ((Get_Tick() - tickstart) < wait)
    {
    }
}

/**
  * @brief Provides a tick value in millisecond.
  * @note  This function is declared as to be overwritten in case of other
  *       implementations in user file.
  * @retval tick value
  */
uint32_t Get_Tick()
{
    return uTick;
}


/**
  * @brief This function is called to increment  a global variable "uTick"
  *        used as application time base.
  * @note In the default implementation, this variable is incremented each 1ms
  *       in SysTick ISR.
  * @note This function is declared as  to be overwritten in case of other
  *      implementations in user file.
  * @retval None
  */
void Inc_Tick()
{
    uTick += uTick_Freq;
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
    // Inc_Tick();
    Decide_WhatNext();
    Trigger_Os_PendSV();
}
//==============================================================================