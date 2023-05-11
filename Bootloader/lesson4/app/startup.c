/**
 * @file startup.c
 * @author Adem Alnajjar (Adem.marangoz95@gmail.com)
 * @brief startup stm32f103c with startup c file
 * @version 0.1
 * @date 2021-11-30
 * @copyright Copyright (c) 2021
 */

#include <stdint.h>
#include "Stm32f10xx_Address.h"
#define STACK_Start_SP			0x20001000
#define USER_IVT_OFFSET			1
#define FLASH_BASE            	0x08000000UL /*!< FLASH base address in the alias region */
#define VECT_TAB_OFFSET       	0x00004400U
extern unsigned int _stack_top;
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

void NMI_Handler(void)__attribute((weak,alias("Default_Handler")));;
void Hard_Fault_Handler(void)__attribute((weak,alias("Default_Handler")));;
void MM_Fault_Handler(void)__attribute((weak,alias("Default_Handler")));;
void Bus_Fault_Handler(void)__attribute((weak,alias("Default_Handler")));;
void Usage_Fault_Handler(void)__attribute((weak,alias("Default_Handler")));;
void SVCall_Handler(void)__attribute((weak,alias("Default_Handler")));;
void DebugMonitor_Handler(void)__attribute((weak,alias("Default_Handler")));;
void PendSv_Handler(void)__attribute((weak,alias("Default_Handler")));;
void SysTick_Handler(void)__attribute((weak,alias("Default_Handler")));;
void WWDG_Handler(void)__attribute((weak,alias("Default_Handler")));;
void PVD_Handler(void)__attribute((weak,alias("Default_Handler")));;
void TEMPER_Handler(void)__attribute((weak,alias("Default_Handler")));;
void RTC_Handler(void)__attribute((weak,alias("Default_Handler")));;
void FLASH_Handler(void)__attribute((weak,alias("Default_Handler")));;
void RCC_Handler(void)__attribute((weak,alias("Default_Handler")));;
void EXTI0_Handler(void)__attribute((weak,alias("Default_Handler")));;
void EXTI1_Handler(void)__attribute((weak,alias("Default_Handler")));;
void EXTI2_Handler(void)__attribute((weak,alias("Default_Handler")));;
void EXTI3_Handler(void)__attribute((weak,alias("Default_Handler")));;
void EXTI4_Handler(void)__attribute((weak,alias("Default_Handler")));;
void DMA1_Channel1_Handler(void)__attribute((weak,alias("Default_Handler")));;
void DMA1_Channel2_Handler(void)__attribute((weak,alias("Default_Handler")));;
void DMA1_Channel3_Handler(void)__attribute((weak,alias("Default_Handler")));;
void DMA1_Channel4_Handler(void)__attribute((weak,alias("Default_Handler")));;
void DMA1_Channel5_Handler(void)__attribute((weak,alias("Default_Handler")));;
void DMA1_Channel6_Handler(void)__attribute((weak,alias("Default_Handler")));;
void DMA1_Channel7_Handler(void)__attribute((weak,alias("Default_Handler")));;
void ADC1_2_Handler(void)__attribute((weak,alias("Default_Handler")));;         
void USB_HP_CAN1_TX_Handler(void)__attribute((weak,alias("Default_Handler")));;
void USB_LP_CAN1_RX0_Handler(void)__attribute((weak,alias("Default_Handler")));;
void CAN1_RX1_Handler(void)__attribute((weak,alias("Default_Handler")));;
void CAN1_SCE_Handler(void)__attribute((weak,alias("Default_Handler")));;
void EXTI9_5_Handler(void)__attribute((weak,alias("Default_Handler")));;
void TIM1_BRK_Handler(void)__attribute((weak,alias("Default_Handler")));;
void TIM1_UP_Handler(void)__attribute((weak,alias("Default_Handler")));;
void TIM1_TRG_COM_Handler(void)__attribute((weak,alias("Default_Handler")));;
void TIM1_CC_Handler(void)__attribute((weak,alias("Default_Handler")));;
void TIM2_Handler(void)__attribute((weak,alias("Default_Handler")));;
void TIM3_Handler(void)__attribute((weak,alias("Default_Handler")));;
void TIM4_Handler(void)__attribute((weak,alias("Default_Handler")));;
void I2C1_EV_Handler(void)__attribute((weak,alias("Default_Handler")));;
void I2C1_ER_Handler(void)__attribute((weak,alias("Default_Handler")));;
void I2C2_EV_Handler(void)__attribute((weak,alias("Default_Handler")));;
void I2C2_ER_Handler(void)__attribute((weak,alias("Default_Handler")));;
void SPI1_Handler(void)__attribute((weak,alias("Default_Handler")));;
void SPI2_Handler(void)__attribute((weak,alias("Default_Handler")));;
void USART1_Handler(void)__attribute((weak,alias("Default_Handler")));;
void USART2_Handler(void)__attribute((weak,alias("Default_Handler")));;
void USART3_Handler(void)__attribute((weak,alias("Default_Handler")));;
void EXTI15_10_Handler(void)__attribute((weak,alias("Default_Handler")));;
void RTC_Alarm_Handler(void)__attribute((weak,alias("Default_Handler")));;
void USBWakeUp_Handler(void)__attribute((weak,alias("Default_Handler")));;

