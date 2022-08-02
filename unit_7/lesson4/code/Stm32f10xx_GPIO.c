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

    for(pos = 0; pos < GPIO_PIN_NUMBER + 1; pos++)
    {
        ioposition = 0x01 << pos;
        iocurrent  = (uint32_t)GPIO_init->Pin & ioposition;
        if(ioposition == iocurrent)
        {
            if((GPIO_init->Mode == GPIO_MODE_OUTPUT_PP) || (GPIO_init->Mode == GPIO_MODE_OUTPUT_OD)\
                || (GPIO_init->Mode == GPIO_MODE_AF_PP) || (GPIO_init->Mode == GPIO_MODE_AF_OD))
               {
                   
                    temp = GPIOx->GPIO_CR[pos >> 3];
                    temp &= ~((GPIO_MODE0_Mask | GPIO_CNF_Mask) << ((uint32_t)(pos & 0x07U) * 4));
                    temp |= (((GPIO_init->Mode << 2) | GPIO_init->Speed) << ((uint32_t)(pos & 0x07U) * 4));
                    GPIOx->GPIO_CR[pos >> 3] = temp;
               }

               if((GPIO_init->Mode & EXTI_MODE) == EXTI_MODE)
               {
                   temp = AFIO->EXTICR[pos >> 2];
                   temp &= ~((AFIO_Line_Mask) << (pos >> 2));
                   temp |= ((GPIO_GET_INDEX(GPIOx)) << (4U*(pos >> 2)));
                   AFIO->EXTICR[pos >> 2] = temp;
                   
                   temp = GPIOx->GPIO_CR[pos >> 3];
                   temp &= ~((GPIO_CNF_Mask) << ((uint32_t)(pos & 0x07U) * 4));
                   GPIOx->GPIO_CR[pos >> 3] = temp;

                   temp = EXTI->EXTI_IMR;
                   temp &= ~((iocurrent));
                   if((GPIO_init->Mode & GPIO_EXTI_MODE) == GPIO_EXTI_MODE)
                   {
                       temp |= (iocurrent);
                   }
                   EXTI->EXTI_IMR = temp;
                   
                   temp = EXTI->EXTI_EMR;
                   temp &= ~((iocurrent));
                   if((GPIO_init->Mode & GPIO_EVT_MODE) == GPIO_EVT_MODE)
                   {
                       temp |= (iocurrent);
                   }
                   EXTI->EXTI_EMR = temp;
                   
                   temp = EXTI->EXTI_RTSR;
                   temp &= ~((iocurrent));
                   if((GPIO_init->Mode & RISING_EDGE) == RISING_EDGE)
                   {
                        temp |= (iocurrent);
                   }
                   EXTI->EXTI_RTSR = temp;

                   temp = EXTI->EXTI_FTSR;
                   temp &= ~((iocurrent));
                   if((GPIO_init->Mode & FALLING_EDGE) == FALLING_EDGE)
                   {     
                        temp |= (iocurrent);
                   }
                   EXTI->EXTI_FTSR = temp;

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
void Set_GPIO(St_GPIO_Typedef *GPIOx,uint32_t value)
{
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    GPIOx->GPIO_BSRR = value;
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