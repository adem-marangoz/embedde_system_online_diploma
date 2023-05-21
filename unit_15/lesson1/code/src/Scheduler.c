/**
 * @file Scheduler.c
 * @author Adem Marangoz (adem.alnajjar@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

//------------------------------- Include Files --------------------------------
#include "Scheduler.h"
#include "Os_System.h"
#include "Queue_RTOS.h"
#include <string.h>
//==============================================================================


//------------------------------ General Objects -------------------------------

//==============================================================================


//------------------------------- Local Objects --------------------------------
State_Typedef Create_MSP(void);
State_Typedef Create_Task(Scheduler_Typedef *Tref);
void Init_PSP_Task(Scheduler_Typedef *Tref);


void Idle_Task(void);


/**
 * @brief 
 * 
 */
struct 
{
    Scheduler_Typedef *OS_Task_Table[100];
    Scheduler_Typedef *Current_Task;
    Scheduler_Typedef *Next_Task;
    uint32_t _S_OS_MSP;
    uint32_t _E_OS_MSP;
    uint32_t PSP_Locator;
    uint32_t NoOfActiveTasks;
    enum
    {
        OS_Suspend,
        Os_Running
    }OS_State;
}OS_Control;


FIFO_Buf_t Ready_Queue;
Scheduler_Typedef* OS_Task_Table[100];
Scheduler_Typedef Task_Idle;



State_Typedef Create_MSP(void)
{
    State_Typedef state = Ok; 
    /* Define the range of the MSP of the operation system */  
    OS_Control._S_OS_MSP = (uint32_t)&_estack;
    OS_Control._E_OS_MSP = (OS_Control._S_OS_MSP - MSP_Size);

    /* Aligned 8 Bytes spaces between Main Task and PSP tasks */
    OS_Control.PSP_Locator = (OS_Control._E_OS_MSP - (uint32_t)8);

    if(OS_Control.PSP_Locator < (uint32_t)&_heap_End) {state = Not_Ok;} 
    return state;
}


void Idle_Task(void)
{
    while (1)
    {
        __asm("nop");
    }
    
}

State_Typedef Create_Task(Scheduler_Typedef *Tref)
{
    State_Typedef state = Ok;
    Tref->_S_Task_PSP = OS_Control.PSP_Locator;
    Tref->_E_Task_PSP = (Tref->_S_Task_PSP - Tref->Task_PSP_Size);

    OS_Control.PSP_Locator = (Tref->_E_Task_PSP - (uint32_t)8);  
    if(OS_Control.PSP_Locator < (uint32_t)&_heap_End) {return Not_Ok;}

    Init_PSP_Task(Tref);

    OS_Control.OS_Task_Table[OS_Control.NoOfActiveTasks] = Tref;
    OS_Control.NoOfActiveTasks++;

    Tref->Task_State = Suspend;

    return state;
}


void Init_PSP_Task(Scheduler_Typedef *Tref)
{
    Tref->Current_PSP = (uint32_t*)Tref->_S_Task_PSP;
    Tref->Current_PSP--;
    *(Tref->Current_PSP) = 0x01000000;
    
    Tref->Current_PSP--;
    *(Tref->Current_PSP) = (uint32_t)Tref->f_TaskEntry;
    
    Tref->Current_PSP--;
    *(Tref->Current_PSP) = 0xFFFFFFFD;

    for(uint8_t i = 0; i < 13; i++)
    {
        Tref->Current_PSP--;
        *(Tref->Current_PSP) = 0;
    }

}

//==============================================================================


//------------------------------- Global Objects -------------------------------

//==============================================================================


//------------------------------------ API -------------------------------------

//==============================================================================
State_Typedef MYRTOS_init()
{
    State_Typedef state = Ok;

    OS_Control.OS_State = OS_Suspend;           // Update OS State (OS_suspend)
    if(Create_MSP() != Ok) {return Not_Ok;}     // Specify the MSP for OS

    if(FIFO_init(&Ready_Queue, OS_Task_Table, 100) != FIFO_no_Error) {return Not_Ok;}

    //Configure IDLE TASK
    __builtin_memcpy(Task_Idle.Taskname, "IdleTask", 8);
    Task_Idle.priority = 255;
    Task_Idle.f_TaskEntry = Idle_Task;
    Task_Idle._S_Task_PSP = 300;

    if(Create_Task(&Task_Idle) != Ok) { return Not_Ok;}

    return state;

}


State_Typedef MYRTOS_CreateTask(Scheduler_Typedef* Tref)
{

}


State_Typedef MYRTOS_ActivateTask (Scheduler_Typedef* Tref)
{

}


State_Typedef MYRTOS_TerminateTask (Scheduler_Typedef* Tref)
{

}


State_Typedef MYRTOS_STARTOS() 
{


}


State_Typedef MYRTOS_TaskWait(unsigned int NoTICKS,Scheduler_Typedef* SelfTref)
{

}
