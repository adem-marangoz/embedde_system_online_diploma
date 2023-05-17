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
typedef enum 
{
  privileged = 0x00,
  non_privileged
}Access_level_typedef;

#define MSP_SP                  (uint32_t)0x00
#define PSP_SP                  (uint32_t)0x02
#define Access_privileged       (uint32_t)0x00
#define Access_unprivileged     (uint32_t)0x01
#define Switch_SP(sp_sw)    __asm volatile("mrs R1,CONTROL   \n\t and R1,#0xFFFFFFFD   \n\t msr CONTROL,R1   \n\t  orr R1,R1,%0   \n\t msr CONTROL,R1" : : "r" (sp_sw):)   
#define Set_PSP_Add(Add)    __asm volatile("mov R0,%0   \n\t msr PSP,R0" : : "r" (Add):)
#define Set_MSP_Add(Add)    __asm volatile("mov R0,%0   \n\t msr MSP,R0" : : "r" (Add):)      
#define Access_level(level) __asm volatile("mrs R1,CONTROL  \n\t and R1,#0xFFFFFFFE  \n\t msr CONTROL,R1  \n\t orr R1,R1,%0   \n\t msr CONTROL,R1" : : "r" (level):)
#define SVC_Exception       __asm("SVC #0x03")                                  
//==============================================================================


//------------------------------- Local Objects --------------------------------
static inline __attribute__((always_inline)) void __set_MSP(uint32_t topOfMainStack)
{
  __asm volatile ("MSR msp, %0" : : "r" (topOfMainStack) : );
}

//==============================================================================


//------------------------------ Global Functions ------------------------------

// static inline __attribute__((always_inline)) void Access_level(Access_level_typedef Acc_level)
// {
//   int32_t val = (uint32_t)Acc_level;
//     __asm("mrs R3,CONTROL       \n\t"
//             "LSR R3,R3,#0x01    \n\t"
//             "LSL R3,R3,#0x01    \n\t");

//     __asm("msr CONTROL,%0" : : "r" (val) :);

// }

// __attribute__((naked)) void Access_level(Access_level_typedef Acc_level);
//==============================================================================
#endif