/**
 * @file Stm32f10xx_Address.h
 * @author your name (you@domain.com)
 * @brief Stm32f30 Peripherals Addresess and Regsiters
 * @version 0.1
 * @date 2022-08-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef STM32F10XX_ADD_H_
#define STM32F10XX_ADD_H_

#include "Stm32f10xx_Common.h"

//======================================================================

//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*
//----------------- Register Start boundary Addresses ------------------
//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*

// Peripheral Base Address
#define Periperhal_Base_Add             0x40000000U

// Cortex M3 Base Address
#define Cortex_M3_Int_Perip_Base        0xE0000000U

// NVIC Register Mapping
#define NVIC_Base_Add                   (Cortex_M3_Int_Perip_Base + 0x000E100U)

// AFIO Base Address
#define AFIO_Base_Add                   (Periperhal_Base_Add + 0x00010000U)

// EXTI Base Address
#define EXTI_Base_Add                   (Periperhal_Base_Add + 0x00010400U)

// GPIOA Base Address
#define GPIOA_Base_Add                  (Periperhal_Base_Add + 0x00010800U)

// GPIOB Base Address
#define GPIOB_Base_Add                  (Periperhal_Base_Add + 0x00010C00U)

// GPIOC Base Address
#define GPIOC_Base_Add                  (Periperhal_Base_Add + 0x00011000U)

// GPIOD Base Address
#define GPIOD_Base_Add                  (Periperhal_Base_Add + 0x00011400U)

// GPIOE Base Address
#define GPIOE_Base_Add                  (Periperhal_Base_Add + 0x00011800U)

// GPIOF Base Address
#define GPIOF_Base_Add                  (Periperhal_Base_Add + 0x00011C00U)

// GPIOG Base Address
#define GPIOG_Base_Add                  (Periperhal_Base_Add + 0x00012000U)

// RCC Base Address
#define RCC_Base_Add                    (Periperhal_Base_Add + 0x00021000U)

#define UART1_Base_Add                  (Periperhal_Base_Add + 0x00013800U)

#define UART2_Base_Add                  (Periperhal_Base_Add + 0x00004400U)

#define UART3_Base_Add                  (Periperhal_Base_Add + 0x00004800U)

#define UART4_Base_Add                  (Periperhal_Base_Add + 0x00004C00U)

#define UART5_Base_Add                  (Periperhal_Base_Add + 0x00005000U)

#define SPI1_Base_Add                   (Periperhal_Base_Add + 0x00013000U)

#define SPI2_Base_Add                   (Periperhal_Base_Add + 0x00003800U)

#define SPI3_Base_Add                   (Periperhal_Base_Add + 0x00003C00U)

#define I2C1_Base_Add                   (Periperhal_Base_Add + 0x00005400U)

#define I2C2_Base_Add                   (Periperhal_Base_Add + 0x00005800U)

#define TIM1_Base_Add                   (Periperhal_Base_Add + 0x00012C00U)

#define TIM2_Base_Add                   (Periperhal_Base_Add + 0x00000000U)

#define TIM3_Base_Add                   (Periperhal_Base_Add + 0x00000400U)

#define TIM4_Base_Add                   (Periperhal_Base_Add + 0x00000800U)

#define TIM5_Base_Add                   (Periperhal_Base_Add + 0x00000C00U)

#define TIM6_Base_Add                   (Periperhal_Base_Add + 0x00001000U)

#define TIM7_Base_Add                   (Periperhal_Base_Add + 0x00001400U)

#define TIM8_Base_Add                   (Periperhal_Base_Add + 0x00013400U)

#define TIM9_Base_Add                   (Periperhal_Base_Add + 0x00014C00U)

#define TIM10_Base_Add                  (Periperhal_Base_Add + 0x00015000U)

#define TIM11_Base_Add                  (Periperhal_Base_Add + 0x00015400U)

#define TIM12_Base_Add                  (Periperhal_Base_Add + 0x00001800U)

#define TIM13_Base_Add                  (Periperhal_Base_Add + 0x00001C00U)

#define TIM14_Base_Add                  (Periperhal_Base_Add + 0x00002000U)

#define Systick_Base_Add                (Cortex_M3_Int_Perip_Base + 0x0000E010U)

#define SCB_Base_Add                    (Cortex_M3_Int_Perip_Base + 0x0000E000UL + 0x0D00UL)

#define DMA1_Base_Add                   (Periperhal_Base_Add + 0x00020000)

#define DMA2_Base_Add                   (Periperhal_Base_Add + 0x00020400)

#define Flash_Base_Add                  (Periperhal_Base_Add + 0x00022000)
//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*
//---------------------------- Peripheral Registers ----------------------
//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*


/* Peripheral GPIO Register*/
typedef struct
{
    __IO uint32_t GPIO_CR[2];   // Reset value  0x44444444
    __IO uint32_t GPIO_IDR;     // Reset value  0x00000000
    __IO uint32_t GPIO_ODR;     // Reset value  0x00000000
    __IO uint32_t GPIO_BSRR;    // Reset value  0x00000000
    __IO uint32_t GPIO_BRR;     // Reset value  0x00000000
    __IO uint32_t GPIO_LCKR;    // Reset value  0x00000000
}St_GPIO_Typedef;

