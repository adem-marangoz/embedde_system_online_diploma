/**
 * @file Os_System.h
 * @author adem alnajjar (adem.marangoz95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef OS_SYSTEM_H_
#define OS_SYSTEM_H_

//------------------------------- Include Files --------------------------------
#include "Stm32f10xx_Common.h"
//==============================================================================


//------------------------------- Extern Objects -------------------------------

extern uint32_t _estack;
extern uint32_t _heap_End;
//==============================================================================

//------------------------------ General Objects -------------------------------

#define MSP_Size        3072
#define MSP_SP                  (uint32_t)0x00
#define PSP_SP                  (uint32_t)0x02
#define Access_privileged       (uint32_t)0x00
#define Access_unprivileged     (uint32_t)0x01

#define Switch_SP(sp_sw)        __asm volatile("mrs R1,CONTROL   \n\t and R1,#0xFFFFFFFD   \n\t msr CONTROL,R1   \n\t  orr R1,R1,%0   \n\t msr CONTROL,R1" : : "r" (sp_sw):)   
#define Set_PSP_Add(Add)        __asm volatile("mov R0,%0   \n\t msr PSP,R0" : : "r" (Add):)
#define Get_PSP_Add(Add)        __asm volatile("mrs R0,PSP      \n\t mov %0,R0" : "=r" (add) : :)
#define Set_MSP_Add(Add)        __asm volatile("mov R0,%0   \n\t msr MSP,R0" : : "r" (Add):)      
#define Access_level(level)     __asm volatile("mrs R1,CONTROL  \n\t and R1,#0xFFFFFFFE  \n\t msr CONTROL,R1  \n\t orr R1,R1,%0   \n\t msr CONTROL,R1" : : "r" (level):)
#define SVC_Exception           __asm("SVC #0x03")
//==============================================================================


//------------------------------- Local Objects --------------------------------

//==============================================================================


//------------------------------- Global Objects -------------------------------

//==============================================================================


//------------------------------------ API -------------------------------------

//==============================================================================


#endif