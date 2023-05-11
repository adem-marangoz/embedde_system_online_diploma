/**
 * @file Stm32f10xx_RCC.h
 * @author Adem marangoz (adem.marangoz95@gmail.com)
 * @brief This Header file for RCC Registers and Declerat functions and Macro directive
 * @version 0.1
 * @date 2022-05-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef RCC_H_
#define RCC_H_

#include "Stm32f10xx_Common.h"
#include "Stm32f10xx_Address.h"


/* ---------------------------- RCC_CR Register ---------------------------- */
#define __CR_PLLRDY()                          (READ_REG(RCC->RCC_CR) & 1<<25)
#define __CR_PLLON_En()                        (SET_BIT(RCC->RCC_CR,1<<24))
#define __CR_PLLON_Dis()                       (CLEAR_BIT(RCC->RCC_CR,1<<24))
#define __CR_HSEBYP_En()                       (SET_BIT(RCC->RCC_CR,1<<18))         /* external 4-16 MHz oscillator not bypassed */
#define __CR_HSEBYP_Dis()                      (CLEAR_BIT(RCC->RCC_CR,1<<18))       /* external 4-16 MHz oscillator bypassed with external clock */
#define __CR_HSEON_En()                        (SET_BIT(RCC->RCC_CR,1<<18))
#define __CR_HSEON_Dis()                       (CLEAR_BIT(RCC->RCC_CR,1<<16))
#define __CR_HSION_En()                        (SET_BIT(RCC->RCC_CR,1<<0))          /* internal 8 MHz RC oscillator ON */
#define __CR_HSION_Dis()                       (CLEAR_BIT(RCC->RCC_CR,1<<0))        /* internal 8 MHz RC oscillator OFF */

/* ------------------------------------------------------------------------- */


/* ---------------------------- RCC_CFGR Register ---------------------------- */
#define __CFGR_PLLXTPRE_Not_Divided()          (CLEAR_BIT(RCC->RCC_CFGR,1<<17))
#define __CFGR_PLLXTPRE_Divided_By_2()         (SET_BIT(RCC->RCC_CFGR,1<<17))
#define __CFGR_PLLSRC_HSI()                    (CLEAR_BIT(RCC->RCC_CFGR,1<<16))     /* HSE oscillator clock selected as PLL input clock */
#define __CFGR_PLLSRC_HSE()                    (SET_BIT(RCC->RCC_CFGR,1<<16))       /* HSI oscillator clock / 2 selected as PLL input clock */

/* --------------------------------------------------------------------------- */

/*----------------------------- RCC_CIR Register ----------------------------- */
#define __CIR_HSERDYIE_En()                    (SET_BIT(RCC->RCC_CIR,1<<11))
#define __CIR_HSERDYIE_Dis()                   (CLEAR_BIT(RCC->RCC_CIR,1<<11))
#define __CIR_HSIRDYIE_En()                    (SET_BIT(RCC->RCC_CIR,1<<10))
#define __CIR_HSIRDYIE_Dis()                   (CLEAR_BIT(RCC->RCC_CIR,1<<10))
#define __CIR_LSERDYIE_En()                    (SET_BIT(RCC->RCC_CIR,1<<9))
#define __CIR_LSERDYIE_Dis()                   (CLEAR_BIT(RCC->RCC_CIR,1<<9))
#define __CIR_LSIRDYIE_En()                    (SET_BIT(RCC->RCC_CIR,1<<8))
#define __CIR_LSIRDYIE_Dis()                   (CLEAR_BIT(RCC->RCC_CIR,1<<8))


/*---------------------------------------------------------------------------- */


