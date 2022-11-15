/**
 * @file Stm32f10x_UART.c
 * @author adem alnajjar (adem.marangoz95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Stm32f10x_UART.h"
#include "Stm32f10xx_GPIO.h"
#include "Stm32f10xx_RCC.h"
#include "Stm32f10xx_EXTI.h"
#include "Stm32f10x_SPI.h"
#include <stdio.h>
#include "Stm32_f10xx_Systick.h"
#include "EEPROM_25xx256.h"

//_____________________ Generica Function & Data Structure _____________________

void _Config_GPIO_f(St_Uart_API *Inst);
//==============================================================================

//________________________ External Function & Variables _______________________

extern St_SPI_API spi1_config;
extern void _delay_ms(uint32_t time);
extern St_Uart_API uart1_config;
extern St_Uart_API uart2_config;
extern St_Uart_API uart3_config;
// extern uint16_t Rx_Buff[10];
extern St_EEPROM_25xx256_Typedef EEPORM_25xx_config;
//==============================================================================



/**
 * @brief       is used to Set baud rate uart
 * @param[in]   Inst : data structure for UART API    
 * @return      None
 */
uint8_t Set_BaudRate(St_Uart_API *Inst)
{
    if(!(IS_UART_ALL_INSTANCE(Inst->UARTx))){return 0;}
    uint32_t Bus_Freq = 0;
    if(Inst->UARTx == UART1){Bus_Freq = Get_APB2_Freq();}
    else{Bus_Freq = Get_APB1_Freq();}

    uint32_t Div_Mantissa = Bus_Freq/(uint32_t)16;
    Div_Mantissa = Div_Mantissa/(Inst->baudrate);
    Inst->UARTx->UART_BRR |= (Div_Mantissa << 4);
    uint32_t Div_Fraction = Bus_Freq/(uint32_t)16;
    Div_Fraction = ((uint32_t)100*Div_Fraction)/(Inst->baudrate);
    Div_Fraction = (Div_Fraction - Div_Mantissa*100)*16;
    Div_Fraction = Div_Fraction/(uint32_t)100;
    Inst->UARTx->UART_BRR |= Div_Fraction;
    
    return 1;
}

/**
 * @brief       is used to get baud rate uart
 * @param[in]   uart : data structure for UART API  
 * @return      uint16_t : Baud Rate value
 */
uint16_t Get_BaudRate(St_Uart_API *Inst)
{
    //TODO
}

/**
 * @brief       Is Used to Config UART
 * @param[in]   uart : data structure for UART API   
 * @return      uint8_t  : 1 = Succesed
 *                         0 = Failed
 */
