/**
 * @file Stm32f10x_UART.h
 * @author Adem alnajjar (adem.marangoz95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef STM32F10X_UART_H_
#define STM32F10X_UART_H_

#include "Stm32f10xx_Address.h"
#include "Stm32f10xx_Common.h"


#define IS_UART_ALL_INSTANCE(INSTANCE) (((INSTANCE) == UART1) || \
                                        ((INSTANCE) == UART2) || \
                                        ((INSTANCE) == UART3))



//______________________________ USART_SR_BITS _________________________________
/**
 * This bit is set by hardware when a parity error occurs in receiver mode. It is cleared by a
software sequence (a read to the status register followed by a read to the USART_DR data
register). The software must wait for the RXNE flag to be set before clearing the PE bit.
An interrupt is generated if PEIE = 1 in the USART_CR1 register.
 * 
 */
#define UART_SR_PE                  (uint32_t)1 << 0
/**
 * This bit is set by hardware when a de-synchronization, excessive noise or a break character
is detected. It is cleared by a software sequence (an read to the USART_SR register
followed by a read to the USART_DR register).
0: No Framing error is detected
 * Note: This bit does not generate interrupt as it appears at the same time as the RXNE bit
which itself generates an interrupt. If the word currently being transferred causes both
frame error and overrun error, it will be transferred and only the ORE bit will be set.
An interrupt is generated on FE flag in case of Multi Buffer communication if the EIE bit
is set.
 */
#define UART_SR_FE                  (uint32_t)1 << 1
/**
 * This bit is set by hardware when noise is detected on a received frame. It is cleared by a
software sequence (an read to the USART_SR register followed by a read to the
USART_DR register).
 * Note: This bit does not generate interrupt as it appears at the same time as the RXNE bit
which itself generates an interrupting interrupt is generated on NE flag in case of Multi
Buffer communication if the EIE bit is set.
 */
#define UART_SR_NE                  (uint32_t)1 << 2
/**
 * This bit is set by hardware when the word currently being received in the shift register is
ready to be transferred into the RDR register while RXNE=1. An interrupt is generated if
RXNEIE=1 in the USART_CR1 register. It is cleared by a software sequence (an read to the
USART_SR register followed by a read to the USART_DR register).
 * Note: When this bit is set, the RDR register content will not be lost but the shift register will be
overwritten. An interrupt is generated on ORE flag in case of Multi Buffer
communication if the EIE bit is set
 */
#define UART_SR_ORE                 (uint32_t)1 << 3
/**
 * This bit is set by hardware when an Idle Line is detected. An interrupt is generated if the
IDLEIE=1 in the USART_CR1 register. It is cleared by a software sequence (an read to the
USART_SR register followed by a read to the USART_DR register).
 * Note: The IDLE bit will not be set again until the RXNE bit has been set itself (i.e. a new idle
line occurs).
 */
#define UART_SR_IDLE                (uint32_t)1 << 4
/**
 * This bit is set by hardware when the content of the RDR shift register has been transferred to
the USART_DR register. An interrupt is generated if RXNEIE=1 in the USART_CR1 register.
It is cleared by a read to the USART_DR register. The RXNE flag can also be cleared by
writing a zero to it. This clearing sequence is recommended only for multibuffer
communication.
 * 
 */
#define UART_SR_RXNE                (uint32_t)1 << 5
/**
 * This bit is set by hardware if the transmission of a frame containing data is complete and if
TXE is set. An interrupt is generated if TCIE=1 in the USART_CR1 register. It is cleared by a
software sequence (a read from the USART_SR register followed by a write to the
USART_DR register). The TC bit can also be cleared by writing a '0' to it. This clearing
sequence is recommended only for multibuffer communication
 * 
 */
#define UART_SR_TC                  (uint32_t)1 << 6
/**
 *  This bit is set by hardware when the content of the TDR register has been transferred into
    the shift register. An interrupt is generated if the TXEIE bit =1 in the USART_CR1 register. It
    is cleared by a write to the USART_DR register.
 *  Note: This bit is used during single buffer transmission
 */
#define UART_SR_TXE                 (uint32_t)1 << 7
/**
 * This bit is set by hardware when the LIN break is detected. It is cleared by software (by
   writing it to 0). An interrupt is generated if LBDIE = 1 in the USART_CR2 register.
 * Note: An interrupt is generated when LBD=1 if LBDIE=1
 */
