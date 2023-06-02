/*
*@author 	Adem Alnajjar
*@data		24.11.2021
*/

//_________________________________ Include Files ______________________________
#include "Application.h"
#include "Stm32f10xx_Common.h"
#include "Scheduler.h"
#include <string.h>
#include "Stm32f10xx_EXTI.h"
//==============================================================================

//______________________________ Generic Macro _________________________________


//==============================================================================

//------------------------------- Local Objects --------------------------------

Scheduler_Typedef Task1, Task2, Task3, Task4, Task5;

void Task_1(void);
void Task_2(void);
void Task_3(void);
void Task_4(void);
void Task_5(void);
//==============================================================================
uint8_t Led1 = 0,Led2 = 0, Led3 = 0, Led4= 0;

void Task_1(void)
{
    static uint32_t counter1 = 0;
    while (1)
    {
        Led1 ^= 1;
        // counter1++;
        // if(counter1 == 0xF)
        // {
        //     counter1 = 0;
        //     Activate_Task(&Task4);
        // }
    }
}


void Task_2(void)
{
    while (1)
    {
        Led2 ^= 1;
    }
}


void Task_3(void)
{
    while (1)
    {
        Led3 ^= 1;
    }
}


void Task_4(void)
{
    static uint32_t counter = 0;
    while (1)
    {
        Led4 ^= 1;
        counter++;
        if(counter == 10)
        {
            counter = 0;
            Terminate_Task(&Task4);
        }
    }
}



int main(void)
{

    config_Drives_and_Perpherals();
    if(Init_RTOS() != Ok) {while(1);}

    Task1.priority = 3;
    Task1.f_TaskEntry = Task_1;
    Task1.Task_PSP_Size = 2000;
    __builtin_memcpy(Task1.Taskname,"Task 1", 6);
    if(Create_Task(&Task1) != Ok) {while(1);}
    
    Task2.priority = 3;
    Task2.f_TaskEntry = Task_2;
    Task2.Task_PSP_Size = 2000;
    __builtin_memcpy(Task2.Taskname,"Task 2", 6);
    if(Create_Task(&Task2) != Ok) {while(1);}
    
    Task3.priority = 3;
    Task3.f_TaskEntry = Task_3;
    Task3.Task_PSP_Size = 2000;
    __builtin_memcpy(Task3.Taskname,"Task 3", 6);
    if(Create_Task(&Task3) != Ok) {while(1);}
    
    Task4.priority = 1;
    Task4.f_TaskEntry = Task_4;
    Task4.Task_PSP_Size = 2000;
    __builtin_memcpy(Task4.Taskname,"Task 4", 6);
    if(Create_Task(&Task4) != Ok) {while(1);}
    

    Activate_Task(&Task1);
    Activate_Task(&Task2);
    Activate_Task(&Task3);
    Activate_Os();
    Infinite_loop();

    return 1;
}
