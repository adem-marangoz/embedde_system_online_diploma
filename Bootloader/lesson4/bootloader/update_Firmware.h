/**
 * @file update_Firmware.h
 * @author adem alnajjar (adem.marangoz95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef UPDATE_FIRMWARE_H_
#define UPDATE_FIRMWARE_H_


#include "Stm32f10xx_Address.h"
#include "Stm32f10xx_Common.h"


//------------------------------ Generica Object -------------------------------
#define Page_Size               1024    // 1 KiloByte

//==============================================================================


//---------------------------- Update Firmware API -----------------------------

//==============================================================================


//------------------------------ Global Function -------------------------------
uint8_t update_firmware(void);
uint8_t write_data_into_flash(uint8_t *data, uint16_t data_len, bool is_first);
//==============================================================================

#endif