/* ---------------------------- RCC_APB2RSTR Register ---------------------------- */
#define __APB2RSTR_TIM11RST()                 (SET_BIT(RCC->RCC_APB2RSTR,1<<21))
#define __APB2RSTR_TIM10RST()                 (SET_BIT(RCC->RCC_APB2RSTR,1<<20))
#define __APB2RSTR_TIM9RST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<19))
#define __APB2RSTR_ADC3RST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<15))
#define __APB2RSTR_USART1RST()                (SET_BIT(RCC->RCC_APB2RSTR,1<<14))
#define __APB2RSTR_TIM8RST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<13))
#define __APB2RSTR_SPI1RST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<12))
#define __APB2RSTR_TIM1RST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<11))
#define __APB2RSTR_ADC2RST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<10))
#define __APB2RSTR_ADC1RST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<9))
#define __APB2RSTR_IOPGRST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<8))
#define __APB2RSTR_IOPFRST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<7))
#define __APB2RSTR_IOPERST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<6))
#define __APB2RSTR_IOPDRST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<5))
#define __APB2RSTR_IOPCRST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<4))
#define __APB2RSTR_IOPBRST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<3))
#define __APB2RSTR_IOPARST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<2))
#define __APB2RSTR_AFIORST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<0))
/* ------------------------------------------------------------------------------- */


/* ---------------------------- RCC_APB1RSTR Register ---------------------------- */
#define __APB1RSTR_DACRST()                   (SET_BIT(RCC->RCC_APB2RSTR,1<<29))
#define __APB1RSTR_PWRRST()                   (SET_BIT(RCC->RCC_APB2RSTR,1<<28))
#define __APB1RSTR_BKPRST()                   (SET_BIT(RCC->RCC_APB2RSTR,1<<27))
#define __APB1RSTR_CANRST()                   (SET_BIT(RCC->RCC_APB2RSTR,1<<25))
#define __APB1RSTR_USBRST()                   (SET_BIT(RCC->RCC_APB2RSTR,1<<23))
#define __APB1RSTR_I2C2RST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<22))
#define __APB1RSTR_I2C1RST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<21))
#define __APB1RSTR_UART5RST()                 (SET_BIT(RCC->RCC_APB2RSTR,1<<20))
#define __APB1RSTR_UART4RST()                 (SET_BIT(RCC->RCC_APB2RSTR,1<<19))
#define __APB1RSTR_USART3RST()                (SET_BIT(RCC->RCC_APB2RSTR,1<<18))
#define __APB1RSTR_USART2RST()                (SET_BIT(RCC->RCC_APB2RSTR,1<<17))
#define __APB1RSTR_SPI3RST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<15))
#define __APB1RSTR_SPI2RST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<14))
#define __APB1RSTR_WWDGRST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<11))
#define __APB1RSTR_TIM14RST()                 (SET_BIT(RCC->RCC_APB2RSTR,1<<8))
#define __APB1RSTR_TIM13RST()                 (SET_BIT(RCC->RCC_APB2RSTR,1<<7))
#define __APB1RSTR_TIM12RST()                 (SET_BIT(RCC->RCC_APB2RSTR,1<<6))
#define __APB1RSTR_TIM7RST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<5))
#define __APB1RSTR_TIM6RST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<4))
#define __APB1RSTR_TIM5RST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<3))
#define __APB1RSTR_TIM4RST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<2))
#define __APB1RSTR_TIM3RST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<1))
#define __APB1RSTR_TIM2RST()                  (SET_BIT(RCC->RCC_APB2RSTR,1<<0))
/* ------------------------------------------------------------------------------- */


