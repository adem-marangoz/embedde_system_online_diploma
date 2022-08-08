/**
 * @file Stm32f10xx_EXTI.h
 * @author Adem marangoz (adem.marangoz95@gmail.com)
 * @brief This Header file for EXTI Registers and Declerat functions and Macro directive
 * @version 0.1
 * @date 2022-05-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef EXTI_H_
#define EXTI_H_

#include "Stm32f10xx_Common.h"
#include "Stm32f10xx_Address.h"
#include "Stm32f10xx_GPIO.h"

#define NVIC_EnableIRQ              __NVIC_EnableIRQ
#define NVIC_DisableIRQ             __NVIC_DisableIRQ


/* Interrupt Tabol */
typedef enum
{
/******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                             */
  HardFault_IRQn              = -13,    /*!< 3 Cortex-M3 Hard Fault Interrupt                     */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt              */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                       */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                 */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                       */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                   */
/******  STM32 specific Interrupt Numbers *********************************************************/
  WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                            */
  PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt            */
  TAMPER_IRQn                 = 2,      /*!< Tamper Interrupt                                     */
  RTC_IRQn                    = 3,      /*!< RTC global Interrupt                                 */
  FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                               */
  RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                 */
  EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                 */
  EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                 */
  EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                 */
  EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                 */
  EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                 */
  DMA1_Channel1_IRQn          = 11,     /*!< DMA1 Channel 1 global Interrupt                      */
  DMA1_Channel2_IRQn          = 12,     /*!< DMA1 Channel 2 global Interrupt                      */
  DMA1_Channel3_IRQn          = 13,     /*!< DMA1 Channel 3 global Interrupt                      */
  DMA1_Channel4_IRQn          = 14,     /*!< DMA1 Channel 4 global Interrupt                      */
  DMA1_Channel5_IRQn          = 15,     /*!< DMA1 Channel 5 global Interrupt                      */
  DMA1_Channel6_IRQn          = 16,     /*!< DMA1 Channel 6 global Interrupt                      */
  DMA1_Channel7_IRQn          = 17,     /*!< DMA1 Channel 7 global Interrupt                      */
  ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
  USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
  USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
  CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
  CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
  EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
  TIM1_BRK_IRQn               = 24,     /*!< TIM1 Break Interrupt                                 */
  TIM1_UP_IRQn                = 25,     /*!< TIM1 Update Interrupt                                */
  TIM1_TRG_COM_IRQn           = 26,     /*!< TIM1 Trigger and Commutation Interrupt               */
  TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                       */
  TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                */
  TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                */
  TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt                                */
  I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
  I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
  I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
  I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
  SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
  SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
  USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
  USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
  USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
  EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
  RTC_Alarm_IRQn              = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
  USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
}IRQn_Type;

typedef enum
{
  EXTI0 = 0,
  EXTI1,
  EXTI2,
  EXTI3,
  EXTI4,
  EXTI5,
  EXTI6,
  EXTI7,
  EXTI8,
  EXTI9,
  EXTI10,
  EXTI11,
  EXTI12,
  EXTI13,
  EXTI14,
  EXTI15,
}En_EXTI_Lines;


//@ref EXTI_Pin_Trigger_Type
typedef enum
{
  RISING_EDGE_Trigger = 0,
  FALLING_EDGE_Trigger,
  RISING_EDGE_FALLIG_EDGE_Trigger,
}En_EXTI_Trigger;

//@ref EXTI_State
typedef enum
{
  EXTI_Disable = 0,
  EXTI_Enable,
}En_EXTI_State;

typedef struct 
{
  uint16_t pin;
  St_GPIO_Typedef *GPIO_port;
  En_EXTI_Lines Line;
  IRQn_Type IRQn_number;
}St_EXTI_Pins;

typedef struct 
{
  St_EXTI_Pins    EXTI_Pin;    // Specifies the External interrupt GPIO mapping
                                // This parameter must be set based on @ref define EXTI_Pins_Config

  En_EXTI_Trigger EXTI_Trigger; // Specifies the External intrrupt Trigger type
                                // This parameter must be set base on @ref EXTI_Pin_Trigger_Type

  En_EXTI_State   EXTI_State;   // Specifies the External interrupt state
                                // This parameter must be set base on @ref EXTI_State

  void (*P_IRQ_CallBack)(void); // Set C Function() which will be called once the IRQ happen

}St_EXTI_config;