#define UART_SR_LBD                 (uint32_t)1 << 8
/*
This bit is set by hardware when the CTS input toggles, if the CTSE bit is set.
It is cleared by software (by writing it to 0).
An interrupt is generated if CTSIE=1 in the USART_CR3 register
This bit is not available for UART4 & UART5.
*/                
#define UART_SR_CTS                 (uint32_t)1 << 9  

//==============================================================================

//________________________________ UART_CR1 ____________________________________
#define UART_CR1_UE                 (uint32_t)1 << 13
#define UART_CR1_M                  (uint32_t)1 << 12
#define UART_CR1_WAKE               (uint32_t)1 << 11
#define UART_CR1_PCE                (uint32_t)1 << 10
#define UART_CR1_PS                 (uint32_t)1 << 9
#define UART_CR1_PEIE               (uint32_t)1 << 8
#define UART_CR1_TXEIE              (uint32_t)1 << 7
#define UART_CR1_TCIE               (uint32_t)1 << 6
#define UART_CR1_RXNEIE             (uint32_t)1 << 5
#define UART_CR1_IDLEIE             (uint32_t)1 << 4
#define UART_CR1_TE                 (uint32_t)1 << 3
#define UART_CR1_RE                 (uint32_t)1 << 2
#define UART_CR1_RWU                (uint32_t)1 << 1
#define UART_CR1_SBK                (uint32_t)1 << 0                  
//==============================================================================

//________________________________ UART_CR2 ____________________________________
#define UART_CR2_LINEN              (uint32_t)1 << 14
#define UART_CR2_STOP               (uint32_t)3 << 12
#define UART_CR2_CLKEN              (uint32_t)1 << 11
#define UART_CR2_CPOL               (uint32_t)1 << 10
#define UART_CR2_CPHA               (uint32_t)1 << 9
#define UART_CR2_LBCL               (uint32_t)1 << 8
#define UART_CR2_LBDIE              (uint32_t)1 << 6
#define UART_CR2_LBDL               (uint32_t)1 << 5
#define UART_CR2_ADD                (uint32_t)15 << 0

//==============================================================================

//________________________________ UART_CR3 ____________________________________
#define UART_CR3_CTSIE              (uint32_t)1 << 10
#define UART_CR3_CTSE               (uint32_t)1 << 9
#define UART_CR3_RTSE               (uint32_t)1 << 8
#define UART_CR3_DMAT               (uint32_t)1 << 7
#define UART_CR3_DMAR               (uint32_t)1 << 6
#define UART_CR3_SCEN               (uint32_t)1 << 5
#define UART_CR3_NACK               (uint32_t)1 << 4
#define UART_CR3_HDSEL              (uint32_t)1 << 3
#define UART_CR3_IRLP               (uint32_t)1 << 2
#define UART_CR3_IREN               (uint32_t)1 << 1
#define UART_CR3_EIE                (uint32_t)1 << 0

//==============================================================================

//________________________________ UART_intrrupts ______________________________
//@ref UART_Interrupt_define
#define En_CR1_Interrupt            (uint32_t)1 << 11
#define En_CR2_Interrupt            (uint32_t)2 << 11
#define En_CR3_Interrupt            (uint32_t)4 << 11

#define En_Error_Inter              (uint32_t)(En_CR3_Interrupt | UART_CR3_EIE)
#define En_Parity_Inter             (uint32_t)(En_CR1_Interrupt | UART_CR1_PEIE)
#define En_Tx_Inter                 (uint32_t)(En_CR1_Interrupt | UART_CR1_TXEIE)
#define En_Tx_Com_Inter             (uint32_t)(En_CR1_Interrupt | UART_CR1_TCIE)
#define En_RX_Inter                 (uint32_t)(En_CR1_Interrupt | UART_CR1_RXNEIE)
#define En_IDLE_Inter               (uint32_t)(En_CR1_Interrupt | UART_CR1_IDLEIE)
#define En_Lin_BK_Inter             (uint32_t)(En_CR2_Interrupt | UART_CR2_LBDIE)
#define En_FlowCt_Inter             (uint32_t)(En_CR3_Interrupt | UART_CR3_CTSIE)

//==============================================================================
//@ref UART_Payload_Length_define
#define Payload_8_bit           0 << 12
#define Payload_9_bit           1 << 12

//@ref UART_Stop_Bit_define
#define Stop_1_bit              0 << 12
#define Stop_Half_bit           1 << 12
#define Stop_1_Half_bit         2 << 12
#define Stop_2_bit              3 << 12

