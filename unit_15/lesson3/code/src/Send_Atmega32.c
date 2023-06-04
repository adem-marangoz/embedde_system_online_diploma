/**
 * @file Send_Atmega32.c
 * @author adem alnajjar (adem.alnajjar95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//------------------------------- INCLUDE FILES --------------------------------
#include "Send_Atmega32.h"
#include "Stm32f10xx_GPIO.h"
#include "string.h"
//==============================================================================


//------------------------------ GENERAIC OBJECTS ------------------------------
St_GPIO_Typedef *NSS_Ports_SPI1[2] = {SPI1_NSS2_PORT , SPI1_NSS3_PORT};
uint16_t NSS_Pins_SPI1[2] = {SPI1_NSS2_PIN, SPI1_NSS3_PIN};
//==============================================================================


//------------------------------ GLOBAL FUNCTIONS ------------------------------
uint8_t Send_to_controller(St_SPI_API *SPIx, uint8_t controller , uint16_t command)
{
    uint8_t retval = 0;
    uint16_t Rx_temp_Buf[2] = {0};
    Reset_pin(NSS_Ports_SPI1[controller], NSS_Pins_SPI1[controller]);
    SPI_Tx_Rx_Char(SPIx, Rx_temp_Buf, &command, 1,SPI_Pol_Enable);
    Set_pin(NSS_Ports_SPI1[controller], NSS_Pins_SPI1[controller]);
    return retval;
}
//==============================================================================


//------------------------------- DATA STRUCTURE -------------------------------

//==============================================================================