/* ---------------------------- RCC_AHBENR Register ---------------------------- */
#define __AHBENR_SDIOEN_En()                 (SET_BIT(RCC->RCC_AHBENR,1<<10))
#define __AHBENR_SDIOEN_Dis()                (CLEAR_BIT(RCC->RCC_AHBENR,1<<10))
#define __AHBENR_FSMCEN_En()                 (SET_BIT(RCC->RCC_AHBENR,1<<8))
#define __AHBENR_FSMCEN_Dis()                (CLEAR_BIT(RCC->RCC_AHBENR,1<<8))
#define __AHBENR_CRCEN_En()                  (SET_BIT(RCC->RCC_AHBENR,1<<6))
#define __AHBENR_CRCEN_Dis()                 (CLEAR_BIT(RCC->RCC_AHBENR,1<<6))
#define __AHBENR_FLITFEN_En()                (SET_BIT(RCC->RCC_AHBENR,1<<4))        /* Set and cleared by software to disable/enable FLITF clock during Sleep mode. */
#define __AHBENR_FLITFEN_Dis()               (CLEAR_BIT(RCC->RCC_AHBENR,1<<4))      /* Set and cleared by software to disable/enable FLITF clock during Sleep mode. */
#define __AHBENR_SRAMEN_En()                 (SET_BIT(RCC->RCC_AHBENR,1<<2))
#define __AHBENR_SRAMEN_Dis()                (CLEAR_BIT(RCC->RCC_AHBENR,1<<2))
#define __AHBENR_DMA2EN_En()                 (SET_BIT(RCC->RCC_AHBENR,1<<1))
#define __AHBENR_DMA2EN_Dis()                (CLEAR_BIT(RCC->RCC_AHBENR,1<<1))
#define __AHBENR_DMA1EN_En()                 (SET_BIT(RCC->RCC_AHBENR,1<<0))
#define __AHBENR_DMA1EN_Dis()                (CLEAR_BIT(RCC->RCC_AHBENR,1<<0))
/* ----------------------------------------------------------------------------- */


/* ---------------------------- RCC_APB2ENR Register ---------------------------- */
#define __APB2ENR_USART1EN_En()              (SET_BIT((RCC->RCC_APB2ENR),1<<14))
#define __APB2ENR_SPI1EN_En()                (SET_BIT((RCC->RCC_APB2ENR),1<<12))
#define __APB2ENR_TIM1EN_En()                (SET_BIT((RCC->RCC_APB2ENR),1<<11))
#define __APB2ENR_ADC2EN_En()                (SET_BIT((RCC->RCC_APB2ENR),1<<10))
#define __APB2ENR_ADC1EN_En()                (SET_BIT((RCC->RCC_APB2ENR),1<<9))
//#define __APB2ENR_IOPGEN_En()                (SET_BIT((RCC->RCC_APB2ENR),1<<8))
//#define __APB2ENR_IOPFEN_En()                (SET_BIT((RCC->RCC_APB2ENR),1<<7))
#define __APB2ENR_IOPEEN_En()                (SET_BIT((RCC->RCC_APB2ENR),1<<6))
#define __APB2ENR_IOPDEN_En()                (SET_BIT((RCC->RCC_APB2ENR),1<<5))
#define __APB2ENR_IOPCEN_En()                (SET_BIT((RCC->RCC_APB2ENR),1<<4))
#define __APB2ENR_IOPBEN_En()                (SET_BIT((RCC->RCC_APB2ENR),1<<3))
#define __APB2ENR_IOPAEN_En()                (SET_BIT((RCC->RCC_APB2ENR),1<<2))
#define __APB2ENR_AFIOEN_En()                (SET_BIT((RCC->RCC_APB2ENR),1U<<0U))


/* ------------------------------------------------------------------------------ */