/* Peripheral AFIO Registers*/
typedef struct 
{
    __IO uint32_t EVCR;
    __IO uint32_t MAPR;
    __IO uint32_t EXTICR[4];
         uint32_t RESERVED0;
    __IO uint32_t MAPR2;
}St_AFIO_Typedef;

/* Peripheral EXTI Registers */
typedef struct
{
    __IO uint32_t EXTI_IMR;
    __IO uint32_t EXTI_EMR;
    __IO uint32_t EXTI_RTSR;
    __IO uint32_t EXTI_FTSR;
    __IO uint32_t EXTI_SWIER;
    __IO uint32_t EXTI_RP;
}St_EXTI_Typedef;

/* Peripheral NVIC Registers */
typedef struct
{
    __IO uint32_t ISER[8U];                 /*!< The NVIC_ISER0-NVIC_ISER7 registers enable interrupts, and show which interrupts are enabled */
         uint32_t RESERVED0[24U];
    __IO uint32_t ICER[8U];                 /*!< The NVIC_ICER0-NVIC_ICER7 registers disable interrupts, and show which interrupts are enabled */
         uint32_t RESERVED1[24U];
    __IO uint32_t ISPR0[8U];                /*!< The NVIC_ISPR0-NVIC_ISPR7 registers force interrupt into the pending state, and show which interrupts are pending */
         uint32_t RESERVED2[24U];
    __IO uint32_t ICPR0[8U];                /*!< The NVIC_ICPR0-NVIC_ICPR7 registers remove the pendig state from interrupts, and show which interrupts are pending */
         uint32_t RESERVED3[24U];
    __IO uint32_t IABR0[8U];                /*!< The NVIC_IABR0-NVIC_IABR7 registers indicate which interrupts are active */
         uint32_t RESERVED4[56U];
    __IO uint32_t IPR0[240U];                 /*!< The NVIC_IPR0-NVIC_IRP59 register provide an 8-bit priority field for each interrupt and each register holds four priority fields. These registers are byte-accessible*/
         uint32_t RESERVED5[644U];
    __IO uint32_t STIR;                 /*!< The to the STIR to generate an interrupt from sofware // When the USERSETMPEND bit in the SCR is set to 1, unprivileged software can access the STIR  // Only privileged software can enable unprivileged access to the STIR*/
}St_NVIC_Typedef;

