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
//==============================================================================


//------------------------------- Global Objects -------------------------------
St_Systick_API Systick_API = {0};


void Init_Systick(void)
{
    SysTick->STK_CTRL = Systick_API.Enable_Interrupt | Systick_API.Clock_Source;
    if((Systick_API.Reload_Value == Microsecond_Prescale) || (Systick_API.Reload_Value == Milisecond_Prescale))
    {
        SysTick->STK_LOAD = Get_HCLK_Freq()/Systick_API.Reload_Value;
    }else
    {
        SysTick->STK_LOAD = Systick_API.Reload_Value;
    }
    SysTick->STK_VAL = Systick_API.Current_Value;

    if(Systick_API.Enable_Interrupt == Enable_Systick_Req)
    {
        NVIC_EnableIRQ(SysTick_IRQn);
    }
}
//==============================================================================