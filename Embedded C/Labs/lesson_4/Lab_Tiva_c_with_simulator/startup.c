/**
 * @file startup.c
 * @author Adem Alnajjar (Adem.marangoz95@domain.com)
 * @brief startup stm32f103c with startup c file
 * @version 0.1
 * @date 2021-11-30
 * @copyright Copyright (c) 2021
 */

#include <stdint.h>
extern unsigned int _S_DATA;
extern unsigned int _E_DATA;
extern unsigned int _S_bss;
extern unsigned int _E_bss;
extern unsigned int _E_text;
extern int main(void);


void Rest_Handler(void);

void Default_Handler()
{
	Rest_Handler();
}
static unsigned long Stack_top[256]; // The top of stack in sram 256*4=1024



void NMI_Handler(void)__attribute((weak,alias("Default_Handler")));;
void Hard_Fault_Handler(void)__attribute((weak,alias("Default_Handler")));;
void MM_Fault_Handler(void)__attribute((weak,alias("Default_Handler")));;
void Bus_Fault_Handler(void)__attribute((weak,alias("Default_Handler")));;
void Usage_Fault_Handler(void)__attribute((weak,alias("Default_Handler")));;


void (* const g_p_fn_Vectors[])() __attribute__((section(".vectors"))) =
{
	(void (*)())	((unsigned long)Stack_top + sizeof(Stack_top)),
	&Rest_Handler,
	&NMI_Handler,
	&Hard_Fault_Handler,
	&MM_Fault_Handler,
	&Bus_Fault_Handler,
	&Usage_Fault_Handler
};


void Rest_Handler(void)
{
	//Copy Data form ROM To RAM
	unsigned int DATA_size=(unsigned char*)&_E_DATA - (unsigned char*)&_S_DATA ;
	unsigned char* P_src=(unsigned char*)&_E_text ;
	unsigned char* P_dst=(unsigned char*)&_S_DATA ;

	for(int i=0; i<DATA_size;i++)
	{
		*((unsigned char*)P_dst++)=*((unsigned char*)P_src++) ;
	}

	//Init The .bss with Zero
	unsigned int bss_size=(unsigned char*)&_E_bss -(unsigned char*)&_S_bss ;
	P_dst=(unsigned char*)&_S_bss ;
	for(int i=0;i<bss_size;i++)
	{
		*((unsigned char*)P_dst++)==(unsigned char)0 ;
	}
	main();
}