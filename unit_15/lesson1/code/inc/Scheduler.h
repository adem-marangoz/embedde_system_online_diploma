/**
 * @file Scheduler.h
 * @author adem alnajjar (adem.marangoz95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

//------------------------------- Include Files --------------------------------
#include "Stm32f10xx_Common.h"
//==============================================================================


//------------------------------ General Objects -------------------------------


/**
 * @brief 
 * 
 */
typedef enum
{
    Suspend,
    Running,
    Waiting,
    Ready
}Task_State_Typedef;


/**
 * @brief 
 * 
 */
typedef struct 
{
    uint8_t Taskname[30];               // Task Name
    uint32_t Task_PSP_Size;             // Size of Task
    uint32_t _S_Task_PSP;               // Start Address of Task Stack
    uint32_t _E_Task_PSP;               // End Address of Task Stack
    uint32_t *Current_PSP;              // Last Current PSP Addres before exit
    Task_State_Typedef Task_State;      // Task State
    void (*f_TaskEntry)(void);          // Task Function
    struct 
    {
        enum
        {
            Block_Enable,
            Block_Disable
        }Blocking_State;
        uint32_t Ticks_count;
    }Block;                             // For Wait or Delay in Task 
    uint8_t priority;                   // Priority Task Rang 0 - 255 High pirority 0
}Scheduler_Typedef;

//==============================================================================

//------------------------------ Local Functions -------------------------------

//==============================================================================


//---------------------------- Global Functions -----------------------------
State_Typedef MYRTOS_init();
State_Typedef MYRTOS_CreateTask(Scheduler_Typedef* Tref);
State_Typedef MYRTOS_ActivateTask (Scheduler_Typedef* Tref);
State_Typedef MYRTOS_TerminateTask (Scheduler_Typedef* Tref);
State_Typedef MYRTOS_STARTOS() ;
State_Typedef MYRTOS_TaskWait(unsigned int NoTICKS,Scheduler_Typedef* SelfTref);
//==============================================================================

#endif