/* ---------------------------- RCC_APB1ENR Register ---------------------------- */
#define __APB1ENR_DACEN_EN()                  (SET_BIT(RCC->RCC_APB1ENR,1<<29))
#define __APB1ENR_PWREN_EN()                  (SET_BIT(RCC->RCC_APB1ENR,1<<28))
#define __APB1ENR_BKPEN_EN()                  (SET_BIT(RCC->RCC_APB1ENR,1<<27))
#define __APB1ENR_CANEN_EN()                  (SET_BIT(RCC->RCC_APB1ENR,1<<25))
#define __APB1ENR_USBEN_EN()                  (SET_BIT(RCC->RCC_APB1ENR,1<<23))
#define __APB1ENR_I2C2EN_EN()                 (SET_BIT(RCC->RCC_APB1ENR,1<<22))
#define __APB1ENR_I2C1EN_EN()                 (SET_BIT(RCC->RCC_APB1ENR,1<<21))
#define __APB1ENR_UART5EN_EN()                (SET_BIT(RCC->RCC_APB1ENR,1<<20))
#define __APB1ENR_UART4EN_EN()                (SET_BIT(RCC->RCC_APB1ENR,1<<19))
#define __APB1ENR_USART3EN_EN()               (SET_BIT(RCC->RCC_APB1ENR,1<<18))
#define __APB1ENR_USART2EN_EN()               (SET_BIT(RCC->RCC_APB1ENR,1<<17))
#define __APB1ENR_SPI3EN_EN()                 (SET_BIT(RCC->RCC_APB1ENR,1<<15))
#define __APB1ENR_SPI2EN_EN()                 (SET_BIT(RCC->RCC_APB1ENR,1<<14))
#define __APB1ENR_WWDGEN_EN()                 (SET_BIT(RCC->RCC_APB1ENR,1<<11))
#define __APB1ENR_TIM14EN_EN()                (SET_BIT(RCC->RCC_APB1ENR,1<<8))
#define __APB1ENR_TIM13EN_EN()                (SET_BIT(RCC->RCC_APB1ENR,1<<7))
#define __APB1ENR_TIM12EN_EN()                (SET_BIT(RCC->RCC_APB1ENR,1<<6))
#define __APB1ENR_TIM7EN_EN()                 (SET_BIT(RCC->RCC_APB1ENR,1<<5))
#define __APB1ENR_TIM6EN_EN()                 (SET_BIT(RCC->RCC_APB1ENR,1<<4))
#define __APB1ENR_TIM5EN_EN()                 (SET_BIT(RCC->RCC_APB1ENR,1<<3))
#define __APB1ENR_TIM4EN_EN()                 (SET_BIT(RCC->RCC_APB1ENR,1<<2))
#define __APB1ENR_TIM3EN_EN()                 (SET_BIT(RCC->RCC_APB1ENR,1<<1))
#define __APB1ENR_TIM2EN_EN()                 (SET_BIT(RCC->RCC_APB1ENR,1<<0))


/* ------------------------------------------------------------------------------ */


/* ---------------------------- RCC_BDCR Register ---------------------------- */
#define __BDCR_BDRST_EN()                     (SET_BIT(RCC->RCC_BDCR,1<<16))
#define __BDCR_BDRST_Dis()                    (CLEAR_BIT(RCC->RCC_BDCR,1<<16))
#define __BDCR_RTCEN_EN()                     (SET_BIT(RCC->RCC_BDCR,1<<15))
#define __BDCR_RTCEN_Dis()                    (CLEAR_BIT(RCC->RCC_BDCR,1<<15))
#define __BDCR_LSEBYP_En()                    (SET_BIT(RCC->RCC_BDCR,1<<2))         /* LSE oscillator bypassed */
#define __BDCR_LSEBYP_Dis()                   (CLEAR_BIT(RCC->RCC_BDCR,1<<2))       /* LSE oscillator not bypassed */
#define __BDCR_LSEON_EN()                     (SET_BIT(RCC->RCC_BDCR,1<<0))         /* External 32 kHz oscillator ON */
#define __BDCR_LSEON_Dis()                    (CLEAR_BIT(RCC->RCC_BDCR,1<<0))       /* External 32 kHz oscillator OFF */


/* --------------------------------------------------------------------------- */


/* ---------------------------- RCC_CSR Register ---------------------------- */
#define __CSR_LSION_En()                     (SET_BIT(RCC->RCC_CSR,1<<0))
#define __CSR_LSION_Dis()                    (CLEAR_BIT(RCC->RCC_CSR,1<<0))


/* -------------------------------------------------------------------------- */
#define HSI_Freq                            8000000UL
#define HSE_MIN                             3000000UL
#define HSE_MAX                             25000000UL
//___________________________ Global Function __________________________________
uint32_t Get_Systick_Freq();
uint32_t Get_HCLK_Freq();
uint32_t Get_APB1_Freq();
uint32_t Get_APB2_Freq();
uint8_t Set_HSE_CLK_Freq(uint32_t _HSE_Freq);
//==============================================================================


#endif