//@ref define EXTI_Pins_Config
#define EXTI0PA0              (St_EXTI_Pins){GPIO_PIN_0 , GPIOA , EXTI0 , EXTI0_IRQn}
#define EXTI0PA1              (St_EXTI_Pins){GPIO_PIN_1 , GPIOA , EXTI1 , EXTI1_IRQn}
#define EXTI0PA2              (St_EXTI_Pins){GPIO_PIN_2 , GPIOA , EXTI2 , EXTI2_IRQn}
#define EXTI0PA3              (St_EXTI_Pins){GPIO_PIN_3 , GPIOA , EXTI3 , EXTI3_IRQn}
#define EXTI0PA4              (St_EXTI_Pins){GPIO_PIN_4 , GPIOA , EXTI4 , EXTI4_IRQn}
#define EXTI0PA5              (St_EXTI_Pins){GPIO_PIN_5 , GPIOA , EXTI5 , EXTI9_5_IRQn}
#define EXTI0PA6              (St_EXTI_Pins){GPIO_PIN_6 , GPIOA , EXTI6 , EXTI9_5_IRQn}
#define EXTI0PA7              (St_EXTI_Pins){GPIO_PIN_7 , GPIOA , EXTI7 , EXTI9_5_IRQn}
#define EXTI0PA8              (St_EXTI_Pins){GPIO_PIN_8 , GPIOA , EXTI8 , EXTI9_5_IRQn}
#define EXTI0PA9              (St_EXTI_Pins){GPIO_PIN_9 , GPIOA , EXTI9 , EXTI9_5_IRQn}
#define EXTI0PA10             (St_EXTI_Pins){GPIO_PIN_10 , GPIOA , EXTI10 , EXTI15_10_IRQn}
#define EXTI0PA11             (St_EXTI_Pins){GPIO_PIN_11 , GPIOA , EXTI11 , EXTI15_10_IRQn}
#define EXTI0PA12             (St_EXTI_Pins){GPIO_PIN_12 , GPIOA , EXTI12 , EXTI15_10_IRQn}
#define EXTI0PA13             (St_EXTI_Pins){GPIO_PIN_13 , GPIOA , EXTI13 , EXTI15_10_IRQn}
#define EXTI0PA14             (St_EXTI_Pins){GPIO_PIN_14 , GPIOA , EXTI14 , EXTI15_10_IRQn}
#define EXTI0PA15             (St_EXTI_Pins){GPIO_PIN_15 , GPIOA , EXTI15 , EXTI15_10_IRQn}

#define EXTI0PB0              (St_EXTI_Pins){GPIO_PIN_0 , GPIOB , EXTI0 , EXTI0_IRQn}
#define EXTI0PB1              (St_EXTI_Pins){GPIO_PIN_1 , GPIOB , EXTI1 , EXTI1_IRQn}
#define EXTI0PB2              (St_EXTI_Pins){GPIO_PIN_2 , GPIOB , EXTI2 , EXTI2_IRQn}
#define EXTI0PB3              (St_EXTI_Pins){GPIO_PIN_3 , GPIOB , EXTI3 , EXTI3_IRQn}
#define EXTI0PB4              (St_EXTI_Pins){GPIO_PIN_4 , GPIOB , EXTI4 , EXTI4_IRQn}
#define EXTI0PB5              (St_EXTI_Pins){GPIO_PIN_5 , GPIOB , EXTI5 , EXTI9_5_IRQn}
#define EXTI0PB6              (St_EXTI_Pins){GPIO_PIN_6 , GPIOB , EXTI6 , EXTI9_5_IRQn}
#define EXTI0PB7              (St_EXTI_Pins){GPIO_PIN_7 , GPIOB , EXTI7 , EXTI9_5_IRQn}
#define EXTI0PB8              (St_EXTI_Pins){GPIO_PIN_8 , GPIOB , EXTI8 , EXTI9_5_IRQn}
#define EXTI0PB9              (St_EXTI_Pins){GPIO_PIN_9 , GPIOB , EXTI9 , EXTI9_5_IRQn}
#define EXTI0PB10             (St_EXTI_Pins){GPIO_PIN_10 , GPIOB , EXTI10 , EXTI15_10_IRQn}
#define EXTI0PB11             (St_EXTI_Pins){GPIO_PIN_11 , GPIOB , EXTI11 , EXTI15_10_IRQn}
#define EXTI0PB12             (St_EXTI_Pins){GPIO_PIN_12 , GPIOB , EXTI12 , EXTI15_10_IRQn}
#define EXTI0PB13             (St_EXTI_Pins){GPIO_PIN_13 , GPIOB , EXTI13 , EXTI15_10_IRQn}
#define EXTI0PB14             (St_EXTI_Pins){GPIO_PIN_14 , GPIOB , EXTI14 , EXTI15_10_IRQn}
#define EXTI0PB15             (St_EXTI_Pins){GPIO_PIN_15 , GPIOB , EXTI15 , EXTI15_10_IRQn}

