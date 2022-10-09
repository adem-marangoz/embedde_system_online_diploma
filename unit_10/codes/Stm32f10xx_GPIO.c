/**
 * @file Stm32f10xx_GPIO.c
 * @author Adem marangoz (adem.marangoz95@gmail.com)
 * @brief This source file for GPIO function definition
 * @version 0.1
 * @date 2022-05-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Stm32f10xx_GPIO.h"
#include "Stm32f10xx_AFIO.h"
#include "Stm32f10xx_RCC.h"



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @addtogroup GPIO_Private_Constants GPIO Private Constants
  * @{
  */
#define GPIO_MODE             0x00000003u
#define EXTI_MODE             0x10000000u
#define GPIO_MODE_IT          0x00010000u
#define GPIO_MODE_EVT         0x00020000u
#define RISING_EDGE           0x00100000u
#define FALLING_EDGE          0x00200000u
#define GPIO_OUTPUT_TYPE      0x00000010u

#define GPIO_NUMBER           16u

/* Definitions for bit manipulation of CRL and CRH register */
#define  GPIO_CR_MODE_INPUT         0x00000000u /*!< 00: Input mode (reset state)  */
#define  GPIO_CR_CNF_ANALOG         0x00000000u /*!< 00: Analog mode  */
#define  GPIO_CR_CNF_INPUT_FLOATING 0x00000004u /*!< 01: Floating input (reset state)  */
#define  GPIO_CR_CNF_INPUT_PU_PD    0x00000008u /*!< 10: Input with pull-up / pull-down  */
#define  GPIO_CR_CNF_GP_OUTPUT_PP   0x00000000u /*!< 00: General purpose output push-pull  */
#define  GPIO_CR_CNF_GP_OUTPUT_OD   0x00000004u /*!< 01: General purpose output Open-drain  */
#define  GPIO_CR_CNF_AF_OUTPUT_PP   0x00000008u /*!< 10: Alternate function output Push-pull  */
#define  GPIO_CR_CNF_AF_OUTPUT_OD   0x0000000Cu /*!< 11: Alternate function output Open-drain  */



/**
  * @brief  Initializes the GPIOx peripheral according to the specified parameters in the GPIO_Init.
  * @param[in]  GPIOx: where x can be (A..G depending on device used) to select the GPIO peripheral
  * @param[in]  GPIO_Init: pointer to a GPIO_InitTypeDef structure that contains
  *         the configuration information for the specified GPIO peripheral.
  * @retval
  * Note
  * @retval None
  */
