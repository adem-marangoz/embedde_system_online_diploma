/**
 * @file Stm32_f10xx_Systick.h
 * @author adem alnajjar (adem.alnajjar95@gmail.com)
 * @brief Systick Driver
 * @version 0.1
 * @date 2022-10-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef STM32_F10XX_SYSTICK_H_
#define STM32_F10XX_SYSTICK_H_

//------------------------------- Include Files --------------------------------
#include "Stm32f10xx_Common.h"
#include "Stm32f10xx_Address.h"
//==============================================================================


//------------------------------- Generaic Objects -----------------------------

#define COUNGFLAG                   1 << 16

// @ref Systic_Clock_Source_define
#define AHB_Divided_8               0x00000000U
#define Processor_Clock_AHB         1 << 2

// @ref Systick_Interrupt_Req_define
#define Enable_Systick_Req          1 << 1
#define Disable_Systick_Req         0x00000000U

#define ENABLE_Systick              1 << 0

#define Microsecond_Prescale        1000000
#define Milisecond_Prescale         1000

typedef struct 
{
    uint32_t Reload_Value;      /* auto reload register, after hitting 0, count 
                                (VAL register) is reset to this value */

    uint32_t Current_Value;     /* current value register */

    uint32_t Enable_Interrupt;  /* This member configures the Intrrupt enable
                                    This parameter must be set base on @ref Systick_Interrupt_Req_define */

    uint32_t Clock_Source;      /* This member configures the Systick Clock Source
                                    This paremeter must be set vase on @ref Systic_Clock_Source_define */
}St_Systick_API;

extern St_Systick_API Systick_API;

//==============================================================================


//-------------------------------- Global Functions ----------------------------
void Init_Systick(void);

static inline void delay_us(uint32_t us)
{
    SysTick->STK_VAL = 0;
    SysTick->STK_CTRL |= ENABLE_Systick;
    while(us)
    {
        while ((SysTick->STK_CTRL & COUNGFLAG) == 0);
        us--;
    }
    SysTick->STK_CTRL &= ~(ENABLE_Systick);
}

//==============================================================================



#endif