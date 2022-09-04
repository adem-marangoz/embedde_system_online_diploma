/**
 * @file SPI_driver.h
 * @author adem alnajjar (adem.marangoz95@gmail.com)
 * @brief This header is used to define bits and registers and the API for SPI
 * @version 0.1
 * @date 2022-09-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SPI_DERIVER_H_
#define SPI_DERIVER_H_

#include "Common.h"

//__________________________________ SPCR ______________________________________

#define SPIE                        7
#define SPE                         6
#define DORD                        5
#define MSTR                        4
#define CPOL                        3
#define CPHA                        2
#define SPR1                        0
//==============================================================================

//_________________________________ SPSR _______________________________________

#define SPI2X                       0
#define WCOL                        6
#define SPIF                        7
//==============================================================================

//@ref SPI_Interrupt_define
#define Dis_SPI_Interrupt           0 << 7         
#define EN_SPI_Interrupt            1 << 7

//@ref SPI_Data_Order_define
#define Data_Order_MSB              0 << 5
#define Data_Order_LSB              1 << 5

//@ref SPI_Slave_Master_define
#define SPI_Slave                   0 << 4
#define SPI_Master                  1 << 4

//@ref SPI_Data_Modes_define
#define Sample_Ris_Setup_Fall       0
#define Setup_Ris_Sample_Fall       1
#define Sample_Fall_Setup_Ris       2
#define Setup_Fall_Sample_Ris       3

//@ref SPI_Frquecny_define
#define F_OSC_4                     0
#define F_OSC_16                    1
#define F_OSC_64                    2
#define F_OSC_12                    3
#define F_OSC_2                     4
#define F_OSC_8                     5
#define F_OSC_32                    6


enum
{
    Polling_Dis = 0,
    Polling_En
}En_Polling_CTR;

//_________________________________ SPI API ____________________________________

typedef struct
{
    uint8_t En_interrupt;           /* Specifies the SPI mode to be configured
                                       The parameter can be any value of @ref SPI_Interrupt_define*/
    uint8_t Data_Order;             /* Specifies the SPI mode to be configured
                                       The parameter can be any value of @ref SPI_Data_Order_define*/
    uint8_t Slave_Master;           /* Specifies the SPI mode to be configured
                                       The parameter can be any value of @ref SPI_Slave_Master_define*/
    uint8_t Data_Modes;             /* Specifies the SPI mode to be configured 
                                        The paremeter can be any value of @ref SPI_Data_Modes_define*/
    uint8_t SPI_Freq;               /* Specifies the SPI mode to be configured 
                                        The parameter can be any value of @ref SPI_Frquecny_define*/
}St_SPI_API;


//==============================================================================

//______________________________ Global Function _______________________________

uint8_t SPI_Init(St_SPI_API *SPIx);
uint8_t SPI_MasterTransmit_Char(St_SPI_API *SPIx ,uint8_t data);
uint8_t SPI_SlaveReceive_Char(St_SPI_API *SPIx, uint8_t data);

//==============================================================================
#endif