void Init_GPIO(St_GPIO_Typedef *GPIOx, GPIO_InitTypeDef *GPIO_init)
{
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_init->Pin));
    assert_param(IS_GPIO_MODE(GPIO_init->Mode));
    assert_param(IS_GPIO_SPEED(GPIO_init->Speed));
    assert_param(IS_GPIO_PULL(GPIO_init->Pull));


    uint32_t pos;
    uint32_t temp = 0;
    uint32_t ioposition = 0x00;
    uint32_t iocurrent  = 0x00;
    uint32_t config = 0x00u;
    __IO uint32_t *configregister; /* Store the address of CRL or CRH register based on pin number */
    uint32_t registeroffset;       /* offset used during computation of CNF and MODE bits placement inside CRL or CRH register */

    for(pos = 0; pos < GPIO_PIN_NUMBER + 1; pos++)
    {
        ioposition = 0x01 << pos;
        iocurrent  = (uint32_t)GPIO_init->Pin & ioposition;
        if(ioposition == iocurrent)
        {
            switch (GPIO_init->Mode)
            {
            case GPIO_MODE_OUTPUT_OD:
                assert_param(IS_GPIO_SPEED(GPIO_Init->Speed));
                config = GPIO_init->Speed + GPIO_CR_CNF_GP_OUTPUT_OD;
                break;
            case GPIO_MODE_OUTPUT_PP:
                assert_param(IS_GPIO_SPEED(GPIO_Init->Speed));
                config = GPIO_init->Speed + GPIO_CR_CNF_GP_OUTPUT_PP;
                break;

            case GPIO_MODE_AF_OD:
                assert_param(IS_GPIO_SPEED(GPIO_Init->Speed));
                config = GPIO_init->Speed + GPIO_CR_CNF_AF_OUTPUT_OD;
                break;

            case GPIO_MODE_AF_PP:
                assert_param(IS_GPIO_SPEED(GPIO_Init->Speed));
                config = GPIO_init->Speed + GPIO_CR_CNF_AF_OUTPUT_PP;
                break;

            /* If we are configuring the pin in INPUT (also applicable to EVENT and IT mode) */
            case GPIO_MODE_INPUT:
            case GPIO_MODE_IT_RISING:
            case GPIO_MODE_IT_FALLING:
            case GPIO_MODE_IT_RISING_FALLING:
            case GPIO_MODE_EVT_RISING:
            case GPIO_MODE_EVT_FALLING:
            case GPIO_MODE_EVT_RISING_FALLING:
                assert_param(IS_GPIO_PULL(GPIO_init->Pull));
                if (GPIO_init->Pull == GPIO_NOPULL)
                {
                    config = GPIO_CR_MODE_INPUT + GPIO_CR_CNF_INPUT_FLOATING;
                }
                else if (GPIO_init->Pull == GPIO_PULLUP)
                {
                    config = GPIO_CR_MODE_INPUT + GPIO_CR_CNF_INPUT_PU_PD;

                    /* Set the corresponding ODR bit */
                    GPIOx->GPIO_BSRR = ioposition;
                }
                else /* GPIO_PULLDOWN */
                {
                    config = GPIO_CR_MODE_INPUT + GPIO_CR_CNF_INPUT_PU_PD;

                    /* Reset the corresponding ODR bit */
                    GPIOx->GPIO_BRR = ioposition;
                }
                break;

            case GPIO_MODE_ANALOG:
                config = GPIO_CR_MODE_INPUT + GPIO_CR_CNF_ANALOG;
                break;

            default:
                break;
            }

                        /* Check if the current bit belongs to first half or last half of the pin count number
            in order to address CRH or CRL register*/
            configregister = (iocurrent < GPIO_PIN_8) ? &GPIOx->GPIO_CR[0] : &GPIOx->GPIO_CR[1];
            registeroffset = (iocurrent < GPIO_PIN_8) ? (pos << 2u) : ((pos - 8u) << 2u);

            /* Apply the new configuration of the pin to the register */
            MODIFY_REG((*configregister), ((GPIO_CRL_MODE0 | GPIO_CRL_CNF0) << registeroffset), (config << registeroffset));
            
            /*--------------------- EXTI Mode Configuration ------------------------*/
            /* Configure the External Interrupt or event for the current IO */
            if ((GPIO_init->Mode & EXTI_MODE) == EXTI_MODE)
            {
                /* Enable AFIO Clock */
                __APB2ENR_AFIOEN_En();
                temp = AFIO->EXTICR[pos >> 2u];
                CLEAR_BIT(temp, (0x0Fu) << (4u * (pos & 0x03u)));
                SET_BIT(temp, (GPIO_GET_INDEX(GPIOx)) << (4u * (pos & 0x03u)));
                AFIO->EXTICR[pos >> 2u] = temp;


                // /* Configure the interrupt mask */
                // if ((GPIO_init->Mode & GPIO_MODE_IT) == GPIO_MODE_IT)
                // {
                //     SET_BIT(EXTI->EXTI_IMR, iocurrent);
                // }
                // else
                // {
                //     CLEAR_BIT(EXTI->EXTI_IMR, iocurrent);
                // }

                // /* Configure the event mask */
                // if ((GPIO_init->Mode & GPIO_MODE_EVT) == GPIO_MODE_EVT)
                // {
                //     SET_BIT(EXTI->EXTI_EMR, iocurrent);
                // }
                // else
                // {
                //     CLEAR_BIT(EXTI->EXTI_EMR, iocurrent);
                // }

                // /* Enable or disable the rising trigger */
                // if ((GPIO_init->Mode & RISING_EDGE) == RISING_EDGE)
                // {
                //     SET_BIT(EXTI->EXTI_RTSR, iocurrent);
                // }
                // else
                // {
                //     CLEAR_BIT(EXTI->EXTI_RTSR, iocurrent);
                // }

                // /* Enable or disable the falling trigger */
                // if ((GPIO_init->Mode & FALLING_EDGE) == FALLING_EDGE)
                // {
                //     SET_BIT(EXTI->EXTI_FTSR, iocurrent);
                // }
                // else
                // {
                //     CLEAR_BIT(EXTI->EXTI_FTSR, iocurrent);
                // }
            }
        }
    }
}

/**
 * @brief Set Pin in GPIOx
 * @param[in] GPIOx     -where x can be (A..G depending on device used ) to select the GPIO peripheral @ref GPIO_Instance
 * @param[in] pin       -specifies the port bit to read. Set by @ref GPIO_PINS_Define 
 * @retval
 * Note
 */
void Set_pin(St_GPIO_Typedef *GPIOx,uint16_t pin)
{
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    GPIOx->GPIO_BSRR = pin;
}

/**
 * @brief               -Reset Pin in GPIOx
 * @param[in] GPIOx     -where x can be (A..G depending on device used ) to select the GPIO peripheral @ref GPIO_Instance
 * @param[in] pin       -specifies the port bit to read. Set by @ref GPIO_PINS_Define 
 * @retval
 * Note
 */
void Reset_pin(St_GPIO_Typedef *GPIOx,uint16_t pin)
{
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    GPIOx->GPIO_BSRR = pin << 16;
}