//@ref UART_Rx_Tx_En_define
#define Enable_RX               1 << 2
#define Enable_Tx               1 << 3
#define Enable_RX_Tx            Enable_Tx | Enable_RX 

//@ref UART_Parity_define
#define Parity_None             0 << 10
#define Parity_Even             2 << 9
#define Parity_Odd              3 << 9

//@ref CTS_RTS_En_define
#define CTS_RTS_None            0 << 8
#define Enable_RTS              1 << 8
#define Enable_CTS              1 << 9
#define Enable_RTS_CTS          Enable_CTS | Enable_RTS

//@ref Rx and Tx Polling Mechism 
enum Polling_mechism
{
  Disable = 0,
  Enable
};



//____________________________ UART API ________________________________________
typedef struct _St_Uart_API
{
    St_UART_Typedef *UARTx;                                 // Specifies the UART Peripheral
                                                            // This parameter must be set base on @ref UART_Peripheral_define
    uint32_t baudrate;                                      // This member configures the uart communication baud rate
                                                            // This parameter must be set between 2400 to 4500K
    uint32_t interrupt;                                     // This member configures the uart interrupt
                                                            // This parameter must be set base on @ref UART_Interrupt_define
    uint16_t Word_Len;                                      // This member configures the Payload Length
                                                            // This parameter must be set base on @ref UART_Payload_Length_define
    uint16_t Stop_bit;                                      // This member configures the Stop bit
                                                            // This parameter must be set base on @ref UART_Stop_Bit_define
    uint16_t Mode;                                          // This member configures the uart RX/Tx enable disable
                                                            // This parameter must be set base on @ref UART_Rx_Tx_En_define
    uint16_t Parity;                                        // This member configures the uart parity
                                                            // This parameter must be set base on @ref UART_Parity_define
    uint16_t Hw_Flow_CTRL;                                  // This member configures the uart CTS/RTS Enalbe/Disable
                                                            // This parameter must be set base on @ref CTS_RTS_En_define
    void (*P_Parity_CallBack)(struct _St_Uart_API *UARTx);  // UART Parity CallBack Function pointer
    void (*P_Error_CallBack)(struct _St_Uart_API *UARTx);   // UART Error CallBack Function pointer
    void (*P_Tx_CallBack)(struct _St_Uart_API *UARTx);      // UART Tx CallBack Function pointer 
    void (*P_Tx_Com_CallBack)(struct _St_Uart_API *UARTx);  // UART Tx Complate CallBack Function pointer
    void (*P_Rx_CallBack)(struct _St_Uart_API *UARTx);      // UART Rx CallBack Function pointer
    void (*P_Lin_BK_CallBack)(struct _St_Uart_API *UARTx);  // UART LIN Break CallBack Function pointer
    void (*P_FlowCTR_CallBack)(struct _St_Uart_API *UARTx); // UART CTS/RTS CallBack Function pointer
    void (*P_IDLE_CallBack)(struct _St_Uart_API *UARTx);    // UART IDLE CallBack Function pointer
}St_Uart_API;


//==============================================================================

//____________________________ UART Functions __________________________________
uint8_t Init_Uart(St_Uart_API *Inst);
uint8_t DeInit_Uart(St_Uart_API *Inst);
uint8_t Set_BaudRate(St_Uart_API *Inst);
uint16_t Get_BaudRate(St_Uart_API *Inst);
uint8_t Receive_Char_Uart(St_UART_Typedef *Inst, uint16_t *msg, enum Polling_mechism PollingEn);
uint8_t Send_Char_Uart(St_UART_Typedef *Inst,uint16_t *msg, enum Polling_mechism PollingEn);
uint8_t Receive_String_Uart(St_UART_Typedef *Inst, uint16_t *msg, uint8_t msg_len,enum Polling_mechism PollingEn);
uint8_t Send_String_Uart(St_UART_Typedef *Inst, uint16_t *msg, enum Polling_mechism PollingEn);
void Parity_CallBack_UART(St_Uart_API *UARTx);
void Error_CallBack_UART(St_Uart_API *UARTx);
void Tx_CallBack_UART(St_Uart_API *UARTx);
void Tx_Comp_CallBack_UART(St_Uart_API *UARTx);
void Rx_CallBack_UART(St_Uart_API *UARTx);
void IDLE_CallBack_UART(St_Uart_API *UARTx);
void FlowCt_CallBack_UART(St_Uart_API *UARTx);
void Lin_BK_CallBack_UART(St_Uart_API *UARTx);
//==============================================================================



#endif