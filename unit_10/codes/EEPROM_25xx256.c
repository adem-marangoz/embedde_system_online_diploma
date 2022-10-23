/**
 * @file EEPROM_25xx256.c
 * @author adem alnajjar (adem.alnajjar95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */


// ----------------------------- Include Files ---------------------------------
#include "EEPROM_25xx256.h"

// =============================================================================

//------------------------------ Extern Objects --------------------------------
extern uint16_t Rx_Buff[10];
//==============================================================================

//------------------------------ Local Objects ---------------------------------
void Send_CMD(uint16_t cmd);
uint8_t Status_EEPROM(St_EEPROM_25xx256_Typedef *EEPROM_inst);
uint8_t Busy_EEPROM(St_EEPROM_25xx256_Typedef *EEPROM_inst);
//==============================================================================

// ----------------------------- Generaic Objects ------------------------------
St_SPI_API SPIx = {0}; 
// =============================================================================


// ----------------------------- Global Functions ------------------------------

/**
 * @brief Is usded to config SPI and NSS pin
 * @param EEPROM_inst Data Structre for EEPROM 25LC256 API
 */
void Init_EEPROM_25x(St_EEPROM_25xx256_Typedef *EEPROM_inst)
{
    // Config SPI
    SPIx.SPI_Inst = EEPROM_inst->SPI_Instance;
    SPIx.SPI_Mode = Full_Duplex;
    SPIx.BaudRate = FPCLK_div_2;
    SPIx.Master_Select = SPI_Master;
    SPIx.NSS_Hardware_Mode = NSS_Hardware_Output_Dis_MultiMaster_En;
    SPIx.Slave_Select_Software = Software_Mang_Enable;
    SPIx.Frame_format = MSB_Trans;
    SPIx.Data_Legnth_format = Data_8_bit;
    SPIx.CLK_Phase_Polarity = Setup_Fall_Sample_Ris;
    SPIx.Rx_Tx_interrupt = SPI_interrupt_Dis;
    Init_SPI(&SPIx);

    // Config NSS Pin
    GPIO_InitTypeDef *NSS = {0};
    NSS->Mode = GPIO_MODE_OUTPUT_PP;
    NSS->Speed = GPIO_SPEED_FREQ_2MHZ;
    NSS->Pin = EEPROM_inst->NSS_Pin;
    Init_GPIO(EEPROM_inst->GPIOx,NSS);

    // Set NSS
    Set_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);

}

/**
 * @brief Is used to Send command to EEPROM
 * @param cmd command value
 */
void Send_CMD(uint16_t cmd)
{    
    // Send 1 byte data
    cmd &= 0x00FF;
    SPI_Send_Char(&SPIx,&cmd,SPI_Pol_Enable);
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
    SPI_Tx_Rx_Char(&SPIx, &status, &data, SPI_Pol_Enable);
    // Set NSS
    Set_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);
    return status;
}


/**
 * @brief Is used to check if EEPROM is busy
 * @param EEPROM_inst Data Structre for EEPROM 25LC256 API
 * @return uint8_t 1 : EEPROM is busy
 *                 0 : EEPROM is not busy
 */
uint8_t Busy_EEPROM(St_EEPROM_25xx256_Typedef *EEPROM_inst)
{
    uint8_t busy = Status_EEPROM();
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

//-------------------------- Check BUSY EEPROM ---------------------------------
    while(Busy_EEPROM(EEPROM_inst) == 1);

//-------------------------- Write to EEPROM ----------------------------------- 
    // Reset NSS
    Reset_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);

    // Send Write commnad
    Send_CMD(Write_CMD);

    // Send Address
    uint16_t Add_temp[2];
    Add_temp[0] = Add >> 8;
    Add_temp[1] = Add & 0x00FF;
    SPI_Send_String(&SPIx , Add_temp, 2, SPI_Pol_Enable);

    // Send 1 byte data
    data &= 0x00FF;
    // SPI_Tx_Rx_Char(&SPIx,Rx_Buff,&data1,SPI_Pol_Enable);
    SPI_Send_Char(&SPIx, &data, SPI_Pol_Enable);

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

//-------------------------- Check BUSY EEPROM ---------------------------------
    while(Busy_EEPROM(EEPROM_inst) == 1);

//-------------------------- Write to EEPROM ----------------------------------- 
    // Reset NSS
    Reset_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);
    // Send Address
    uint16_t Add_temp[2];
    Add_temp[0] = Add >> 8;
    Add_temp[1] = Add & 0x00FF;
    SPI_Send_String(&SPIx , Add_temp, 2, SPI_Pol_Enable);

    // Send 1 byte data
    SPI_Send_String(&SPIx , data, len, SPI_Pol_Enable);

    // Set NSS
    Set_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);

    return 1;
}


/**
 * @brief Is used to read data form EEPROM
 * @param EEPROM_inst Data Structre for EEPROM 25LC256 API
 * @param Add destination EEPORM address to read
 * @return uint8_t 
 */
uint8_t Read_Byte_EEPROM_25xx(St_EEPROM_25xx256_Typedef *EEPROM_inst, uint16_t Add)
{
    // Reset NSS
    Reset_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);

    // Send Address
    uint8_t Add_temp[2] = {(Add >> 8) , (Add & 0x00FF)};
    SPI_Send_String(&SPIx , (uint16_t *)&Add_temp, 2, SPI_Pol_Enable);

    // Set NSS
    Set_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);

    return 1;
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
    SPI_Send_Char(&SPIx,(uint16_t *)&data_temp,SPI_Pol_Enable);

    // Set NSS
    Set_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);
    
}


// =============================================================================