#define EXTI0PC0              (St_EXTI_Pins){GPIO_PIN_0 , GPIOC , EXTI0 , EXTI0_IRQn}
#define EXTI0PC1              (St_EXTI_Pins){GPIO_PIN_1 , GPIOC , EXTI1 , EXTI1_IRQn}
#define EXTI0PC2              (St_EXTI_Pins){GPIO_PIN_2 , GPIOC , EXTI2 , EXTI2_IRQn}
#define EXTI0PC3              (St_EXTI_Pins){GPIO_PIN_3 , GPIOC , EXTI3 , EXTI3_IRQn}
#define EXTI0PC4              (St_EXTI_Pins){GPIO_PIN_4 , GPIOC , EXTI4 , EXTI4_IRQn}
#define EXTI0PC5              (St_EXTI_Pins){GPIO_PIN_5 , GPIOC , EXTI5 , EXTI9_5_IRQn}
#define EXTI0PC6              (St_EXTI_Pins){GPIO_PIN_6 , GPIOC , EXTI6 , EXTI9_5_IRQn}
#define EXTI0PC7              (St_EXTI_Pins){GPIO_PIN_7 , GPIOC , EXTI7 , EXTI9_5_IRQn}
#define EXTI0PC8              (St_EXTI_Pins){GPIO_PIN_8 , GPIOC , EXTI8 , EXTI9_5_IRQn}
#define EXTI0PC9              (St_EXTI_Pins){GPIO_PIN_9 , GPIOC , EXTI9 , EXTI9_5_IRQn}
#define EXTI0PC10             (St_EXTI_Pins){GPIO_PIN_10 , GPIOC , EXTI10 , EXTI15_10_IRQn}
#define EXTI0PC11             (St_EXTI_Pins){GPIO_PIN_11 , GPIOC , EXTI11 , EXTI15_10_IRQn}
#define EXTI0PC12             (St_EXTI_Pins){GPIO_PIN_12 , GPIOC , EXTI12 , EXTI15_10_IRQn}
#define EXTI0PC13             (St_EXTI_Pins){GPIO_PIN_13 , GPIOC , EXTI13 , EXTI15_10_IRQn}
#define EXTI0PC14             (St_EXTI_Pins){GPIO_PIN_14 , GPIOC , EXTI14 , EXTI15_10_IRQn}
#define EXTI0PC15             (St_EXTI_Pins){GPIO_PIN_15 , GPIOC , EXTI15 , EXTI15_10_IRQn}

#define EXTI0PD0              (St_EXTI_Pins){GPIO_PIN_0 , GPIOD , EXTI0 , EXTI0_IRQn}
#define EXTI0PD1              (St_EXTI_Pins){GPIO_PIN_1 , GPIOD , EXTI1 , EXTI1_IRQn}
#define EXTI0PD2              (St_EXTI_Pins){GPIO_PIN_2 , GPIOD , EXTI2 , EXTI2_IRQn}
#define EXTI0PD3              (St_EXTI_Pins){GPIO_PIN_3 , GPIOD , EXTI3 , EXTI3_IRQn}
#define EXTI0PD4              (St_EXTI_Pins){GPIO_PIN_4 , GPIOD , EXTI4 , EXTI4_IRQn}
#define EXTI0PD5              (St_EXTI_Pins){GPIO_PIN_5 , GPIOD , EXTI5 , EXTI9_5_IRQn}
#define EXTI0PD6              (St_EXTI_Pins){GPIO_PIN_6 , GPIOD , EXTI6 , EXTI9_5_IRQn}
#define EXTI0PD7              (St_EXTI_Pins){GPIO_PIN_7 , GPIOD , EXTI7 , EXTI9_5_IRQn}
#define EXTI0PD8              (St_EXTI_Pins){GPIO_PIN_8 , GPIOD , EXTI8 , EXTI9_5_IRQn}
#define EXTI0PD9              (St_EXTI_Pins){GPIO_PIN_9 , GPIOD , EXTI9 , EXTI9_5_IRQn}
#define EXTI0PD10             (St_EXTI_Pins){GPIO_PIN_10 , GPIOD , EXTI10 , EXTI15_10_IRQn}
#define EXTI0PD11             (St_EXTI_Pins){GPIO_PIN_11 , GPIOD , EXTI11 , EXTI15_10_IRQn}
#define EXTI0PD12             (St_EXTI_Pins){GPIO_PIN_12 , GPIOD , EXTI12 , EXTI15_10_IRQn}
#define EXTI0PD13             (St_EXTI_Pins){GPIO_PIN_13 , GPIOD , EXTI13 , EXTI15_10_IRQn}
#define EXTI0PD14             (St_EXTI_Pins){GPIO_PIN_14 , GPIOD , EXTI14 , EXTI15_10_IRQn}
#define EXTI0PD15             (St_EXTI_Pins){GPIO_PIN_15 , GPIOD , EXTI15 , EXTI15_10_IRQn}

