/**
 * @file Stm32f10xx_Timers.c
 * @author adem alnajjar (adem.alnajjar95@gmail.com)
 * @brief Timers Drivers
 * @version 0.1
 * @date 2022-10-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//------------------------------- Include Files --------------------------------
#include "Stm32f10xx_Timers.h"
#include "Stm32f10xx_RCC.h"
//==============================================================================


//------------------------------ Global Functions ------------------------------
ST_Timers_API tim1_config;

/**
 * @brief This function to initialization Timer
 * @param Timx data Structure for Timer API
 */
void Init_Timer(ST_Timers_API *Timx)
{
    __APB2ENR_TIM1EN_En();
    Timx->Instance->TIM_PSC = Timx->Prescaler;
    Timx->Instance->TIM_ARR = Timx->Period;
    Timx->Instance->TIM_CR1 |= Timx->ClockDivision | Timx->AutoReloadPreload | Timx->CounterMode;
    Timx->Instance->TIM_RCR = Timx->RepetitionCounter;
    Timx->Instance->TIM_EGR |= TIM_EGR_UG;
}


/**
 * @brief This Function used to delay
 * @param Timx data Structure for Timer API
 * @param delay Delay value
 */
// void delay_us(ST_Timers_API *Timx, uint16_t delay)
// {
//     // __HAL_TIM_ENABLE(Timx);
// 	__HAL_TIM_SET_COUNTER(Timx, 0);
// 	while(__HAL_TIM_GET_COUNTER(Timx) < delay);	
//     // __HAL_TIM_DISABLE(Timx);
// }
//==============================================================================


