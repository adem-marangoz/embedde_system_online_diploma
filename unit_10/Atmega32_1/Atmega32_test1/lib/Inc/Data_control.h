/**
 * @file Data_control.h
 * @author adem alnajjar (adem.alnajjar95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef DATA_CONTROL_H_
#define DATA_CONTROL_H_

//------------------------------- INCLUDE FILES --------------------------------
#include "Common.h"
//==============================================================================


//------------------------------ GENERAIC OBJECTS ------------------------------
#define Open_entry_gate1                    0x11
#define Close_entry_gate1                   0x10
#define Open_exit_gate2                     0x21
#define Close_exit_gate2                    0x22
//==============================================================================


//------------------------------- DATA STRUCTURE -------------------------------

//==============================================================================


//------------------------------ GLOBAL FUNCTIONS ------------------------------
uint8_t Data_analysis(uint8_t *data);
//==============================================================================




#endif