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


#include "Stm32f10xx_Common.h"
#include "Stm32f10xx_Address.h"

typedef enum 
{
  privileged = 0x00,
  non_privileged
}Access_level_typedef;


static inline __attribute__((always_inline)) void __set_MSP(uint32_t topOfMainStack)
{
  __asm volatile ("MSR msp, %0" : : "r" (topOfMainStack) : );
}


static inline __attribute__((always_inline)) void Access_level(Access_level_typedef Acc_level)
{
  int32_t val = (uint32_t)Acc_level;
    __asm("mrs R3,CONTROL       \n\t"
            "LSR R3,R3,#0x01    \n\t"
            "LSL R3,R3,#0x01    \n\t");

    __asm("msr CONTROL,%0" : : "r" (val) :);

}
#endif