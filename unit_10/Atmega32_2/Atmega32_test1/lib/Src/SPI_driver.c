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


//------------------------------- Inculde Files --------------------------------
#include "SPI_driver.h"
#include <avr/io.h>
#include <util/delay.h>
#include "GPIO.h"
#include "LCD_16_2.h"
#include "avr/interrupt.h"
//==============================================================================


//------------------------------ External Objects ------------------------------
extern St_SPI_API spi_confige;
extern volatile LCD_16_2 Lcd_config;
//==============================================================================


//------------------------------- Local Objects --------------------------------

//==============================================================================


//------------------------------ Generaic Objects ------------------------------
#define DDR_SPI         PORT_B
#define DD_SCK          PIN_7
#define DD_MISO         PIN_6
#define DD_MOSI         PIN_5
#define DD_SS           PIN_4
//==============================================================================


/**
 * @brief      : This function is used to initialize the SPI Peripheral
 * @param SPIx : SPI data structure containing the SPI parameters specified by the user 
 * @return uint8_t  0 : Fail
 *                  1 : Success
*/
uint8_t SPI_Init(St_SPI_API *SPIx)
{
    GPIO_config gpio_config = {0};
    if(SPIx->Slave_Master)
    {
        // Set MOSI and SCK and SS output
        gpio_config.mode = OUTPUT;
        gpio_config.pin = DD_SCK | DD_MOSI | DD_SS;
        Init_GPIO(DDR_SPI, &gpio_config);
        // Set MISO as Input
        gpio_config.mode = INPUT;
        gpio_config.pin = DD_MISO;
        Init_GPIO(DDR_SPI, &gpio_config);
    }
    else
    {
        // Set MOSI and SCK and SS INPUT
        gpio_config.mode = INPUT;
        gpio_config.pin = DD_SCK | DD_MOSI | DD_SS;
        Init_GPIO(DDR_SPI, &gpio_config);
        // Set MISO as Output
        gpio_config.mode = OUTPUT;
        gpio_config.pin = DD_MISO;
        Init_GPIO(DDR_SPI, &gpio_config);
    }
    // Confige SPI
    SPCR = (1 << SPE) | (SPIx->Slave_Master) | (SPIx->SPI_Freq) | (SPIx->Data_Order) | (SPIx->En_interrupt) | (SPIx->Data_Modes);

    return 1;
}

/**
 * @brief Send data through SPI as Master
 * @param SPIx : SPI data structure containing the SPI parameters specified by the user 
 * @param data The data to be sent through SPI
 * @return uint8_t  0 : Fail
 *                  1 : Success 
 */
uint8_t SPI_MasterTransmit_Char(St_SPI_API *SPIx ,uint8_t data)
{
    // Select Slave Low
    Write_Pin(DDR_SPI,DD_SS,Low);
    // Start transimission
    SPDR = data;
    // Wait for transmission complate
    while(!(SPSR & (1 << SPIF)));
    // Select slave High
    Write_Pin(DDR_SPI,DD_SS,High);
    return SPDR;    
}


/**
 * @brief Receiving data from the Master
 * @param SPIx : SPI data structure containing the SPI parameters specified by the user  
 * @param data The data to be sent through SPI
 * @return uint8_t  0 : Fail
 *                  1 : Success 
 */
uint8_t SPI_SlaveReceive_Char(St_SPI_API *SPIx, uint8_t data)
{   
    
    SPDR = data;
    // Wait for reception complate 
    while(!(SPSR & (1 << SPIF)));
    // return Data 
    return SPDR;
}


/**
 * @brief Send address and data through SPI as Master
 * @param SPIx : SPI data structure containing the SPI parameters specified by the user 
 * @param Add Address to be sent through SPI
 * @param data The data to be sent through SPI
 * @return uint8_t  0 : Fail
 *                  1 : Success 
 */
uint8_t SPI_MasterTransmit_ADD_Data(St_SPI_API *SPIx ,uint8_t Add, uint8_t data)
{
    // Select Slave Low
    Write_Pin(DDR_SPI,DD_SS,Low);
    // Start transimission
    SPDR = Add;
    // Wait for transmission complate
    while(!(SPSR & (1 << SPIF)));
    // Start transimission
    SPDR = data;
    // Wait for transmission complate
    while(!(SPSR & (1 << SPIF)));
    // Select slave High
    Write_Pin(DDR_SPI,DD_SS,High);
    return SPDR; 
}

