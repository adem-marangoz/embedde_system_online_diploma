/**
 * @file Max7221_driver.c
 * @author adem alnajjar (adem.marangoz95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Max7221_driver.h"
#include "SPI_driver.h"

extern St_SPI_API spi_confige;

/**
 * @brief Configuration of MAX7221 with default settings
 */
void Max7212_Default_Init(void)
{
    SPI_MasterTransmit_ADD_Data(&spi_confige,Command_Decode_Mode,Code_B_Digit0_7);
    
    SPI_MasterTransmit_ADD_Data(&spi_confige,Commnad_Intensity,0xFF);
    
    SPI_MasterTransmit_ADD_Data(&spi_confige,Command_Scan_Limit,Display_Digit0To7);
    
    SPI_MasterTransmit_ADD_Data(&spi_confige,Command_Shoutdown,Normal_Operation);
    
    SPI_MasterTransmit_ADD_Data(&spi_confige,Command_Display_Test,Dispaly_Test_Mode);

    SPI_MasterTransmit_ADD_Data(&spi_confige,Command_Display_Test,Normal_Operation_Test);

    
}

/**
 * @brief Send a command to the MAX7221 directly
 * @param command The command to send to MAX7221
 * @param data The data to send to MAX7221
 */
void Max7221_Send_Command_with_data(uint8_t command, uint8_t data)
{
    SPI_MasterTransmit_ADD_Data(&spi_confige,command,data);
}


/**
 * @brief turning on MAX7221
 */
void Max7221_On(void)
{
    SPI_MasterTransmit_ADD_Data(&spi_confige,Command_Shoutdown,Normal_Operation);
}


/**
 * @brief turning off MAX7221
 */
void Max7221_Off(void)
{
    SPI_MasterTransmit_ADD_Data(&spi_confige,Command_Shoutdown,No_decode_7_0);
}
