/**
 * @file Stm32f10xx_Timers.h
 * @author adem alnajjar (Adem.alnajjar@gmail.com)
 * @brief Timers Drivers
 * @version 0.1
 * @date 2022-10-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef STM32F10XX_TIMERS_H_
#define STM32F10XX_TIMERS_H_

//------------------------------ Include Files ---------------------------------
#include "Stm32f10xx_Address.h"
#include "Stm32f10xx_Common.h"
//==============================================================================

//----------------------------- Generaic Objects -------------------------------
#define TIM_CR1_CKD_Pos                                 (8U)                               
#define TIM_CR1_CKD_Msk                                 (0x3UL << TIM_CR1_CKD_Pos)          /*!< 0x00000300 */
#define TIM_CR1_CKD                                     TIM_CR1_CKD_Msk                    /*!<CKD[1:0] bits (clock division) */
#define TIM_CR1_CKD_0                                   (0x1UL << TIM_CR1_CKD_Pos)          /*!< 0x00000100 */
#define TIM_CR1_CKD_1                                   (0x2UL << TIM_CR1_CKD_Pos)          /*!< 0x00000200 */

#define TIM_CR1_DIR_Pos                                 (4U)                               
#define TIM_CR1_DIR_Msk                                 (0x1UL << TIM_CR1_DIR_Pos)          /*!< 0x00000010 */
#define TIM_CR1_DIR                                     TIM_CR1_DIR_Msk                    /*!<Direction */

#define TIM_CR1_CMS_Pos                                 (5U)                               
#define TIM_CR1_CMS_Msk                                 (0x3UL << TIM_CR1_CMS_Pos)          /*!< 0x00000060 */
#define TIM_CR1_CMS                                     TIM_CR1_CMS_Msk                    /*!<CMS[1:0] bits (Center-aligned mode selection) */
#define TIM_CR1_CMS_0                                   (0x1UL << TIM_CR1_CMS_Pos)          /*!< 0x00000020 */
#define TIM_CR1_CMS_1                                   (0x2UL << TIM_CR1_CMS_Pos)          /*!< 0x00000040 */

#define TIM_CR1_ARPE_Pos                                (7U)                               
#define TIM_CR1_ARPE_Msk                                (0x1UL << TIM_CR1_ARPE_Pos)         /*!< 0x00000080 */
#define TIM_CR1_ARPE                                    TIM_CR1_ARPE_Msk                   /*!<Auto-reload preload enable */

#define TIM_EGR_UG_Pos                                  (0U)                               
#define TIM_EGR_UG_Msk                                  (0x1UL << TIM_EGR_UG_Pos)           /*!< 0x00000001 */
#define TIM_EGR_UG                                      TIM_EGR_UG_Msk                     /*!<Update Generation */

#define TIM_CR1_CEN_Pos                                 (0U)                               
#define TIM_CR1_CEN_Msk                                 (0x1UL << TIM_CR1_CEN_Pos)          /*!< 0x00000001 */
#define TIM_CR1_CEN                                     TIM_CR1_CEN_Msk                    /*!<Counter enable */

#define TIM_CCER_CC1E_Pos                               (0U)                               
#define TIM_CCER_CC1E_Msk                               (0x1UL << TIM_CCER_CC1E_Pos)        /*!< 0x00000001 */
#define TIM_CCER_CC1E                                   TIM_CCER_CC1E_Msk                  /*!<Capture/Compare 1 output enable */

#define TIM_CCER_CC2E_Pos                               (4U)                               
#define TIM_CCER_CC2E_Msk                               (0x1UL << TIM_CCER_CC2E_Pos)        /*!< 0x00000010 */
#define TIM_CCER_CC2E                                   TIM_CCER_CC2E_Msk                  /*!<Capture/Compare 2 output enable */

#define TIM_CCER_CC3E_Pos                               (8U)                               
#define TIM_CCER_CC3E_Msk                               (0x1UL << TIM_CCER_CC3E_Pos)        /*!< 0x00000100 */
#define TIM_CCER_CC3E                                   TIM_CCER_CC3E_Msk                  /*!<Capture/Compare 3 output enable */

#define TIM_CCER_CC4E_Pos                               (12U)                              
#define TIM_CCER_CC4E_Msk                               (0x1UL << TIM_CCER_CC4E_Pos)        /*!< 0x00001000 */
#define TIM_CCER_CC4E                                   TIM_CCER_CC4E_Msk                  /*!<Capture/Compare 4 output enable */

#define TIM_CCER_CC1NE_Pos                              (2U)                               
#define TIM_CCER_CC1NE_Msk                              (0x1UL << TIM_CCER_CC1NE_Pos)       /*!< 0x00000004 */
#define TIM_CCER_CC1NE                                  TIM_CCER_CC1NE_Msk                 /*!<Capture/Compare 1 Complementary output enable */

#define TIM_CCER_CC2NE_Pos                              (6U)                               
#define TIM_CCER_CC2NE_Msk                              (0x1UL << TIM_CCER_CC2NE_Pos)       /*!< 0x00000040 */
#define TIM_CCER_CC2NE                                  TIM_CCER_CC2NE_Msk                 /*!<Capture/Compare 2 Complementary output enable */

#define TIM_CCER_CC3NE_Pos                              (10U)                              
#define TIM_CCER_CC3NE_Msk                              (0x1UL << TIM_CCER_CC3NE_Pos)       /*!< 0x00000400 */
#define TIM_CCER_CC3NE                                  TIM_CCER_CC3NE_Msk                 /*!<Capture/Compare 3 Complementary output enable */




