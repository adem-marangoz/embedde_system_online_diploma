/**
 * @file Stm32f10x_SPI.h
 * @author adem marangoz (adem.marangoz@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef STM32F10X_SPI_H_
#define STM32F10X_SPI_H_

//______________________________ Includes ______________________________________
#include "Stm32f10xx_Common.h"
#include "Stm32f10xx_Address.h"
//==============================================================================


//_______________________________ Checks Macro _________________________________

// Check The SPI Instance
#define IS_SPI_ALL_INSTANCE(INSTANCE)   (((INSTANCE) == SPI1)||\
                                        ((INSTANCE) == SPI2)||\
                                        ((INSTANCE) == SPI3))
// Check The SPI BuadRate
#define IS_SPI_BAURDRATE(BaurdRate)     (((BaurdRate) == FPCLK_div_2)||\
                                        ((BaurdRate) == FPCLK_div_4)||\
                                        ((BaurdRate) == FPCLK_div_8)||\
                                        ((BaurdRate) == FPCLK_div_16)||\
                                        ((BaurdRate) == FPCLK_div_32)||\
                                        ((BaurdRate) == FPCLK_div_64)||\
                                        ((BaurdRate) == FPCLK_div_128)||\
                                        ((BaurdRate) == FPCLK_div_256))

// Check The SPI Master Select
#define IS_SPI_MASTER(MASTER)           (((MASTER) == SPI_Slave)||\
                                        ((MASTER) == SPI_Master))

// Check The SPI Send Data Format
#define IS_DATA_FORMATE(DATA_FORMAT)    (((DATA_FORMAT) == LSB_Trans)||\
                                        ((DATA_FORMAT) == MSB_Trans))

// Chack The SPI NSS software
#define IS_SOFTWARE_MANG(SOFTWARE)      (((SOFTWARE) == Software_Mang_Disable)||\
                                        ((SOFTWARE) == Software_Mang_Enable))     

// Check The SPI Data Format
#define IS_DATA_LENG(DATA_LEN)          (((DATA_LEN) == Data_8_bit)||\
                                        ((DATA_LEN) == Data_16_bit))      
                                        
// Check The SPI CLK phase and polarity
#define IS_CLK_PHASE_POLARIYT(CLK)      (((CLK) == Sample_Ris_Setup_Fall)||\
                                        ((CLK) == Setup_Ris_Sample_Fall)||\
                                        ((CLK) == Sample_Fall_Setup_Ris)||\
                                        ((CLK) == Setup_Fall_Sample_Ris))

// Check The SPI interrupt
#define IS_RX_TX_INTERRUPT(INTERRUPT)   (((INTERRUPT) == SPI_interrupt_Dis)||\
                                        ((INTERRUPT) == Tx_Interrupt_En)||\
                                        ((INTERRUPT) == Rx_Tx_Interrupt_En)||\
                                        ((INTERRUPT) == Rx_Interrupt_En))

// Check The SPI Mode
#define IS_SPI_MODE(MODE)               (((MODE) == Full_Duplex)||\
                                        ((MODE) == Hlaf_Duplex_Receive_only)||\
                                        ((MODE) == Half_Duplex_Transmit_only)||\
                                        ((MODE) == Simplex_Only_Rx))

// Check The SPI half duplex mode
#define IS_HALF_DUPLEX_MODE(MODE)       (((MODE) == Output_Dis_Receive_only)||\
                                        ((MODE) == Ouptut_En_Transmit_only))
//==============================================================================


//_______________________________ SPI CR1 ______________________________________

#define CPHA                                        0
#define CPOL                                        1
#define MSTR                                        2
#define BR                                          3
#define SPE                                         6
#define LSB_FIRST                                   7
#define SSI                                         8
#define SSM                                         9
#define RX_ONLY                                     10
#define DFF                                         11
#define CRC_NEXT                                    12
#define CRC_EN                                      13
#define BIDIOE                                      14
#define BIDIMODE                                    15

//==============================================================================


//_________________________________ SPI CR2 ____________________________________

#define RXDMAEN                                     0
#define TXDMAEN                                     1
#define SSOE                                        2
#define ERRIE                                       5
#define RXNEIE                                      6
#define TXEIE                                       7
//==============================================================================


//__________________________________ SPI SR ____________________________________

#define RXNE                                        0
#define TXE                                         1
#define CHSIDE                                      2
#define UDR                                         3
#define CRC_ERR                                     4
#define MODF                                        5
#define OVR                                         6
#define BSY                                         7
//==============================================================================


// @ref SPI_buard_rate_define
#define FPCLK_div_2                                 0
#define FPCLK_div_4                                 1
#define FPCLK_div_8                                 2
#define FPCLK_div_16                                3
#define FPCLK_div_32                                4
#define FPCLK_div_64                                5
#define FPCLK_div_128                               6
#define FPCLK_div_256                               7

// @ref MASTER_Select_define
#define SPI_Slave                                   0
#define SPI_Master                                  1

// @ref Data_Frame_Format_define
#define MSB_Trans                                   0
#define LSB_Trans                                   1

// @ref Software_Slave_Management_define
#define Software_Mang_Disable                       0
#define Software_Mang_Enable                        1

// @ref Data_Frame_Length
#define Data_8_bit                                  0
#define Data_16_bit                                 1

// @ref CLK_Polarity_And_Phase_define
#define Sample_Ris_Setup_Fall                       0
#define Setup_Ris_Sample_Fall                       1
#define Sample_Fall_Setup_Ris                       2
#define Setup_Fall_Sample_Ris                       3

// @ref Rx_Tx_interrupt_En_define
#define SPI_interrupt_Dis                           0
#define Rx_Interrupt_En                             1
#define Tx_Interrupt_En                             2
#define Rx_Tx_Interrupt_En                          3


// @ref SPI_Mode_define
#define Full_Duplex                                 (0 << BIDIMODE) | ( 0 << RX_ONLY)
#define Hlaf_Duplex_Receive_only                    (1 << BIDIMODE)
#define Half_Duplex_Transmit_only                   (1 << BIDIMODE) | (1 << BIDIOE)
#define Simplex_Only_Tx                             Full_Duplex
#define Simplex_Only_Rx                             ( 1 << RX_ONLY)


// @ref Half_Duplex_Mode_define
#define Output_Dis_Receive_only                     0
#define Ouptut_En_Transmit_only                     1


// @ref NSS_Hardware_Mode_define
#define NSS_Hardware_Output_Dis_MultiMaster_En      0
#define NSS_Hardware_Output_En_MultiMaster_Dis      1

enum En_SPI_polling
{
    SPI_Pol_Disable = 0,
    SPI_Pol_Enable
};


//_______________________________ SPI API ______________________________________

typedef struct _St_Spi_API
{
    St_SPI_Typedef *SPI_Inst;                                       // Specifies the SPI Peripheral
    uint16_t SPI_Mode;                                              // This member configures the SPi Mode
                                                                    // This parameter must be set base on @ref SPI_Mode_define
    uint16_t BaudRate;                                              // This member configures the SPi Buad Rate
                                                                    // This parameter must be set base on @ref SPI_buard_rate_define
    uint16_t Master_Select;                                         // This member configures the SPi Master select
                                                                    // This parameter must be set base on @ref MASTER_Select_define
    uint16_t Half_duplex_Mode;                                      // This member configures the SPi half duplex mode
                                                                    // This parameter must be set base on @ref Half_Duplex_Mode_define
    uint16_t NSS_Hardware_Mode;                                     // This member configures the NSS Hardware Mode
                                                                    // This parameter must be set base on @ref NSS_Hardware_Mode_define
    uint16_t Slave_Select_Software;                                 // This member configures the SPi NSS software
                                                                    // This parameter must be set base on @ref Software_Slave_Management_define
    uint16_t Frame_format;                                          // This member configures the SPi Data foramt
                                                                    // This parameter must be set base on @ref Data_Frame_Format_define
    uint16_t Data_Legnth_format;                                    // This member configures the SPi Data length
                                                                    // This parameter must be set base on @ref Data_Frame_Length_define
    uint16_t CLK_Phase_Polarity;                                    // This member configures the SPi CLK polarity and phase
                                                                    // This parameter must be set base on @ref CLK_Polarity_And_Phase_define
    uint16_t Rx_Tx_interrupt;                                       // This member configures the SPi Tx/Rx interrupt
                                                                    // This parameter must be set base on @ref Rx_Tx_interrupt_En_define
    void (*P_Tx_Empty_CallBack)(struct _St_Spi_API* SPIx);          // SPI Tx empty CallBack Function pointer
    void (*P_Rx_Empty_CallBack)(struct _St_Spi_API* SPIx);          // SPI Rx empty CallBack Function pointer
    void (*P_Fault_Event_CallBack)(struct _St_Spi_API* SPIx);       // SPI Fault evnet CallBack Function pointer
    void (*P_Overrun_CallBack)(struct _St_Spi_API* SPIx);           // SPI Overrun CallBack Function pointer
    void (*P_CRC_CallBack)(struct _St_Spi_API* SPIx);               // SPI CRC CallBack Function pointer
}St_SPI_API;

//==============================================================================


//________________________________ Global Function _____________________________

uint8_t Init_SPI(St_SPI_API *SPIx);
void Deinit_SPI(St_SPI_API *SPIx);
uint16_t SPI_Send_Char(St_SPI_API *SPIx,uint16_t *Tx_buffer ,enum En_SPI_polling polling);
uint16_t SPI_Receive_Char(St_SPI_API *SPIx, uint16_t *Rx_buffer,enum En_SPI_polling polling);
uint16_t * SPI_Send_String(St_SPI_API *SPIx , uint16_t *Tx_buffer, uint16_t *Rx_buffer ,uint8_t len, enum En_SPI_polling polling);
uint16_t * SPI_Receive_String(St_SPI_API *SPIx , uint16_t *Rx_buffer, uint8_t len , enum En_SPI_polling polling);
uint16_t * SPI_Tx_Rx_Char(St_SPI_API *SPIx , uint16_t *Rx_buffer, uint16_t *Tx_buffer, uint8_t len_Rx,enum En_SPI_polling polling);
void Tx_Empty_CallBack(St_SPI_API *SPIx);
void RX_Empty_CallBack(St_SPI_API *SPIx);
void Fault_Event_CallBack(St_SPI_API *SPIx);
void Overrun_CallBack(St_SPI_API *SPIx);
void CRC_CallBack(St_SPI_API *SPIx);

//==============================================================================

#endif