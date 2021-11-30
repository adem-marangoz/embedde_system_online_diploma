/*
*@author 	Adem Alnajjar
*@data		24.11.2021
*/
#include <stdio.h>
//#include "Platform_Types.h"
typedef volatile unsigned int vuint32_t;
#define RCC_BASE 				0x40021000
#define GPIOA_BASE	   			0x40010800

#define RCC_APB2ENR	    		*(volatile uint32_t*)(RCC_BASE +0x18) 	//Rest Clock Control Register
#define GPIOA_CRH				*(volatile uint32_t*)(GPIOA_BASE+0x04) 	//GPIOA Register Mode
#define GPIOA_ODR				*(volatile uint32_t*)(RCC_BASE+0x0C) 		//GPIOA Output State Register

#define RCC_IOPAEN      (1<<2)
#define GPIOA13         (1UL<<13)

typedef union	{
	vuint32_t	all_fields;
    struct
    {
    	volatile uint32_t reserved :13;
    	volatile uint32_t P_13:1;
    }PIN;
}R_ODR_t;

volatile R_ODR_t* R_ODR=(volatile R_ODR_t*)(GPIOA_BASE + 0X0C);
unsigned char g_var[3]={1,2,3};
unsigned char const const_char_var[3]={1,2,3};
unsigned char bss_var[3];

int main(void)
{
    RCC_APB2ENR |=	RCC_IOPAEN;
    GPIOA_CRH   &=	0XFF0FFFFF;
    GPIOA_CRH   |=	0X00200000;
    while (1)
    {
        R_ODR->PIN.P_13=1; 				//Set Pin 13 GPIOA
        for(int i=0;i<5000;i++);	//Delay
        R_ODR->PIN.P_13=0;				//Reset Pin 13 GPIOA
        for(int i=0;i<5000;i++);	//Delay
    }

}