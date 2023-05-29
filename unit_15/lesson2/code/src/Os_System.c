/**
 * @file Os_System.c
 * @author adem marangoz (adem.marangoz95@gmail.com)
 * @brief OS Driver 
 * @version 0.1
 * @date 2023-05-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */


//------------------------------- Include Files --------------------------------
#include "Os_System.h"
#include "Scheduler.h"
//==============================================================================



//------------------------------- Extern Objects -------------------------------

/**
 * @brief NMI Handler
 */
void NMI_Handler(void)
{

}

/**
 * @brief Hard Fault Handler
 */
void Hard_Fault_Handler(void)
{

}

/**
 * @brief Bus Fault Handler
 */
void Bus_Fault_Handler(void)
{

}

/**
 * @brief Usage Fault Handler
 */
void Usage_Fault_Handler(void)
{

}

/**
 * @brief SVC Handler
 */
__attribute ((naked)) void SVCall_Handler()
{
    __asm("TST lr,#4        \n\t"
            "ITE EQ         \n\t"
            "mrseq r0,MSP   \n\t"
            "mrsne r0,PSP   \n\t"
            "B OS_SVC");
}

//==============================================================================

