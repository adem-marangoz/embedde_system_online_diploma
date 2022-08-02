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

#endif