uint8_t Init_Uart(St_Uart_API *Inst)
{
    // Check Instance UART 
    if(!(IS_UART_ALL_INSTANCE(Inst->UARTx))){return 0;}
    
    //Initially giving base functions addresses values
    if(Inst->P_Error_CallBack == NULL){Inst->P_Error_CallBack = Error_CallBack_UART;}
    if(Inst->P_Parity_CallBack == NULL){Inst->P_Parity_CallBack = Parity_CallBack_UART;}
    if(Inst->P_Tx_CallBack == NULL){Inst->P_Tx_CallBack = Tx_CallBack_UART;}
    if(Inst->P_Tx_Com_CallBack == NULL){Inst->P_Tx_Com_CallBack = Tx_Comp_CallBack_UART;}
    if(Inst->P_Rx_CallBack == NULL){Inst->P_Rx_CallBack = Rx_CallBack_UART;}
    if(Inst->P_IDLE_CallBack == NULL){Inst->P_IDLE_CallBack = IDLE_CallBack_UART;}
    if(Inst->P_Lin_BK_CallBack == NULL){Inst->P_Lin_BK_CallBack = Lin_BK_CallBack_UART;}
    if(Inst->P_FlowCTR_CallBack == NULL){Inst->P_FlowCTR_CallBack = FlowCt_CallBack_UART;}

    // Config Pins
    _Config_GPIO_f(Inst);

    // Enable Uart Clock
    if(Inst->UARTx == UART1){__APB2ENR_USART1EN_En();}
    else if (Inst->UARTx == UART2){__APB1ENR_USART2EN_EN();}
    else if (Inst->UARTx == UART3){__APB1ENR_USART3EN_EN();}

    // Set Uart BuadRate
    Set_BaudRate(Inst);
    // Set Transmitter Enable to sends IDLE line 
    if(Inst->Mode == Enable_RX){Inst->UARTx->UART_CR1 |=  Inst->Mode;} // Enable Just Rx
    else if(Inst->Mode == Enable_Tx){Inst->UARTx->UART_CR1 |= Inst->Mode;} // Enable Just Tx
    else {Inst->UARTx->UART_CR1 |= Inst->Mode;} // Enable Rx and Tx
    //PCE: Parity control enable
    Inst->UARTx->UART_CR1 |= Inst->Parity;
    //Enable/Disable Flow Control CTS/RTS
    Inst->UARTx->UART_CR3 |= Inst->Hw_Flow_CTRL;
    //Stop bit
    Inst->UARTx->UART_CR2 |= Inst->Stop_bit;
    // Word Lenght
    Inst->UARTx->UART_CR1 |= Inst->Word_Len;
    

    // for Enable Interrupt
    if(Inst->interrupt != 0)
    {
        if(Inst->UARTx == UART1){NVIC_EnableIRQ(USART1_IRQn);}
        else if (Inst->UARTx == UART2){NVIC_EnableIRQ(USART2_IRQn);}
        else if(Inst->UARTx == UART3){NVIC_EnableIRQ(USART3_IRQn);}

        if((Inst->interrupt & En_CR3_Interrupt) == En_CR3_Interrupt)
        {
            Inst->UARTx->UART_CR3 |= (Inst->interrupt & UART_CR3_EIE);
            Inst->UARTx->UART_CR3 |= (Inst->interrupt & UART_CR3_CTSIE);
        }

        if((Inst->interrupt & En_CR2_Interrupt) == En_CR2_Interrupt)
        {
            Inst->UARTx->UART_CR2 |= (Inst->interrupt & UART_CR2_LBDIE);
        }

        if((Inst->interrupt & En_CR1_Interrupt) == En_CR1_Interrupt)
        {
            Inst->UARTx->UART_CR1 |= (Inst->interrupt & UART_CR1_PEIE);
            Inst->UARTx->UART_CR1 |= (Inst->interrupt & UART_CR1_TXEIE);
            Inst->UARTx->UART_CR1 |= (Inst->interrupt & UART_CR1_TCIE);
            Inst->UARTx->UART_CR1 |= (Inst->interrupt & UART_CR1_RXNEIE);
        }


    }

    // Enable the UART by writing the UE bit in UART_CR1 register to 1
    Inst->UARTx->UART_CR1 |= UART_CR1_UE;
    
    return 1;
}

/**
 * @brief       This function is used to reset UART Registers
 * @param[in]   Inst  : data structure for UART API  
 * @return      uint8_t 1 : Successed
 *                      0 : Failed
 */
uint8_t DeInit_Uart(St_Uart_API *Inst)
{
    if(Inst->UARTx == UART1)
    {
        __APB2RSTR_USART1RST();
        NVIC_DisableIRQ(USART1_IRQn);
        
    }else if(Inst->UARTx == UART2)
    {
        __APB1RSTR_USART2RST();
        NVIC_DisableIRQ(USART2_IRQn);
    }else if(Inst->UARTx == UART3)
    {
        __APB1RSTR_USART3RST();
        NVIC_DisableIRQ(USART3_IRQn);
    }
    return 1;
}


/**
 * @brief       Used to Confige UART pins
 * @param[in]   uart : data structure for UART API  
 */
