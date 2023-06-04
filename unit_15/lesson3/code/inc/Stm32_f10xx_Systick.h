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


    //____________________________ API EasyConfig ______________________________
    // Systick_API.Clock_Source = Processor_Clock_AHB;
    // Systick_API.Current_Value = 0;
    // Systick_API.Enable_Interrupt = Enable_Systick_Req;
    // Systick_API.Reload_Value = 7999;
    // Init_Systick();
    //==========================================================================

//------------------------------- Generaic Objects -----------------------------

#define Max_Delay                   0xFFFFFFFFU
#define COUNGFLAG                   1 << 16

// @ref Systic_Clock_Source_define
#define AHB_Divided_8               0x00000000U
#define Processor_Clock_AHB         1 << 2

// @ref Systick_Interrupt_Req_define
#define Enable_Systick_Req          1 << 1
#define Disable_Systick_Req         0x00000000U

#define ENABLE_Systick              1U

#define Microsecond_Prescale        1000000 - 1
#define Milisecond_Prescale         1000 - 1


/** @defgroup TICK_FREQ Tick Frequency
  * @{
  */
typedef enum
{
  TICK_FREQ_10HZ         = 100U,
  TICK_FREQ_100HZ        = 10U,
  TICK_FREQ_1KHZ         = 1U,
}TickFreq_Typedef;

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
void Delay_ms(uint32_t ms);
uint32_t Get_Tick();
void Inc_Tick();

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