/* Peripheral RCC Registers*/
typedef struct 
{
    __IO uint32_t RCC_CR; // Reset value: 0x0000 XX83
    __IO uint32_t RCC_CFGR;
    __IO uint32_t RCC_CIR;
    __IO uint32_t RCC_APB2RSTR;
    __IO uint32_t RCC_APB1RSTR;
    __IO uint32_t RCC_AHBENR;
    __IO uint32_t RCC_APB2ENR;
    __IO uint32_t RCC_APB1ENR;
    __IO uint32_t RCC_BCDR;
    __IO uint32_t RCC_CSR;
    __IO uint32_t RCC_AHBRSTR;
    __IO uint32_t RCC_CFGR2;
}St_RCC_Typedef;


/* 
     Peripheral UART Registers
     @ref UART_Peripheral_define
*/
typedef struct 
{
     __IO uint32_t UART_SR;
     __IO uint32_t UART_DR;
     __IO uint32_t UART_BRR;
     __IO uint32_t UART_CR1;
     __IO uint32_t UART_CR2;
     __IO uint32_t UART_CR3;
     __IO uint32_t UART_GTPR;
}St_UART_Typedef;


typedef struct 
{
     __IO uint32_t SPI_CR1;
     __IO uint32_t SPI_CR2;
     __IO uint32_t SPI_SR;
     __IO uint32_t SPI_DR;
     __IO uint32_t SPI_CRCPR;
     __IO uint32_t SPI_RXCRCR;
     __IO uint32_t SPI_TXCRCR;
     __IO uint32_t SPI_I2SCFGR;
     __IO uint32_t SPI_I2SPR;
}St_SPI_Typedef;


/**
 * @brief Peripheral I2C Registers 
 * @ref I2C_Peripheral_define
 */
typedef struct 
{
     __IO uint32_t I2C_CR1;
     __IO uint32_t I2C_CR2;
     __IO uint32_t I2C_OAR1;
     __IO uint32_t I2C_OAR2;
     __IO uint32_t I2C_DR;
     __IO uint32_t I2C_SR1;
     __IO uint32_t I2C_SR2;
     __IO uint32_t I2C_CCR;
     __IO uint32_t I2C_TRISE;
}St_I2C_Typedef;


/**
 * @brief Peripheral Advanced TIM1-TIM8 Registers 
 * @ref TIM1_TIM8_Peripheral_define
 */
typedef struct 
{
     __IO uint32_t TIM_CR1;
     __IO uint32_t TIM_CR2;
     __IO uint32_t TIM_SMCR;
     __IO uint32_t TIM_DIER;
     __IO uint32_t TIM_SR;
     __IO uint32_t TIM_EGR;
     __IO uint32_t TIM_CCMR1;
     __IO uint32_t TIM_CCMR2;
     __IO uint32_t TIM_CCER;
     __IO uint32_t TIM_CNT;
     __IO uint32_t TIM_PSC;
     __IO uint32_t TIM_ARR;
     __IO uint32_t TIM_RCR;
     __IO uint32_t TIM_CCR1;
     __IO uint32_t TIM_CCR2;
     __IO uint32_t TIM_CCR3;
     __IO uint32_t TIM_CCR4;
     __IO uint32_t TIM_BDTR;
     __IO uint32_t TIM_DCR;
     __IO uint32_t TIM_DMAR;
}St_Timers_Typedef;


/**
 * @brief Cortex M3 Systick Registers 
 * @ref SysTick_define
 */
typedef struct 
{
     __IO uint32_t STK_CTRL;
     __IO uint32_t STK_LOAD;
     __IO uint32_t STK_VAL;
     __IO uint32_t STK_CALIB;
}St_SysTick_Typedef;





/**
 * @brief Peripheral DMA channel Registers 
 * @ref DMA_Peripheral_define
 */
typedef struct 
{
     __IO uint32_t DMA_CCR;
     __IO uint32_t DMA_CNDTR;
     __IO uint32_t DMA_CPAR;
     __IO uint32_t DMA_CMAR;
     __IO uint32_t RES;
}St_DMA_Channel_Register;