void _Config_GPIO_f(St_Uart_API *Inst)
{
    GPIO_InitTypeDef gpio_config = {0};
    if(Inst->UARTx == UART1)
    {
        // Rx Pin config
        gpio_config.Mode = GPIO_MODE_AF_INPUT;
        gpio_config.Pin = GPIO_PIN_10;
        Init_GPIO(GPIOA,&gpio_config);
        // TX Pin config
        gpio_config.Mode = GPIO_MODE_AF_PP;
        gpio_config.Speed = GPIO_SPEED_FREQ_2MHZ;
        gpio_config.Pin = GPIO_PIN_9;
        Init_GPIO(GPIOA,&gpio_config);

    }else if(Inst->UARTx == UART2)
    {
        // Rx Pin config
        gpio_config.Mode = GPIO_MODE_AF_INPUT;
        gpio_config.Pin = GPIO_PIN_3;
        Init_GPIO(GPIOA,&gpio_config);
        // Tx Pin config
        gpio_config.Mode = GPIO_MODE_AF_PP;
        gpio_config.Pin = GPIO_PIN_2;
        gpio_config.Speed = GPIO_SPEED_FREQ_2MHZ;
        Init_GPIO(GPIOA,&gpio_config);

    }else if(Inst->UARTx == UART3)
    {
        // Rx Pin config
        gpio_config.Mode = GPIO_MODE_AF_INPUT;
        gpio_config.Pin = GPIO_PIN_11;
        Init_GPIO(GPIOB,&gpio_config);
        // Tx Pin config
        gpio_config.Mode = GPIO_MODE_AF_PP;
        gpio_config.Pin = GPIO_PIN_10;
        gpio_config.Speed = GPIO_SPEED_FREQ_2MHZ;
        Init_GPIO(GPIOB,&gpio_config);

    }
}

/**
 * @brief   This function is used to send a single character through uart 
 * @param   Inst : UART Data Structure ,It can be replaced by UART1 or UART2 or UART3
 * @param   msg  : First address of sending massage
 * @return  uint8_t 1 : Successed
 *                  0 : Failed
 */
uint8_t Send_Char_Uart(St_UART_Typedef *Inst,uint16_t *msg, enum Polling_mechism PollingEn)
{
    // Cgeck TXE bit  : if set meaning the data is transferred to shift register
    if(PollingEn == Enable)
        while(!(Inst->UART_SR & UART_SR_TXE));
    
    if((Inst->UART_CR1 & UART_CR1_PCE) == UART_CR1_PCE)
    {
        Inst->UART_DR = (*msg & (uint16_t)0x01FF);
    }else
    {
        Inst->UART_DR =(*msg & (uint8_t)0xFF);
    }
    return 1;
}

/**
 * @brief   This function is used to receive a singal character through uart
 * @param   Inst : UART Data Structure ,It can be replaced by UART1 or UART2 or UART3
 * @param   msg  : First address of receiving massage
 * @return  uint8_t 1 : Successed
 *                  0 : Failed 
 */
uint8_t Receive_Char_Uart(St_UART_Typedef *Inst, uint16_t *msg, enum Polling_mechism PollingEn)
{
    // Check RXNE bit : if set meaning the data is transferred to shift register 
    if(PollingEn == Enable)
        while(!(Inst->UART_SR & UART_SR_RXNE));

    if((Inst->UART_CR1 & UART_CR1_M) == UART_CR1_M)
    {
        if((Inst->UART_CR1 & UART_CR1_PCE) == UART_CR1_PCE)
        {
            *((uint16_t*)msg) = (Inst->UART_DR & (uint8_t)0xFF);
        }else
        {
            *((uint16_t*)msg) = Inst->UART_DR;
        }
    }else
    {
        if((Inst->UART_CR1 & UART_CR1_PCE) == UART_CR1_PCE)
        {
            *((uint16_t*)msg) = (Inst->UART_DR & (uint8_t)0x7F);
        }else
        {
            *((uint16_t*)msg) = (Inst->UART_DR & (uint8_t)0xFF);
        }
    }
    
    return 1;
}

/**
 * @brief   This function used to Receiv string through uart
 * @param   Inst : UART Data Structure ,It can be replaced by UART1 or UART2 or UART3
 * @param   msg  : First address of receiving massage
 * @param   msg_len : Massege length 
 * @return  uint8_t 1 : Successed
 *                  0 : Failed  
 */
uint8_t Receive_String_Uart(St_UART_Typedef *Inst, uint16_t *msg, uint8_t msg_len, enum Polling_mechism PollingEn)
{
    while(*msg != '\0')
    {
        
    }
}

/**
 * @brief   This function used to Send string through uart
 * @param   Inst : UART Data Structure ,It can be replaced by UART1 or UART2 or UART3
 * @param   msg  : First address of receiving massage
 * @param   msg_len : Massege length 
 * @return  uint8_t 1 : Successed
 *                  0 : Failed  
 */
