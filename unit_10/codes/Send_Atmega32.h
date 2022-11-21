/**
 * @file Send_Atmega32.h
 * @author adem alnajjar (adem.alnajjar95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SEND_ATMEGA32_H_
#define SEND_ATMEGA32_H_

//------------------------------- INCLUDE FILES --------------------------------
#include "defines.h"
#include "Stm32f10xx_Common.h"
#include "Stm32f10x_SPI.h"

//==============================================================================


//------------------------------ GENERAIC OBJECTS ------------------------------
#define Vehicle_entry_controller            0
#define Vehicle_exit_controller             1
#define Open_entry_gate1                    0x11
#define Close_entry_gate1                   0x10
#define Open_exit_gate2                     0x21
#define Close_exit_gate2                    0x22

//==============================================================================


//------------------------------ GLOBAL FUNCTIONS ------------------------------
uint8_t Send_to_controller(St_SPI_API *SPIx, uint8_t controller , uint16_t command);
//==============================================================================


//------------------------------- DATA STRUCTURE -------------------------------

//==============================================================================

#endif