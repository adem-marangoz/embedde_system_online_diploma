/*
*@author 	Adem Alnajjar
*@data		24.11.2021
*/

//_________________________________ Include Files ______________________________
#include "Application.h"
#include "Stm32f10xx_Common.h"
#include "Scheduler.h"
#include <string.h>
//==============================================================================

//______________________________ Generic Macro _________________________________


//==============================================================================

//------------------------------- Local Objects --------------------------------

Scheduler_Typedef Task1, Task2, Task3, Task4;

void Task_1(void);
void Task_2(void);
void Task_3(void);
void Task_4(void);
//==============================================================================

void Task_1(void)
{
    while (1)
    {
        __asm("nop");
    }
}


void Task_2(void)
{
    while (1)
    {
        __asm("nop");
    }
}


void Task_3(void)
{
    while (1)
    {
        __asm("nop");
    }
}


void Task_4(void)
{
    while (1)
    {
        __asm("nop");
    }
}


int main(void)
{

    // config_Drives_and_Perpherals(); // config Drives and Peripherals  
    
    if(MYRTOS_init() != Ok) {while(1);}

    Task1.priority = 3;
    Task1.f_TaskEntry = Task_1;
    Task1.Task_PSP_Size = 1024;
    __builtin_memcpy(Task1.Taskname,"Task 1", 6);
    if(Create_Task(&Task1) != Ok) {while(1);}
    
    Task2.priority = 3;
    Task2.f_TaskEntry = Task_2;
    Task2.Task_PSP_Size = 1024;
    __builtin_memcpy(Task2.Taskname,"Task 2", 6);
    if(Create_Task(&Task2) != Ok) {while(1);}
    
    Task3.priority = 3;
    Task3.f_TaskEntry = Task_1;
    Task3.Task_PSP_Size = 1024;
    __builtin_memcpy(Task3.Taskname,"Task 3", 6);
    if(Create_Task(&Task3) != Ok) {while(1);}
    
    Task4.priority = 3;
    Task4.f_TaskEntry = Task_1;
    Task4.Task_PSP_Size = 1024;
    __builtin_memcpy(Task4.Taskname,"Task 4", 6);
    if(Create_Task(&Task4) != Ok) {while(1);}

    
    Infinite_loop();

    return 1;
}