#define EXTI0PE0              (St_EXTI_Pins){GPIO_PIN_0 , GPIOE , EXTI0 , EXTI0_IRQn}
#define EXTI0PE1              (St_EXTI_Pins){GPIO_PIN_1 , GPIOE , EXTI1 , EXTI1_IRQn}
#define EXTI0PE2              (St_EXTI_Pins){GPIO_PIN_2 , GPIOE , EXTI2 , EXTI2_IRQn}
#define EXTI0PE3              (St_EXTI_Pins){GPIO_PIN_3 , GPIOE , EXTI3 , EXTI3_IRQn}
#define EXTI0PE4              (St_EXTI_Pins){GPIO_PIN_4 , GPIOE , EXTI4 , EXTI4_IRQn}
#define EXTI0PE5              (St_EXTI_Pins){GPIO_PIN_5 , GPIOE , EXTI5 , EXTI9_5_IRQn}
#define EXTI0PE6              (St_EXTI_Pins){GPIO_PIN_6 , GPIOE , EXTI6 , EXTI9_5_IRQn}
#define EXTI0PE7              (St_EXTI_Pins){GPIO_PIN_7 , GPIOE , EXTI7 , EXTI9_5_IRQn}
#define EXTI0PE8              (St_EXTI_Pins){GPIO_PIN_8 , GPIOE , EXTI8 , EXTI9_5_IRQn}
#define EXTI0PE9              (St_EXTI_Pins){GPIO_PIN_9 , GPIOE , EXTI9 , EXTI9_5_IRQn}
#define EXTI0PE10             (St_EXTI_Pins){GPIO_PIN_10 , GPIOE , EXTI10 , EXTI15_10_IRQn}
#define EXTI0PE11             (St_EXTI_Pins){GPIO_PIN_11 , GPIOE , EXTI11 , EXTI15_10_IRQn}
#define EXTI0PE12             (St_EXTI_Pins){GPIO_PIN_12 , GPIOE , EXTI12 , EXTI15_10_IRQn}
#define EXTI0PE13             (St_EXTI_Pins){GPIO_PIN_13 , GPIOE , EXTI13 , EXTI15_10_IRQn}
#define EXTI0PE14             (St_EXTI_Pins){GPIO_PIN_14 , GPIOE , EXTI14 , EXTI15_10_IRQn}
#define EXTI0PE15             (St_EXTI_Pins){GPIO_PIN_15 , GPIOE , EXTI15 , EXTI15_10_IRQn}

