/**
 * @file Application.h
 * @author adem alnajjar (adem.alnajjar@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

//------------------------------- INCLUDE FILES --------------------------------
#include "Stm32f10xx_GPIO.h"
#include "Stm32f10xx_EXTI.h"
#include "Stm32f10xx_RCC.h"
#include "Stm32f10xx_AFIO.h"
#include "Stm32f10xx_Address.h"
#include "LCD_Driver.h"
#include "Key_pad_Driver.h"
#include "Seven_Segment.h"
#include "Stm32f10x_UART.h"
#include <stdio.h>
#include "Stm32f10x_SPI.h"
#include "Stm32f10xx_I2C.h"
#include "EEPROM.h"
#include "Stm32f10xx_Timers.h"
#include "Stm32_f10xx_Systick.h"
#include "EEPROM_25xx256.h"
#include "Stm32f10xx_Common.h"
//==============================================================================

//------------------------------- DATA STRUCTURE -------------------------------
typedef enum 
{
    Inc = 0,
    Dec
}Inc_Dec_seg;
//==============================================================================


//------------------------------ GLOBAL OBJECTES -------------------------------
void config_Drives_and_Perpherals(void);
void Init_Component(void);
uint8_t Inc_Dec_seven_segment(St_7_segment *seven_segment,Inc_Dec_seg Index);
//==============================================================================


//--------------------------------- FUNCTIONS ----------------------------------

//==============================================================================


#endif