uint8_t Send_String_Uart(St_UART_Typedef *Inst, uint16_t *msg, enum Polling_mechism PollingEn)
{
    while (*msg != '\0')
    {
        Send_Char_Uart(Inst,msg,PollingEn);
        msg++;
        delay_us(10);
    }
    
}

/**
 * @brief This function handles USART1 global interrupt.
 */
void USART1_Handler(void)
{
    if((UART1->UART_CR3 & UART_CR3_EIE) == UART_CR3_EIE)
        uart1_config.P_Error_CallBack(&uart1_config);   //  jump to defualt Error_CallBack_UART function
    else if((UART1->UART_CR1 & UART_CR1_PEIE) == UART_CR1_PEIE)
        uart1_config.P_Parity_CallBack(&uart1_config);  //  jump to defualt Parity_CallBack_UART function
    else if((UART1->UART_CR1 & UART_CR1_TXEIE) == UART_CR1_TXEIE)
        uart1_config.P_Tx_CallBack(&uart1_config);      //  jump to defualt Tx_CallBack_UART function
    else if((UART1->UART_CR1 & UART_CR1_TCIE) == UART_CR1_TCIE)
        uart1_config.P_Tx_Com_CallBack(&uart1_config);  //  jump to defualt Tx_Comp_CallBack_UART function
    else if((UART1->UART_CR1 & UART_CR1_RXNEIE) == UART_CR1_RXNEIE)
        uart1_config.P_Rx_CallBack(&uart1_config);      //  jump to defualt Rx_CallBack_UART function
    else if((UART1->UART_CR1 & UART_CR1_IDLEIE) == UART_CR1_IDLEIE)
        uart1_config.P_IDLE_CallBack(&uart1_config);    //  jump to defualt IDLE_CallBack_UART function
    else if((UART1->UART_CR2 & UART_CR2_LBDIE) == UART_CR2_LBDIE)
        uart1_config.P_Lin_BK_CallBack(&uart1_config);  //  jump to defualt Lin_BK_CallBack_UART function
    else if((UART1->UART_CR3 & UART_CR3_CTSIE) == UART_CR3_CTSIE)
        uart1_config.P_FlowCTR_CallBack(&uart1_config); //  jump to defualt FlowCt_CallBack_UART function

}

void USART2_Handler(void)
{
    if((UART2->UART_CR3 & UART_CR3_EIE) == UART_CR3_EIE)
        uart2_config.P_Error_CallBack(&uart2_config);
    else if((UART2->UART_CR1 & UART_CR1_PEIE) == UART_CR1_PEIE)
        uart2_config.P_Parity_CallBack(&uart2_config);
    else if((UART2->UART_CR1 & UART_CR1_TXEIE) == UART_CR1_TXEIE)
        uart2_config.P_Tx_CallBack(&uart2_config);
    else if((UART2->UART_CR1 & UART_CR1_TCIE) == UART_CR1_TCIE)
        uart2_config.P_Tx_Com_CallBack(&uart2_config);
    else if((UART2->UART_CR1 & UART_CR1_RXNEIE) == UART_CR1_RXNEIE)
        uart2_config.P_Rx_CallBack(&uart2_config);
    else if((UART2->UART_CR1 & UART_CR1_IDLEIE) == UART_CR1_IDLEIE)
        uart2_config.P_IDLE_CallBack(&uart2_config);
    else if((UART2->UART_CR2 & UART_CR2_LBDIE) == UART_CR2_LBDIE)
        uart2_config.P_Lin_BK_CallBack(&uart2_config);
    else if((UART2->UART_CR3 & UART_CR3_CTSIE) == UART_CR3_CTSIE)
        uart2_config.P_FlowCTR_CallBack(&uart2_config);

}

