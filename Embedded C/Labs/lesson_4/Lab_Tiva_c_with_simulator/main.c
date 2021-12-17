/*
*@author 	Adem Alnajjar
*@data		24.11.2021
*/
#include <stdio.h>
//#include "Platform_Types.h"
#define SYSCTL_RCGC2_R                  (*((volatile unsigned long*)(0x400FE108)))
#define GPIO_PROTF_DATA_R               (*((volatile unsigned long*)(0x400253FC)))
#define GPIO_PROTF_DIR_R                (*((volatile unsigned long*)(0x40025400)))
#define GPIO_PROTF_DEN_R                (*((volatile unsigned long*)(0x4002551C)))



int main(void)
{
    volatile uint32_t delay_counter;
    SYSCTL_RCGC2_R = 0x20;
    for(delay_counter=0;delay_counter<300;delay_counter++);
    GPIO_PROTF_DIR_R|=1<<3;
	GPIO_PROTF_DEN_R|=1<<3;

    while(1)
    {
        GPIO_PROTF_DATA_R |= 1<<3;
        for(delay_counter=0;delay_counter<200000;delay_counter++);
        GPIO_PROTF_DATA_R &= ~(1<<3);
        for(delay_counter=0;delay_counter<200000;delay_counter++);
    }
    return 0;
}