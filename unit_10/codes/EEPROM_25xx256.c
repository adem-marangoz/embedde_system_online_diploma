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


//------------------------------ Local Objects ---------------------------------
void Send_CMD(uint8_t cmd);
//==============================================================================

// ----------------------------- Generaic Objects ------------------------------
St_SPI_API SPIx = {0}; 
// =============================================================================


// ----------------------------- Global Functions ------------------------------

/**
 * @brief 
 * @param EEPROM_inst 
 */
void Init_EEPROM_25x(St_EEPROM_25xx256_Typedef *EEPROM_inst)
{
    // Config SPI
    SPIx.SPI_Inst = EEPROM_inst->SPI_Instance;
    SPIx.SPI_Mode = Full_Duplex;
    SPIx.BaudRate = FPCLK_div_8;
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
    NSS->Speed = GPIO_SPEED_FREQ_10MHZ;
    NSS->Pin = EEPROM_inst->NSS_Pin;
    Init_GPIO(EEPROM_inst->GPIOx,NSS);

    // Set NSS
    Set_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);

}


void Send_CMD(uint8_t cmd)
{
    uint16_t cmd_temp = cmd;
    // Send 1 byte data
    SPI_Send_Char(&SPIx, &cmd_temp, SPI_Pol_Enable);
}

/**
 * @brief 
 * @param EEPROM_inst 
 * @param Add 
 * @param data 
 * @return uint8_t 
 */
uint8_t Write_Byte_EEPROM_25xx(St_EEPROM_25xx256_Typedef *EEPROM_inst, uint16_t Add, uint8_t data)
{
    // Reset NSS
    Reset_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);

    // Send Write commnad
    Send_CMD(Write_CMD);

    // Send Address
    uint16_t Add_temp[2] = {0};
    // SPI_Send_String(&SPIx , (uint16_t *)&Add_temp, 2, SPI_Pol_Enable);
    SPI_Send_Char(&SPIx, (uint16_t *)&Add_temp, SPI_Pol_Enable);
    SPI_Send_Char(&SPIx, (uint16_t *)&Add_temp, SPI_Pol_Enable);

    // Send 1 byte data
    SPI_Send_Char(&SPIx, (uint16_t *)&data, SPI_Pol_Enable);

    // Set NSS
    Set_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);
    
    return 1;
}


uint8_t Write_Bytes_EEPROM_25xx(St_EEPROM_25xx256_Typedef *EEPROM_inst, uint16_t Add, uint8_t len, uint8_t *data)
{
    // Reset NSS
    Reset_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);
    // Send Address
    uint8_t Add_temp[2] = {(Add >> 8) , (Add & 0x00FF)};
    SPI_Send_String(&SPIx , (uint16_t *)&Add_temp, 2, SPI_Pol_Enable);

    // Send 1 byte data
    SPI_Send_String(&SPIx , (uint16_t *)data, len, SPI_Pol_Enable);

    // Set NSS
    Set_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);

    return 1;
}


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


void Enable_Write_EEPROM_25xx(St_EEPROM_25xx256_Typedef *EEPROM_inst)
{
    // Reset NSS
    Reset_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);
    
    // Send Address
    uint8_t data_temp = En_Write_CMD;
    SPI_Send_Char(&SPIx , (uint16_t *)&data_temp, SPI_Pol_Enable);

    // Set NSS
    Set_pin(EEPROM_inst->GPIOx, EEPROM_inst->NSS_Pin);
    
}
// =============================================================================
