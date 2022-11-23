/**
 * @file Servo_sg90.h
 * @author adem alnajjar (adem.alnajjar95@gmail.com)
 * @brief Servo_SG90_Driver
 * @version 0.1
 * @date 2022-11-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SERVO_SG90_H_
#define SERVO_SG90_H_

//------------------------------- Include Files --------------------------------
#include "Common.h"
//==============================================================================

//------------------------------ GENERAIC OBJECTS ------------------------------
#define positive_90_angle               1999
#define _0_angle                        1499        
#define negative_90_angle               999
//==============================================================================


//------------------------------ Global Functions ------------------------------
uint8_t config_servo_timer();
uint16_t Set_angle(uint16_t value);
//==============================================================================


#endif