/** @defgroup TIM_Private_Constants TIM Private Constants
  * @{
  */
/* The counter of a timer instance is disabled only if all the CCx and CCxN
   channels have been disabled */
#define TIM_CCER_CCxE_MASK  ((uint32_t)(TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E))
#define TIM_CCER_CCxNE_MASK ((uint32_t)(TIM_CCER_CC1NE | TIM_CCER_CC2NE | TIM_CCER_CC3NE))



/** @defgroup TIM_Counter_Mode TIM Counter Mode
  * @{
  */
#define TIM_COUNTERMODE_UP                              0x00000000U                          /*!< Counter used as up-counter   */
#define TIM_COUNTERMODE_DOWN                            TIM_CR1_DIR                          /*!< Counter used as down-counter */
#define TIM_COUNTERMODE_CENTERALIGNED1                  TIM_CR1_CMS_0                        /*!< Center-aligned mode 1        */
#define TIM_COUNTERMODE_CENTERALIGNED2                  TIM_CR1_CMS_1                        /*!< Center-aligned mode 2        */
#define TIM_COUNTERMODE_CENTERALIGNED3                  TIM_CR1_CMS                          /*!< Center-aligned mode 3        */

/** @defgroup TIM_ClockDivision TIM Clock Division
  * @{
  */
#define TIM_CLOCKDIVISION_DIV1                          0x00000000U                          /*!< Clock division: tDTS=tCK_INT   */
#define TIM_CLOCKDIVISION_DIV2                          TIM_CR1_CKD_0                        /*!< Clock division: tDTS=2*tCK_INT */
#define TIM_CLOCKDIVISION_DIV4                          TIM_CR1_CKD_1                        /*!< Clock division: tDTS=4*tCK_INT */

/** @defgroup TIM_AutoReloadPreload TIM Auto-Reload Preload
  * @{
  */
#define TIM_AUTORELOAD_PRELOAD_DISABLE                  0x00000000U               /*!< TIMx_ARR register is not buffered */
#define TIM_AUTORELOAD_PRELOAD_ENABLE                   TIM_CR1_ARPE              /*!< TIMx_ARR register is buffered */


/**
  * @brief  Set the TIM Counter Register value on runtime.
  * @param  __HANDLE__ TIM handle.
  * @param  __COUNTER__ specifies the Counter register new value.
  * @retval None
  */
#define __HAL_TIM_SET_COUNTER(__HANDLE__, __COUNTER__)  ((__HANDLE__)->Instance->TIM_CNT = (__COUNTER__))

/**
  * @brief  Get the TIM Counter Register value on runtime.
  * @param  __HANDLE__ TIM handle.
  * @retval 16-bit or 32-bit value of the timer counter register (TIMx_CNT)
  */
#define __HAL_TIM_GET_COUNTER(__HANDLE__)  ((__HANDLE__)->Instance->TIM_CNT)


/**
  * @brief  Enable the TIM peripheral.
  * @param  __HANDLE__ TIM handle
  * @retval None
  */
#define __HAL_TIM_ENABLE(__HANDLE__)                 ((__HANDLE__)->Instance->TIM_CR1|=(TIM_CR1_CEN))

/**
  * @brief  Disable the TIM peripheral.
  * @param  __HANDLE__ TIM handle
  * @retval None
  */
#define __HAL_TIM_DISABLE(__HANDLE__) \
  do { \
    if (((__HANDLE__)->Instance->TIM_CCER & TIM_CCER_CCxE_MASK) == 0UL) \
    { \
      if(((__HANDLE__)->Instance->TIM_CCER & TIM_CCER_CCxNE_MASK) == 0UL) \
      { \
        (__HANDLE__)->Instance->TIM_CR1 &= ~(TIM_CR1_CEN); \
      } \
    } \
  } while(0)


typedef struct 
{
    St_Timers_Typedef *Instance;
    
    uint32_t Prescaler;         /*!< Specifies the prescaler value used to divide the TIM clock.
                                   This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF */

    uint32_t CounterMode;       /*!< Specifies the counter mode.
                                    This parameter can be a value of @ref TIM_Counter_Mode */

    uint32_t Period;            /*!< Specifies the period value to be loaded into the active
                                    Auto-Reload Register at the next update event.
                                    This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF.  */

    uint32_t ClockDivision;     /*!< Specifies the clock division.
                                    This parameter can be a value of @ref TIM_ClockDivision */

    uint32_t RepetitionCounter;  /*!< Specifies the repetition counter value. Each time the RCR downcounter
                                        reaches zero, an update event is generated and counting restarts
                                        from the RCR value (N).
                                        This means in PWM mode that (N+1) corresponds to:
                                            - the number of PWM periods in edge-aligned mode
                                            - the number of half PWM period in center-aligned mode
                                        GP timers: this parameter must be a number between Min_Data = 0x00 and
                                        Max_Data = 0xFF.
                                        Advanced timers: this parameter must be a number between Min_Data = 0x0000 and
                                        Max_Data = 0xFFFF. */

    uint32_t AutoReloadPreload;  /*!< Specifies the auto-reload preload.
                                    This parameter can be a value of @ref TIM_AutoReloadPreload */
}ST_Timers_API;


//==============================================================================

//----------------------------- Global Objects -------------------------------

void Init_Timer(ST_Timers_API *Timx);
// void delay_us(ST_Timers_API *Timx, uint16_t delay);

extern ST_Timers_API tim1_config;
//==============================================================================

#endif