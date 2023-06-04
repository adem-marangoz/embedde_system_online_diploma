/**
 * @file Stm32f10xx_EXTI.c
 * @author Adem marangoz (adem.marangoz95@gmail.com)
 * @brief This source file for EXTI function definition
 * @version 0.1
 * @date 2022-05-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// ----------------------------- Include Files ---------------------------------
#include "Stm32f10xx_EXTI.h"
//==============================================================================

//----------------------------- External Objects -------------------------------
const uint16_t EXTI_Streem[16][16] = {
  {EXTI0, EXTI1, EXTI2, EXTI3, EXTI4, EXTI5, EXTI6, EXTI7, EXTI8, EXTI9, EXTI10, EXTI11, EXTI12, EXTI13, EXTI14, EXTI15},
  {EXTI0_IRQn, EXTI1_IRQn, EXTI2_IRQn, EXTI3_IRQn, EXTI4_IRQn, EXTI9_5_IRQn, EXTI9_5_IRQn ,EXTI9_5_IRQn ,EXTI9_5_IRQn ,EXTI9_5_IRQn ,EXTI15_10_IRQn ,EXTI15_10_IRQn ,EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn}
};
//==============================================================================


void (*GP_EXTI_CallBack[16])(void);
extern void EXTI15_10_Handler(void);
void Config_EXTI(St_EXTI_config *Exti_config);

/**
  * @brief  This function handles EXTI interrupt request.
  * @param[in]  GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void NVIC_EXTI_Clear_Handler(uint32_t pin)
{
    EXTI->EXTI_RP |= 1U << pin;
}


void Init_EXTI(St_EXTI_config *Exti_config)
{
  Config_EXTI(Exti_config);
}

/**
  * @brief  Reset Interrupt Registers and NVIC.
  * @retval None
  */
void Deinit_EXTI(void)
{
  // Reset EXTI registers in EXTI peripheral
  EXTI->EXTI_EMR = 0x00000000U;
  EXTI->EXTI_FTSR = 0x00000000U;
  EXTI->EXTI_IMR = 0x00000000U;
  EXTI->EXTI_RP = 0x00000000U;
  EXTI->EXTI_RTSR = 0x00000000U;
  EXTI->EXTI_SWIER = 0x00000000U;

  // Reset NVIC register in Cortex M3 
  NVIC->ICER[0] |= 1 << 6;
  NVIC->ICER[0] |= 1 << 7;
  NVIC->ICER[0] |= 1 << 8;
  NVIC->ICER[0] |= 1 << 9;
  NVIC->ICER[0] |= 1 << 10;
  NVIC->ICER[0] |= 1 << 23;
  NVIC->ICER[1] |= 1 << 8;

}


void Upadate_EXTI(St_EXTI_config *Exti_config)
{
  Config_EXTI(Exti_config);
}


void Config_EXTI(St_EXTI_config *Exti_config)
{
  GPIO_InitTypeDef gpio_config = {0};
  gpio_config.Pull = GPIO_NOPULL;
  gpio_config.Mode = GPIO_MODE_IT_RISING_FALLING; // GPIO MODE INPUT FLOATING
  gpio_config.Pin = Exti_config->EXTI_Pin.pin;
  Init_GPIO(Exti_config->EXTI_Pin.GPIO_port,&gpio_config);

  EXTI->EXTI_FTSR &= ~(1 << Exti_config->EXTI_Pin.Line);
  EXTI->EXTI_RTSR &= ~(1 << Exti_config->EXTI_Pin.Line);

  if(Exti_config->EXTI_Trigger == RISING_EDGE_Trigger)
    EXTI->EXTI_RTSR |= (1 << Exti_config->EXTI_Pin.Line);
  else if(Exti_config->EXTI_Trigger == FALLING_EDGE_Trigger)
    EXTI->EXTI_FTSR |= (1 << Exti_config->EXTI_Pin.Line);
  else
  {
    EXTI->EXTI_FTSR |= (1 << Exti_config->EXTI_Pin.Line);
    EXTI->EXTI_RTSR |= (1 << Exti_config->EXTI_Pin.Line);
  }
  NVIC_Enable_IRQ(Exti_config->EXTI_Pin.IRQn_number);
  GP_EXTI_CallBack[Exti_config->EXTI_Pin.Line] = Exti_config->P_IRQ_CallBack;

  if(Exti_config->EXTI_State == EXTI_Enable)
  {
    EXTI->EXTI_IMR |= Exti_config->EXTI_Pin.pin;
    NVIC_Enable_IRQ(Exti_config->EXTI_Pin.Line);
  }else
  {
    EXTI->EXTI_IMR &= ~(Exti_config->EXTI_Pin.pin);
    NVIC_Disable_IRQ(Exti_config->EXTI_Pin.Line);
  }
}



