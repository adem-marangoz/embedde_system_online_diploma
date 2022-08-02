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

#include "Stm32f10xx_EXTI.h"

/**
  * @brief  This function handles EXTI interrupt request.
  * @param[in]  GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void EXTI_EXTI_Clear_Handler(uint32_t pin)
{
    EXTI->EXTI_RP |= 1U << pin;
}