uint32_t vectors[] __attribute__((section(".vectors"))) = {
			(uint32_t) &_stack_top,
			(uint32_t) &Rest_Handler,
			(uint32_t) &NMI_Handler,
			(uint32_t) &Hard_Fault_Handler,
			(uint32_t) &MM_Fault_Handler,
			(uint32_t) &Bus_Fault_Handler,
			(uint32_t) &Usage_Fault_Handler,
			(uint32_t) &Default_Handler,
			(uint32_t) &Default_Handler,
			(uint32_t) &Default_Handler,
			(uint32_t) &Default_Handler,
			(uint32_t) &SVCall_Handler,
			(uint32_t) &DebugMonitor_Handler,
			(uint32_t) &Default_Handler,
			(uint32_t) &PendSv_Handler,
			(uint32_t) &SysTick_Handler,
			(uint32_t) &WWDG_Handler,
			(uint32_t) &PVD_Handler,
			(uint32_t) &TEMPER_Handler,
			(uint32_t) &RTC_Handler,
			(uint32_t) &FLASH_Handler,
			(uint32_t) &RCC_Handler,
			(uint32_t) &EXTI0_Handler,
			(uint32_t) &EXTI1_Handler,
			(uint32_t) &EXTI2_Handler,
			(uint32_t) &EXTI3_Handler,
			(uint32_t) &EXTI4_Handler,
			(uint32_t) &DMA1_Channel1_Handler,
			(uint32_t) &DMA1_Channel2_Handler,
			(uint32_t) &DMA1_Channel3_Handler,
			(uint32_t) &DMA1_Channel4_Handler,
			(uint32_t) &DMA1_Channel5_Handler,
			(uint32_t) &DMA1_Channel6_Handler,
			(uint32_t) &DMA1_Channel7_Handler,
			(uint32_t) &ADC1_2_Handler,
			(uint32_t) &USB_HP_CAN1_TX_Handler,
			(uint32_t) &USB_LP_CAN1_RX0_Handler,
			(uint32_t) &CAN1_RX1_Handler,
			(uint32_t) &CAN1_SCE_Handler,
			(uint32_t) &EXTI9_5_Handler,
			(uint32_t) &TIM1_BRK_Handler,
			(uint32_t) &TIM1_UP_Handler,
			(uint32_t) &TIM1_TRG_COM_Handler,
			(uint32_t) &TIM1_CC_Handler,
			(uint32_t) &TIM2_Handler,
			(uint32_t) &TIM3_Handler,
			(uint32_t) &TIM4_Handler,
			(uint32_t) &I2C1_EV_Handler,
			(uint32_t) &I2C1_ER_Handler,
			(uint32_t) &I2C2_EV_Handler,
			(uint32_t) &I2C2_ER_Handler,
			(uint32_t) &SPI1_Handler,
			(uint32_t) &SPI2_Handler,
			(uint32_t) &USART1_Handler,
			(uint32_t) &USART2_Handler,			
			(uint32_t) &USART3_Handler,
			(uint32_t) &EXTI15_10_Handler,
			(uint32_t) &RTC_Alarm_Handler,
			(uint32_t) &USBWakeUp_Handler,
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
	#if (USER_IVT_OFFSET == 1)
		SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM. */
	#endif 
	main();
}