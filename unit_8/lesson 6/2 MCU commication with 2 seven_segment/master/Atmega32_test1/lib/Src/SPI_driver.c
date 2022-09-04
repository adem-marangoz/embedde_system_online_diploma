/**
 * @file SPI_driver.c
 * @author adem alnajjar (adem.marangoz95@gmail.com)
 * @brief This Source file is used to define functions
 * @version 0.1
 * @date 2022-09-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "SPI_driver.h"
#include <avr/io.h>
#include "GPIO.h"


#define DDR_SPI         PORT_B
#define DD_SCK          1 << 7
#define DD_MISO         1 << 6
#define DD_MOSI         1 << 5
#define DD_Pin          4

/**
 * @brief Init the SPI
 * @param SPIx 
 * @return uint8_t 
 */
uint8_t SPI_Init(St_SPI_API *SPIx)
{
    if(SPIx->Slave_Master)
    {
        // Set MOSI and SCK output, all others input
        DDR_SPI->Un_DDRx.DDRx = DD_SCK | DD_MOSI;
        // Enable SPI, Master, Set Clock rate fck/16
        SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
    }
    else
    {
        // Set MISO output, all others input
        DDR_SPI->Un_DDRx.DDRx = DD_MISO;
        // Enable SPI
        SPCR = (1 << SPE);
    }
    return 1;
}


uint8_t SPI_MasterTransmit_Char(St_SPI_API *SPIx ,uint8_t data)
{
    Write_Pin(PORT_B, DD_Pin,Low);
    // Start transimission
    SPDR = data;
    // Wait for transmission complate
    while(!(SPSR & (1 << SPIF)));
    
    Write_Pin(PORT_B, DD_Pin,Low);
    return SPDR;    
}


uint8_t SPI_SlaveReceive_Char(St_SPI_API *SPIx)
{
    // Wait for reception complate 
    while(!(SPSR & (1 << SPIF)));
    // return Data 
    return SPDR;
}