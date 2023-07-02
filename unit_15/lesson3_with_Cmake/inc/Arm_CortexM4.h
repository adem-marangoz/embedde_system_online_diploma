/**
 * @file Arm_CortexM4.h
 * @author adem alnajjar (adem.marangoz95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef ARM_CORTEXM4_H_
#define ARM_CORTEXM4_H_

//------------------------------- Include Files --------------------------------

#include "Stm32f10xx_Common.h"
#include "Stm32f10xx_Address.h"
//==============================================================================

//------------------------------ Generic Objects -------------------------------
                                  
//==============================================================================


//------------------------------- Local Objects --------------------------------
static inline __attribute__((always_inline)) void __set_MSP(uint32_t topOfMainStack)
{
  __asm volatile ("MSR msp, %0" : : "r" (topOfMainStack) : );
}

//==============================================================================


//------------------------------ Global Functions ------------------------------

//==============================================================================
#endif