/**
 * @file startup.c
 * @author Adem Alnajjar (Adem.marangoz95@domain.com)
 * @brief startup stm32f103c with startup c file
 * @version 0.1
 * @date 2021-11-30
 * @copyright Copyright (c) 2021
 */

#include <stdint.h>
#define STACK_Start_SP	0x20001000
extern int main(void);

void Rest_Handler(void)
{
	main();
}

void NMI_Handler(void)
{
	Rest_Handler();
}

void Hard_Fualt_Handler(void)
{
	Rest_Handler();
}

void Bus_Fault_Handler(void)
{
	Rest_Handler();
}

void Usage_Fault_Handler(void)
{
	Rest_Handler();
}

uint32_t vectors[] __attribute__((section(".vectors"))) = {
			STACK_Start_SP,
			(uint32_t) &Rest_Handler,
			(uint32_t) &NMI_Handler,
			(uint32_t) &Hard_Fualt_Handler,
			(uint32_t) &Bus_Fault_Handler,
			(uint32_t) &Usage_Fault_Handler
};