void USART3_Handler(void)
{
    // if((UART3->UART_CR3 & UART_CR3_EIE) == UART_CR3_EIE)
    //     uart3_config.P_Error_CallBack(&uart3_config);
    // else if((UART3->UART_CR1 & UART_CR1_PEIE) == UART_CR1_PEIE)
    //     uart3_config.P_Parity_CallBack(&uart3_config);
    // else if((UART3->UART_CR1 & UART_CR1_TXEIE) == UART_CR1_TXEIE)
    //     uart3_config.P_Tx_CallBack(&uart3_config);
    // else if((UART3->UART_CR1 & UART_CR1_TCIE) == UART_CR1_TCIE)
    //     uart3_config.P_Tx_Com_CallBack(&uart3_config);
    // else if((UART3->UART_CR1 & UART_CR1_RXNEIE) == UART_CR1_RXNEIE)
    //     uart3_config.P_Rx_CallBack(&uart3_config);
    // else if((UART3->UART_CR1 & UART_CR1_IDLEIE) == UART_CR1_IDLEIE)
    //     uart3_config.P_IDLE_CallBack(&uart3_config);
    // else if((UART3->UART_CR2 & UART_CR2_LBDIE) == UART_CR2_LBDIE)
    //     uart3_config.P_Lin_BK_CallBack(&uart3_config);
    // else if((UART3->UART_CR3 & UART_CR3_CTSIE) == UART_CR3_CTSIE)
    //     uart3_config.P_FlowCTR_CallBack(&uart3_config);

}


/**
 * @brief Parity Error Interrupt defualt CallBacks
 * @param UARTx  Pointer to a St_Uart_API structure that contains
 *               the configuration information for the specified UART module
 * @retval None
 */
__weak void Parity_CallBack_UART(St_Uart_API *UARTx)
{
    UNUSED(UARTx);
}

/**
 * @brief Error Flag Interrupt defualt CallBacks
 * @param UARTx  Pointer to a St_Uart_API structure that contains
 *               the configuration information for the specified UART module
 * @return None
 */
__weak void Error_CallBack_UART(St_Uart_API *UARTx)
{
    UNUSED(UARTx);
}

/**
 * @brief Tx Interrupt defualt CallBacks
 * @param UARTx  Pointer to a St_Uart_API structure that contains
 *               the configuration information for the specified UART module 
 * @return None 
 */
__weak void Tx_CallBack_UART(St_Uart_API *UARTx)
{
    UNUSED(UARTx);
}

/**
 * @brief Tx Complate Interrupt defualt CallBacks
 * @param UARTx  Pointer to a St_Uart_API structure that contains
 *               the configuration information for the specified UART module
 * @return None
 */
__weak void Tx_Comp_CallBack_UART(St_Uart_API *UARTx)
{
    UNUSED(UARTx);
}

/**
 * @brief Rx Interrupt defualt CallBacks
 * @param UARTx  Pointer to a St_Uart_API structure that contains
 *               the configuration information for the specified UART module 
 * @return None 
 */
__weak void Rx_CallBack_UART(St_Uart_API *UARTx)
{
    uint16_t *Rx_Buff = NULL;
    Receive_Char_Uart(UART1, Rx_Buff,Disable);
    Send_Char_Uart(UART1, Rx_Buff,Enable);
    Reset_pin(GPIOA, GPIO_PIN_4);
    SPI_Tx_Rx_Char(&spi1_config,Rx_Buff,Rx_Buff, 1,SPI_Pol_Enable);
    Set_pin(GPIOA, GPIO_PIN_4);
    UNUSED(UARTx);
}

/**
 * @brief IDLE interrupt defualt CallBacks
 * @param UARTx  Pointer to a St_Uart_API structure that contains
 *               the configuration information for the specified UART module
 * @return None
 */
__weak void IDLE_CallBack_UART(St_Uart_API *UARTx)
{
    UNUSED(UARTx);
}

/**
 * @brief LIN Break Interrupt defualt Callbacks
 * @param UARTx  Pointer to a St_Uart_API structure that contains
 *               the configuration information for the specified UART module
 * @return None
 */
__weak void Lin_BK_CallBack_UART(St_Uart_API *UARTx)
{
    UNUSED(UARTx);
}

/**
 * @brief CTS/RTS Interrupts defualt CallBacks 
 * @param UARTx  Pointer to a St_Uart_API structure that contains
 *               the configuration information for the specified UART module
 * @return None
 */
__weak void FlowCt_CallBack_UART(St_Uart_API *UARTx)
{
    UNUSED(UARTx);
}