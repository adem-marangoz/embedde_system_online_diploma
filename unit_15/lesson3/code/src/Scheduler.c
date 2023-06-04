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
#include "Stm32f10xx_Address.h"
#include <string.h>
#include "Stm32_f10xx_Systick.h"
#include "Stm32f10xx_EXTI.h"
//==============================================================================


//------------------------------ General Objects -------------------------------
/**
 * @brief Structure of OS
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

/**
 * @brief Enum of SVC Services
 */
enum SVC_Services
{
    Activate_SVC_Service,
    Terminate_SVC_Service,
    Wait_SVC_Service,
    AquireMutex_SVC_Service,
    ReleaseMutex_SVC_Service
};

FIFO_Buf_t Ready_Queue; // Control Ready Buffer Structure

Scheduler_Typedef* Ready_QUEUE_FIFO[100]; // Ready Buffer

Scheduler_Typedef Task_Idle; // Idle Task

//==============================================================================

//------------------------------- Local Objects --------------------------------
State_Typedef Create_MSP(void);
State_Typedef Create_Task(Scheduler_Typedef *Tref);
void Init_PSP_Task(Scheduler_Typedef *Tref);
void Update_Schedular_Table(void);
void Call_SVC_Service(enum SVC_Services Service_Id);
//==============================================================================


//------------------------------- Local Objects --------------------------------
/**
 * @brief This function is used to specify the size MSP of the OS
 * @return State_Typedef    0 : Ok
 *                          1 : Not_Ok
 */
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


/**
 * @brief This Ilde Task priority 255 the last priority
 * 
 */
uint8_t IdleLed = 0;
void Idle_Task_F(void)
{
    while (1)
    {
        IdleLed ^= 1;
        __asm("wfe");
    }
    
}


/**
 * @brief This function is used to initialize the task space
 * @param Tref Structure of Task
 */
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


/**
 * @brief This function is used to run an SVC service
 * @param Service_Id Object of enum for SVC services base on @SVC_Services
 */
void Call_SVC_Service(enum SVC_Services Service_Id)
{
    switch (Service_Id)
    {
        case Activate_SVC_Service:
            __asm volatile("SVC #0x00");
            break;
        case Terminate_SVC_Service:
            __asm volatile("SVC #0x01");
            break;
        case Wait_SVC_Service:
            __asm volatile("SVC #0x02");
            break;
        case AquireMutex_SVC_Service:
            __asm volatile("SVC #0x03");
            break;
        case ReleaseMutex_SVC_Service:
            __asm volatile("SVC #0x04");
            break;    
        default:
            break;
    }
}


/**
 * @brief PendSV Handler
 */
__attribute ((naked)) void PendSv_Handler(void)
{
    // Get the Current Task Current PSP form CPU register as "CPU push xPSR, PC ..."
    Get_PSP_Add(OS_Control.Current_Task->Current_PSP);

    //________________ Save The Context of the Current Task ____________________
    OS_Control.Current_Task->Current_PSP--;
    __asm volatile("mov %0,R4" :"=r" (*(OS_Control.Current_Task->Current_PSP)) : :);
    OS_Control.Current_Task->Current_PSP--;
    __asm volatile("mov %0,R5" :"=r" (*(OS_Control.Current_Task->Current_PSP)) : :);
    OS_Control.Current_Task->Current_PSP--;
    __asm volatile("mov %0,R6" :"=r" (*(OS_Control.Current_Task->Current_PSP)) : :);
    OS_Control.Current_Task->Current_PSP--;
    __asm volatile("mov %0,R7" :"=r" (*(OS_Control.Current_Task->Current_PSP)) : :);
    OS_Control.Current_Task->Current_PSP--;
    __asm volatile("mov %0,R8" :"=r" (*(OS_Control.Current_Task->Current_PSP)) : :);
    OS_Control.Current_Task->Current_PSP--;
    __asm volatile("mov %0,R9" :"=r" (*(OS_Control.Current_Task->Current_PSP)) : :);
    OS_Control.Current_Task->Current_PSP--;
    __asm volatile("mov %0,R10" :"=r" (*(OS_Control.Current_Task->Current_PSP)) : :);
    OS_Control.Current_Task->Current_PSP--;
    __asm volatile("mov %0,R11" :"=r" (*(OS_Control.Current_Task->Current_PSP)) : :);
    //--------------------------------------------------------------------------

    // ________________ Restore The Context of The Next Task ___________________
    OS_Control.Current_Task = OS_Control.Next_Task;
    OS_Control.Next_Task = NULL;

    __asm volatile("mov R11,%0" : :"r" (*(OS_Control.Current_Task->Current_PSP)) :);
    OS_Control.Current_Task->Current_PSP++;
    __asm volatile("mov R10,%0" : :"r" (*(OS_Control.Current_Task->Current_PSP)) :);
    OS_Control.Current_Task->Current_PSP++;
    __asm volatile("mov R9,%0" : :"r" (*(OS_Control.Current_Task->Current_PSP)) :);
    OS_Control.Current_Task->Current_PSP++;
    __asm volatile("mov R8,%0" : :"r" (*(OS_Control.Current_Task->Current_PSP)) :);
    OS_Control.Current_Task->Current_PSP++;
    __asm volatile("mov R7,%0" : :"r" (*(OS_Control.Current_Task->Current_PSP)) :);
    OS_Control.Current_Task->Current_PSP++;
    __asm volatile("mov R6,%0" : :"r" (*(OS_Control.Current_Task->Current_PSP)) :);
    OS_Control.Current_Task->Current_PSP++;
    __asm volatile("mov R5,%0" : :"r" (*(OS_Control.Current_Task->Current_PSP)) :);
    OS_Control.Current_Task->Current_PSP++;
    __asm volatile("mov R4,%0" : :"r" (*(OS_Control.Current_Task->Current_PSP)) :);
    OS_Control.Current_Task->Current_PSP++;

    // Update PSP and exit 
    Set_PSP_Add(OS_Control.Current_Task->Current_PSP);
    __asm volatile("Bx LR");
    //--------------------------------------------------------------------------
}