/**
 * @brief This function used to reset or set pin base on state parametre
 * @param GPIOx -where x can be (A..G depending on device used ) to select the GPIO peripheral @ref GPIO_Instance
 * @param pin -specifies the port bit to read. Set by @ref GPIO_PINS_Define 
 * @param state -specifies the pin state base @ref GPIO_Pin_State
 */
void Change_State_Pin(St_GPIO_Typedef *GPIOx,uint16_t pin,GPIO_PinState state)
{
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(pin));

    if(state == GPIO_PIN_RESET)
    {
        GPIOx->GPIO_BSRR = pin << 16;
    }else
    {
        GPIOx->GPIO_BSRR = pin;
    }
}

/**
 * @brief Toggle Specified GPIO Pin
 * @param[in] GPIOx     -where x can be (A..G depending on device used ) to select the GPIO peripheral @ref GPIO_Instance
 * @param[in] pin       -specifies the port bit to read. Set by @ref GPIO PINS_Define 
 * @retval
 * Note
 */
void Toggle_pin(St_GPIO_Typedef *GPIOx, uint16_t pin)
{
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(pin));

    GPIOx->GPIO_ODR ^= (uint32_t)pin;
}


/**
 * @brief Read Specified GPIO Pin State
 * @param[in] GPIOx     -where x can be (A..G depending on device used ) to select the GPIO peripheral @ref GPIO_Instance
 * @param[in] pin       -specifies the port bit to read. Set by @ref GPIO PINS_Define 
 * @param[out] GPIO_PinState    -specified Pin state according to //@ref GPIO_Pin_State 
 * @retval
 * Note
 */
GPIO_PinState Read_pin(St_GPIO_Typedef *GPIOx,uint16_t pin)
{
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(pin));
    if(GPIOx->GPIO_IDR & pin){return GPIO_PIN_SET;}
    return GPIO_PIN_RESET;
}

/**
 * @brief Set specified GPIOx
 * @param[in] GPIOx     -where x can be (A..G depending on device used ) to select the GPIO peripheral @ref GPIO_Instance
 * @retval
 * Note
 */
void Set_GPIO_Value(St_GPIO_Typedef *GPIOx,uint32_t value)
{
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    GPIOx->GPIO_ODR = value;
}

/**
 * @brief Reset specified GPIOx
 * @param[in] GPIOx     -where x can be (A..G depending on device used ) to select the GPIO peripheral @ref GPIO_Instance
 * @retval
 * Note
 */
void Reset_GPIO(St_GPIO_Typedef *GPIOx)
{
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    GPIOx->GPIO_BSRR = 0xFFFF << 16;
}

/**
 * @brief Read specified GPIOx
 * @param[in] GPIOx     -where x can be (A..G depending on device used ) to select the GPIO peripheral @ref GPIO_Instance
 * @retval
 * Note
 */
uint16_t Read_GPIO(St_GPIO_Typedef *GPIOx)
{
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(pin));
    return (uint16_t)(GPIOx->GPIO_IDR);
}

/**
 * @brief               -This function is used to lock the configuration of the port bits
 * @param[in] GPIOx     -where x can be (A..G depending on device used ) to select the GPIO peripheral @ref GPIO_Instance
 * @param[in] pin       -specifies the port bit to read. Set by @ref GPIO PINS_Define 
 * @reval               -none
 * @Note                -none
 */
uint8_t Lock_GPIO(St_GPIO_Typedef *GPIOx, uint16_t pin)
{
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_GPIO_PIN(pin));
    GPIOx->GPIO_LCKR |= pin;
    GPIOx->GPIO_LCKR |= (GPIOx->GPIO_LCKR | 0x00010000);
    GPIOx->GPIO_LCKR &= (GPIOx->GPIO_LCKR & 0x0000FFFF);
    uint32_t temp = GPIOx->GPIO_LCKR;
    if(temp & 1<<16) {return 0;}
    return 1;
}


/**
 * @brief               -reset all the GPIOx regisets
 * @param[in] GPIOx     -where x can be (A..G depending on device used ) to select the GPIO peripheral @ref GPIO_Instance
 * @param[in] pin       -specifies the port bit to read. Set by @ref GPIO PINS_Define 
 * @reval               -none
 * @Note                -none
 */
void Deinit_GPIO(St_GPIO_Typedef *GPIOx)
{
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    if(GPIOx == GPIOA)
    {

    }else if (GPIOx == GPIOB)
    {
        __APB2RSTR_IOPARST();
    }else if (GPIOx == GPIOB)
    {
        __APB2RSTR_IOPBRST();
    }else if (GPIOx == GPIOC)
    {
        __APB2RSTR_IOPCRST();
    }else if (GPIOx == GPIOD)
    {
        __APB2RSTR_IOPDRST();
    }else if (GPIOx == GPIOE)
    {
        __APB2RSTR_IOPERST();
    }else if (GPIOx == GPIOF)
    {
        __APB2RSTR_IOPFRST();
    }else if (GPIOx == GPIOG)
    {
        __APB2RSTR_IOPGRST();
    }
    
}