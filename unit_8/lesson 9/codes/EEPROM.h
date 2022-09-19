/**
 * @file EEPROM.h
 * @author adem alnajjar (adem.marangoz95@gmail.com)
 * @brief The EEPROM API using I2C
 * @version 0.1
 * @date 2022-09-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef EEPROM_H_
#define EEPROM_H_

//_____________________________ Include Files __________________________________
#include "Stm32f10xx_Common.h"
//==============================================================================


//______________________________ Generic Macro _________________________________

#define EEPROM_Address                      0x2A

//==============================================================================


//______________________________ Global Functions ______________________________

uint8_t EEPORM_Init(void);
uint8_t EEPROM_Write_NBytes(uint16_t Memory_Add, uint8_t *data, uint8_t data_length);
uint8_t EEPROM_Read_Byte(uint16_t Memory_Add, uint8_t *data, uint8_t data_length);
//==============================================================================




#endif