/**
 * @brief Trigger PenSV IRQ handler
 * 
 */
void Trigger_Os_PendSV(void)
{
    SCB->ICSR |= 1UL << 28 ; // Set PendSV
}


/**
 * @brief This function is used to specify the task to be run
 */
void Decide_WhatNext(void)
{
    if((Ready_Queue.counter == 0) && (OS_Control.Current_Task->Task_State != Suspend))
    {
        OS_Control.Current_Task->Task_State = Running;
        // Add the current task again(round robin)
        FIFO_push(&Ready_Queue, OS_Control.Current_Task);
        OS_Control.Next_Task = OS_Control.Current_Task;
    }else
    {
        FIFO_pop(&Ready_Queue, &OS_Control.Next_Task);
        OS_Control.Next_Task->Task_State = Running;

        if((OS_Control.Current_Task->priority == OS_Control.Next_Task->priority) && (OS_Control.Current_Task->Task_State != Suspend))
        {
            FIFO_push(&Ready_Queue, OS_Control.Current_Task);
            OS_Control.Current_Task->Task_State = Ready;
        }
    }
}



/**
 * @brief This function is used to run SVC services
 * @param Stack_Frame   This variable takes the value of the SP before switching 
 *                      from thread mode to handler mode
 */
void OS_SVC(int *Stack_Frame)
{
    uint8_t SVC_Sevice;
    SVC_Sevice = *((uint8_t*)(((uint8_t*)Stack_Frame[6]) - 2));
    switch(SVC_Sevice)
    {
        case Activate_SVC_Service:
        case Terminate_SVC_Service:
            Update_Schedular_Table();

            if(OS_Control.OS_State == Running)
            {
                if(strcmp_(OS_Control.Current_Task->Taskname,"IdleTask",8) != 0)
                {
                    Decide_WhatNext();
                    Trigger_Os_PendSV();
                }
            }
            break;
        case Wait_SVC_Service:
            Update_Schedular_Table();
            break;
        case AquireMutex_SVC_Service:
            break;
        case ReleaseMutex_SVC_Service:
            break;    
        default:
            break;
    }
}


/**
 * @brief   This function is used to add a wait mode task based on the highest 
 *          priority to the Ready_Queue
 */
void Update_Schedular_Table(void)
{
    Scheduler_Typedef *Cur_Task = NULL;
    Scheduler_Typedef *Next_Task = NULL;
    Scheduler_Typedef *Temp = NULL;
    uint8_t counter = 0;

    while((FIFO_pop(&Ready_Queue, &Temp)) != FIFO_emypt);

    while(counter < OS_Control.NoOfActiveTasks)
    {
        Cur_Task = OS_Control.OS_Task_Table[counter];
        Next_Task = OS_Control.OS_Task_Table[counter + 1];
        if(Cur_Task->Task_State  != Suspend)
        {
            if(strcmp_(Cur_Task->Taskname,"IdleTask",8) == 0)
            {
                FIFO_push(&Ready_Queue, Cur_Task);
                Cur_Task->Task_State = Ready;
                break;
            }

            if((Cur_Task->priority) < (Next_Task->priority))
            {
                FIFO_push(&Ready_Queue, Cur_Task);
                Cur_Task->Task_State = Ready;
                break;
            }else if((Cur_Task->priority) == (Next_Task->priority))
            {
                FIFO_push(&Ready_Queue, Cur_Task);
                Cur_Task->Task_State = Ready;
            }else {break;}
        }
        counter++;
    }
}