/**
 * @brief Peripheral DMA Registers 
 * @ref DMA_Peripheral_define
 */
typedef struct 
{
     __IO uint32_t DMA_ISR;
     __IO uint32_t DMA_IFCR;
     __IO St_DMA_Channel_Register DMA_channel_reg[7];
}St_DMA_Typedef;


/**
 * @brief System Control Block Registers
 */
typedef struct
{
  __IO  uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  __IO uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  __IO uint32_t VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  __IO uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  __IO uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  __IO uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  __IO uint8_t  SHP[12U];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  __IO uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  __IO uint32_t CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  __IO uint32_t HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  __IO uint32_t DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  __IO uint32_t MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  __IO uint32_t BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  __IO uint32_t AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  __IO  uint32_t PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  __IO  uint32_t DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  __IO  uint32_t ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  __IO  uint32_t MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  __IO  uint32_t ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
        uint32_t RESERVED0[5U];
  __IO uint32_t CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
}St_SCB_Typedef;


/**
 * @brief Flash Memory Interface Registers
 */
typedef struct
{
  __IO uint32_t ACR;
  __IO uint32_t KEYR;
  __IO uint32_t OPTKEYR;
  __IO uint32_t SR;
  __IO uint32_t CR;
  __IO uint32_t AR;
  __IO uint32_t RESERVED;
  __IO uint32_t OBR;
  __IO uint32_t WRPR;
}St_FLASH_Typedef;

//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*
//---------------------------- Instance Peripheral ----------------------
//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*

#define AFIO                ((St_AFIO_Typedef *) AFIO_Base_Add)
#define EXTI                ((St_EXTI_Typedef *) EXTI_Base_Add)
#define NVIC                ((St_NVIC_Typedef *) NVIC_Base_Add)


//@ref GPIO_Instance
#define GPIOA               ((St_GPIO_Typedef *) GPIOA_Base_Add)
#define GPIOB               ((St_GPIO_Typedef *) GPIOB_Base_Add)
#define GPIOC               ((St_GPIO_Typedef *) GPIOC_Base_Add)
#define GPIOD               ((St_GPIO_Typedef *) GPIOD_Base_Add)
#define GPIOE               ((St_GPIO_Typedef *) GPIOE_Base_Add)
#define GPIOF               ((St_GPIO_Typedef *) GPIOF_Base_Add)
#define GPIOG               ((St_GPIO_Typedef *) GPIOG_Base_Add)

#define UART1               ((St_UART_Typedef *) UART1_Base_Add)
#define UART2               ((St_UART_Typedef *) UART2_Base_Add)
#define UART3               ((St_UART_Typedef *) UART3_Base_Add)

#define SPI1                ((St_SPI_Typedef *) SPI1_Base_Add)
#define SPI2                ((St_SPI_Typedef *) SPI2_Base_Add)
#define SPI3                ((St_SPI_Typedef *) SPI3_Base_Add)

#define RCC                 ((St_RCC_Typedef *) RCC_Base_Add)

#define I2C1                ((St_I2C_Typedef *) I2C1_Base_Add)
#define I2C2                ((St_I2C_Typedef *) I2C2_Base_Add)

#define TIM1                ((St_Timers_Typedef *) TIM1_Base_Add)
#define TIM2                ((St_Timers_Typedef *) TIM2_Base_Add)
#define TIM3                ((St_Timers_Typedef *) TIM3_Base_Add)
#define TIM4                ((St_Timers_Typedef *) TIM4_Base_Add)

#define SysTick             ((St_SysTick_Typedef *) Systick_Base_Add)

#define DMA1                ((St_DMA_Typedef *) DMA1_Base_Add)

#define SCB                 ((St_SCB_Typedef *) SCB_Base_Add)

#define FLASH               ((St_FLASH_Typedef *) Flash_Base_Add)




#endif
