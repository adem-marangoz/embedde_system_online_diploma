#ifndef STM32F10XX_ADD_H_
#define STM32F10XX_ADD_H_


//======================================================================

//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*
//---------------------------- Register Addresses ----------------------
//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*

// Peripheral Base Address
#define Periperhal_Base_Add             0x40000000U

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

// NVIC Base Address
#define NVIC_Base_Add                   0xE000E100U


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


#define RCC_Regs            ((St_RCC_Typedef *) RCC_Base_Add)

#endif