void Check_Wait_Tasks(void)
{
    State_Typedef state = Ok;
    // int i = 0;
    for(int i = 0; i < (OS_Control.NoOfActiveTasks); i++)
    {
        if(OS_Control.OS_Task_Table[i]->Task_State == Suspend)
        {
            if(OS_Control.OS_Task_Table[i]->Block.Blocking_State == Block_Enable)
            {
                OS_Control.OS_Task_Table[i]->Block.Ticks_count--;
                if(OS_Control.OS_Task_Table[i]->Block.Ticks_count == 1)
                {
                    OS_Control.OS_Task_Table[i]->Task_State = Waiting;
                    OS_Control.OS_Task_Table[i]->Block.Blocking_State = Block_Disable;
                    Call_SVC_Service(Wait_SVC_Service);
                }
            }   
        }
    }
}


//==============================================================================


//------------------------------ Global Functions ------------------------------

/**
 * @brief This function is used to initialize the OS and create an İdle Task
 * @return State_Typedef    0 : Ok
 *                          1 : Not_Ok 
 */
State_Typedef Init_RTOS(void)
{
    State_Typedef state = Ok;

    OS_Control.OS_State = OS_Suspend;           // Update OS State (OS_suspend)
    if(Create_MSP() != Ok) {return Not_Ok;}     // Specify the MSP for OS

    if(FIFO_init(&Ready_Queue, Ready_QUEUE_FIFO, 100) != FIFO_no_Error) {return Not_Ok;}

    //Configure IDLE TASK
    __builtin_memcpy(Task_Idle.Taskname, "IdleTask", 8);
    Task_Idle.priority = 255;
    Task_Idle.f_TaskEntry = Idle_Task_F;
    Task_Idle.Task_PSP_Size = 300;

    if(Create_Task(&Task_Idle) != Ok) { return Not_Ok;}
    return state;
}


/**
 * @brief This function is used to define the task space and also to initialize it
 * @param Tref Structure of Task
 * @return State_Typedef    0 : Ok
 *                          1 : Not_Ok
 */
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
   
   
    // Sort Tasks base on priority
    BubbleSort();
   
    return state;
}


/**
 * @brief This function is used to sort tasks based on priority
 */
void BubbleSort(void)
{
    Scheduler_Typedef *Temp = NULL;
    for(uint8_t i = 0; i < OS_Control.NoOfActiveTasks - 1; i++)
    {
        for(uint8_t j = 0; j < OS_Control.NoOfActiveTasks - i - 1; j++)
        {
            if(OS_Control.OS_Task_Table[j]->priority > OS_Control.OS_Task_Table[j + 1]->priority)
            {
                Temp = OS_Control.OS_Task_Table[j];
                OS_Control.OS_Task_Table[j] = OS_Control.OS_Task_Table[j + 1];
                OS_Control.OS_Task_Table[j + 1] = Temp;
            }
        }
    }
}


/**
 * @brief 
 * @param NoTICKS 
 * @param SelfTref 
 * @return State_Typedef 
 */
State_Typedef Wait_Task(unsigned int NoTICKS,Scheduler_Typedef* Tref)
{
    Tref->Block.Blocking_State = Block_Enable;
    Tref->Block.Ticks_count = NoTICKS;
    Tref->Task_State = Suspend;
    Call_SVC_Service(Terminate_SVC_Service);
}



/**
 * @brief This function is used to activate the task
 * @param Tref structure of task
 * @return State_Typedef    0 : Ok
 *                          1 : Not_Ok 
 */
State_Typedef Activate_Task(Scheduler_Typedef* Tref)
{
    Tref->Task_State = Waiting;
    Call_SVC_Service(Activate_SVC_Service);
}


/**
 * @brief This function is used to Terminate the task
 * @param Tref structure of task
 * @return State_Typedef    0 : Ok
 *                          1 : Not_Ok 
 */
State_Typedef Terminate_Task(Scheduler_Typedef* Tref)
{
    Tref->Task_State = Suspend;
    Call_SVC_Service(Terminate_SVC_Service);
}


/**
 * @brief This function is used to activate the OS
 * @return State_Typedef    0 : Ok
 *                          1 : Not_Ok 
 */
void Activate_Os(void) 
{

    // Switch Os State to Running Mode
    OS_Control.OS_State = Running;

    OS_Control.Current_Task = &Task_Idle;
    
    // Activate Idle Task
    Activate_Task(&Task_Idle);

    // Enable Systick 1000 Ticks (1ms)
    Systick_API.Clock_Source = Processor_Clock_AHB;
    Systick_API.Current_Value = 0;
    Systick_API.Enable_Interrupt = Enable_Systick_Req;
    Systick_API.Reload_Value = 7999;
    Init_Systick();

    Set_PSP_Add(OS_Control.Current_Task->Current_PSP);
    // Switch to PSP
    Switch_SP(PSP_SP);

    // Switch to Unprivilged
    Access_level(Access_unprivileged);

    // Task_Idle.Task_State = Running;
    Task_Idle.f_TaskEntry();

}
//==============================================================================