#define EXTI0PF0              (St_EXTI_Pins){GPIO_PIN_0 , GPIOF , EXTI0 , EXTI0_IRQn}
#define EXTI0PF1              (St_EXTI_Pins){GPIO_PIN_1 , GPIOF , EXTI1 , EXTI1_IRQn}
#define EXTI0PF2              (St_EXTI_Pins){GPIO_PIN_2 , GPIOF , EXTI2 , EXTI2_IRQn}
#define EXTI0PF3              (St_EXTI_Pins){GPIO_PIN_3 , GPIOF , EXTI3 , EXTI3_IRQn}
#define EXTI0PF4              (St_EXTI_Pins){GPIO_PIN_4 , GPIOF , EXTI4 , EXTI4_IRQn}
#define EXTI0PF5              (St_EXTI_Pins){GPIO_PIN_5 , GPIOF , EXTI5 , EXTI9_5_IRQn}
#define EXTI0PF6              (St_EXTI_Pins){GPIO_PIN_6 , GPIOF , EXTI6 , EXTI9_5_IRQn}
#define EXTI0PF7              (St_EXTI_Pins){GPIO_PIN_7 , GPIOF , EXTI7 , EXTI9_5_IRQn}
#define EXTI0PF8              (St_EXTI_Pins){GPIO_PIN_8 , GPIOF , EXTI8 , EXTI9_5_IRQn}
#define EXTI0PF9              (St_EXTI_Pins){GPIO_PIN_9 , GPIOF , EXTI9 , EXTI9_5_IRQn}
#define EXTI0PF10             (St_EXTI_Pins){GPIO_PIN_10 , GPIOF , EXTI10 , EXTI15_10_IRQn}
#define EXTI0PF11             (St_EXTI_Pins){GPIO_PIN_11 , GPIOF , EXTI11 , EXTI15_10_IRQn}
#define EXTI0PF12             (St_EXTI_Pins){GPIO_PIN_12 , GPIOF , EXTI12 , EXTI15_10_IRQn}
#define EXTI0PF13             (St_EXTI_Pins){GPIO_PIN_13 , GPIOF , EXTI13 , EXTI15_10_IRQn}
#define EXTI0PF14             (St_EXTI_Pins){GPIO_PIN_14 , GPIOF , EXTI14 , EXTI15_10_IRQn}
#define EXTI0PF15             (St_EXTI_Pins){GPIO_PIN_15 , GPIOF , EXTI15 , EXTI15_10_IRQn}

#define EXTI0PG0              (St_EXTI_Pins){GPIO_PIN_0 , GPIOG , EXTI0 , EXTI0_IRQn}
#define EXTI0PG1              (St_EXTI_Pins){GPIO_PIN_1 , GPIOG , EXTI1 , EXTI1_IRQn}
#define EXTI0PG2              (St_EXTI_Pins){GPIO_PIN_2 , GPIOG , EXTI2 , EXTI2_IRQn}
#define EXTI0PG3              (St_EXTI_Pins){GPIO_PIN_3 , GPIOG , EXTI3 , EXTI3_IRQn}
#define EXTI0PG4              (St_EXTI_Pins){GPIO_PIN_4 , GPIOG , EXTI4 , EXTI4_IRQn}
#define EXTI0PG5              (St_EXTI_Pins){GPIO_PIN_5 , GPIOG , EXTI5 , EXTI9_5_IRQn}
#define EXTI0PG6              (St_EXTI_Pins){GPIO_PIN_6 , GPIOG , EXTI6 , EXTI9_5_IRQn}
#define EXTI0PG7              (St_EXTI_Pins){GPIO_PIN_7 , GPIOG , EXTI7 , EXTI9_5_IRQn}
#define EXTI0PG8              (St_EXTI_Pins){GPIO_PIN_8 , GPIOG , EXTI8 , EXTI9_5_IRQn}
#define EXTI0PG9              (St_EXTI_Pins){GPIO_PIN_9 , GPIOG , EXTI9 , EXTI9_5_IRQn}
#define EXTI0PG10             (St_EXTI_Pins){GPIO_PIN_10 , GPIOG , EXTI10 , EXTI15_10_IRQn}
#define EXTI0PG11             (St_EXTI_Pins){GPIO_PIN_11 , GPIOG , EXTI11 , EXTI15_10_IRQn}
#define EXTI0PG12             (St_EXTI_Pins){GPIO_PIN_12 , GPIOG , EXTI12 , EXTI15_10_IRQn}
#define EXTI0PG13             (St_EXTI_Pins){GPIO_PIN_13 , GPIOG , EXTI13 , EXTI15_10_IRQn}
#define EXTI0PG14             (St_EXTI_Pins){GPIO_PIN_14 , GPIOG , EXTI14 , EXTI15_10_IRQn}
#define EXTI0PG15             (St_EXTI_Pins){GPIO_PIN_15 , GPIOG , EXTI15 , EXTI15_10_IRQn}

/**
  * @brief  Enables a device specific interrupt in the NVIC interrupt controller.
  * @note   To configure interrupts priority correctly, the NVIC_PriorityGroupConfig()
  *         function should be called before. 
  * @param[in]  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (stm32f10xxx.h))
  * @retval None
  */
static inline void __NVIC_EnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}

static inline void __NVIC_DisableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ICER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}

void NVIC_EXTI_Clear_Handler(uint32_t pin);

void Init_EXTI(St_EXTI_config *Exti_config);
void Deinit_EXTI(void);
void Upadate_EXTI(St_EXTI_config *Exti_config);

void NVIC_Enable_IRQ(IRQn_Type IRQn);
void NVIC_Disable_IRQ(IRQn_Type IRQn);

#endif