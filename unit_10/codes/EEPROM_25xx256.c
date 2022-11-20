/**
 * @file EEPROM_25xx256.c
 * @author adem alnajjar (adem.alnajjar95@gmail.com)
 * @brief 25xx2567 eeprom
 * @version 0.1
 * @date 2022-10-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */


// ----------------------------- Include Files ---------------------------------
#include "EEPROM_25xx256.h"
#include <stdio.h>
#include "Stm32_f10xx_Systick.h"

// =============================================================================

//------------------------------ Extern Objects --------------------------------

//==============================================================================

//------------------------------ Local Objects ---------------------------------
uint8_t Status_EEPROM(St_EEPROM_25xx256_Typedef *EEPROM_inst);
uint8_t Busy_EEPROM(St_EEPROM_25xx256_Typedef *EEPROM_inst);
//==============================================================================

// ----------------------------- Generaic Objects ------------------------------
// =============================================================================


// ----------------------------- Global Functions ------------------------------

/**
 * @brief Is usded to config SPI and NSS pin
 * @param EEPROM_inst Data Structre for EEPROM 25LC256 API
 */
void Init_EEPROM_25x(St_EEPROM_25xx256_Typedef *EEPROM_inst)
{    
    // Extra Config EEPROM befor start write and read from EEPROM
}



/**
 * @brief Is used to check status of EEPROM
 * @param EEPROM_inst Data Structre for EEPROM 25LC256 API
 * @return status of EEPROM 25LC256 
 */
uint8_t Status_EEPROM(St_EEPROM_25xx256_Typedef *EEPROM_inst)
{
    // Reset NSS
    Reset_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);

    uint16_t status;
    uint16_t data = Read_St_CMD; 
    SPI_Tx_Rx_Char(EEPROM_inst->EEPROM_SPI, &status, &data, 1,SPI_Pol_Enable);
    // Set NSS
    Set_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);
    
    return (uint8_t)status;
}


/**
 * @brief Is used to check if EEPROM is busy
 * @param EEPROM_inst Data Structre for EEPROM 25LC256 API
 * @return uint8_t 1 : EEPROM is busy
 *                 0 : EEPROM is not busy
 */
uint8_t Busy_EEPROM(St_EEPROM_25xx256_Typedef *EEPROM_inst)
{
    uint8_t busy = Status_EEPROM(EEPROM_inst);
    return (busy & WIP);
}

/**
 * @brief Is used to send 1 byte to EEPROM
 * @param EEPROM_inst Data Structre for EEPROM 25LC256 API
 * @param Add destination EEPORM address to write
 * @param data destination data to write to EEPROM
 * @return uint8_t 
 */
uint8_t Write_Byte_EEPROM_25xx(St_EEPROM_25xx256_Typedef *EEPROM_inst, uint16_t Add, uint16_t data)
{

//-------------------------- Write to EEPROM ----------------------------------- 
    // Reset NSS
    Reset_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);
    uint16_t Add_temp;
    uint16_t * Rx_Buff = NULL;
    // Send Write commnad
    Add_temp = Write_CMD;
    SPI_Tx_Rx_Char(EEPROM_inst->EEPROM_SPI,Rx_Buff,&Add_temp, 1,SPI_Pol_Enable);

    // Send Address
    Add_temp = Add >> 8;
    SPI_Tx_Rx_Char(EEPROM_inst->EEPROM_SPI,Rx_Buff,&Add_temp, 1,SPI_Pol_Enable);
    Add_temp = Add & 0x00FF;
    SPI_Tx_Rx_Char(EEPROM_inst->EEPROM_SPI,Rx_Buff,&Add_temp, 1,SPI_Pol_Enable);

    // Send 1 byte data
    uint16_t data1 = data & 0x00FF;
    SPI_Tx_Rx_Char(EEPROM_inst->EEPROM_SPI,Rx_Buff,&data1, 1,SPI_Pol_Enable);
    
    // Set NSS
    Set_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);
    
    return 1;
}


/**
 * @brief 
 * @param EEPROM_inst Data Structre for EEPROM 25LC256 API
 * @param Add start destination EEPORM address to write
 * @param len The number of data to be stored
 * @param data destination data to write to EEPROM
 * @return uint8_t 
 */
uint8_t Write_Bytes_EEPROM_25xx(St_EEPROM_25xx256_Typedef *EEPROM_inst, uint16_t Add, uint8_t len, uint16_t *data)
{
//----------------------------- Enable Write -----------------------------------
    Enable_Write_EEPROM_25xx(EEPROM_inst);
    delay_us(2000);
//-------------------------- Write to EEPROM ----------------------------------- 
    // Reset NSS
    Reset_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);
    uint16_t Add_temp;
    uint16_t * Rx_Buff = NULL;
    // Send Write commnad
    Add_temp = Write_CMD;
    SPI_Tx_Rx_Char(EEPROM_inst->EEPROM_SPI, Rx_Buff, &Add_temp, 1,SPI_Pol_Enable);

    // Send Address
    Add_temp = Add >> 8;
    SPI_Tx_Rx_Char(EEPROM_inst->EEPROM_SPI, Rx_Buff, &Add_temp, 1,SPI_Pol_Enable);
    Add_temp = Add & 0x00FF;
    SPI_Tx_Rx_Char(EEPROM_inst->EEPROM_SPI, Rx_Buff, &Add_temp, 1,SPI_Pol_Enable);

    SPI_Send_String(EEPROM_inst->EEPROM_SPI, data, Rx_Buff, len, SPI_Pol_Enable);

    // Set NSS
    Set_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);
    
    delay_us(2000);

    return 1;
}


/**
 * @brief Is used to read data form EEPROM
 * @param EEPROM_inst Data Structre for EEPROM 25LC256 API
 * @param Add destination EEPORM address to read
 * @return uint8_t 
 */
uint16_t Read_Byte_EEPROM_25xx(St_EEPROM_25xx256_Typedef *EEPROM_inst, uint16_t Add, uint8_t len, uint16_t *Rx_buffer)
{

    // Reset NSS
    Reset_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);
    uint16_t Add_temp;

    // Send Write commnad
    Add_temp = Read_CMD;
    SPI_Tx_Rx_Char(EEPROM_inst->EEPROM_SPI,Rx_buffer,&Add_temp, 1,SPI_Pol_Enable);

    // Send Address
    Add_temp = Add >> 8;
    SPI_Tx_Rx_Char(EEPROM_inst->EEPROM_SPI,Rx_buffer,&Add_temp, 1,SPI_Pol_Enable);
    Add_temp = Add & 0x00FF;
    SPI_Tx_Rx_Char(EEPROM_inst->EEPROM_SPI,Rx_buffer,&Add_temp, len,SPI_Pol_Enable);

    // Set NSS
    Set_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);
    

    return Rx_buffer[0];
}


/**
 * @brief Is used to Enable Write to EEPROM 
 * @param EEPROM_inst Data Structre for EEPROM 25LC256 API
 */
void Enable_Write_EEPROM_25xx(St_EEPROM_25xx256_Typedef *EEPROM_inst)
{
    // Reset NSS
    Reset_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);
    
    // Send Address
    uint16_t data_temp = En_Write_CMD;
    uint16_t * Rx_Buff = NULL;
    // SPI_Send_Char(&SPIx,(uint16_t *)&data_temp,SPI_Pol_Enable);
    SPI_Tx_Rx_Char(EEPROM_inst->EEPROM_SPI,Rx_Buff ,&data_temp, 1,SPI_Pol_Enable);

    // Set NSS
    Set_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);
    
}


// =============================================================================