/**
  * @brief  Enables a device specific interrupt in the NVIC interrupt controller.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (stm32f10xxx.h))
  * @retval None
  */
void NVIC_Enable_IRQ(IRQn_Type IRQn)
{
  /* Enable interrupt */
  NVIC_EnableIRQ(IRQn);
}

/**
  * @brief  Disable a device specific interrupt in the NVIC interrupt controller.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (stm32f10xxx.h))
  * @retval None
  */
void NVIC_Disable_IRQ(IRQn_Type IRQn)
{
  /* Disable interrupt */
  NVIC_DisableIRQ(IRQn);
}

/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_Handler(void)
{
  NVIC_EXTI_Clear_Handler(1 << EXTI0);
  GP_EXTI_CallBack[EXTI0]();
}

/**
  * @brief This function handles EXTI line1 interrupt.
  */
void EXTI1_Handler(void)
{
  NVIC_EXTI_Clear_Handler(1 << EXTI1);
  GP_EXTI_CallBack[EXTI1]();
}

/**
  * @brief This function handles EXTI line2 interrupt.
  */
void EXTI2_Handler(void)
{
  NVIC_EXTI_Clear_Handler(1 << EXTI2);
  GP_EXTI_CallBack[EXTI2]();
}

/**
  * @brief This function handles EXTI line3 interrupt.
  */
void EXTI3_Handler(void)
{
  NVIC_EXTI_Clear_Handler(1 << EXTI3);
  GP_EXTI_CallBack[EXTI3]();
}

/**
  * @brief This function handles EXTI line4 interrupt.
  */
void EXTI4_Handler(void)
{
  NVIC_EXTI_Clear_Handler(1 << EXTI4);
  GP_EXTI_CallBack[EXTI4]();
}

/**
  * @brief This function handles EXTI line9_5 interrupt.
  */
void EXTI9_5_Handler(void)
{
  if(EXTI->EXTI_RP & 1 << EXTI5) { EXTI->EXTI_RP |= (1 << EXTI5); GP_EXTI_CallBack[EXTI5](); }
  if(EXTI->EXTI_RP & 1 << EXTI6) { EXTI->EXTI_RP |= (1 << EXTI6); GP_EXTI_CallBack[EXTI6](); }
  if(EXTI->EXTI_RP & 1 << EXTI7) { EXTI->EXTI_RP |= (1 << EXTI7); GP_EXTI_CallBack[EXTI7](); }
  if(EXTI->EXTI_RP & 1 << EXTI8) { EXTI->EXTI_RP |= (1 << EXTI8); GP_EXTI_CallBack[EXTI8](); }
  if(EXTI->EXTI_RP & 1 << EXTI9) { EXTI->EXTI_RP |= (1 << EXTI9); GP_EXTI_CallBack[EXTI9](); }
}

/**
  * @brief This function handles EXTI line15_10 interrupt.
  */
void EXTI15_10_Handler(void)
{
  if(EXTI->EXTI_RP & 1 << EXTI10)
  {
    EXTI->EXTI_RP |= (1 << EXTI10); 
    GP_EXTI_CallBack[EXTI10](); 
  }
  if(EXTI->EXTI_RP & 1 << EXTI11) 
  { 
    EXTI->EXTI_RP |= (1 << EXTI11);
    GP_EXTI_CallBack[EXTI11](); 
  }
  if(EXTI->EXTI_RP & 1 << EXTI12) 
  { 
    EXTI->EXTI_RP |= (1 << EXTI12); 
    GP_EXTI_CallBack[EXTI12](); 
  }
  if(EXTI->EXTI_RP & 1 << EXTI13) 
  { 
    EXTI->EXTI_RP |= (1 << EXTI13); 
    GP_EXTI_CallBack[EXTI13](); 
  }
  if(EXTI->EXTI_RP & 1 << EXTI14) 
  { 
    EXTI->EXTI_RP |= (1 << EXTI14); 
    GP_EXTI_CallBack[EXTI14](); 
  }
  if(EXTI->EXTI_RP & 1 << EXTI15) 
  { 
    EXTI->EXTI_RP |= (1 << EXTI15); 
    GP_EXTI_CallBack[EXTI15](); 
  }
}