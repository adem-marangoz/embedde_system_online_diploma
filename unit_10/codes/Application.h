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

typedef enum
{
    Green = 0,
    Red
}En_Led_state;

typedef enum
{
	_byte = 0,
	_half_word,
    _word = 4
}data_type;
//==============================================================================


//------------------------------ GLOBAL OBJECTES -------------------------------
void config_Drives_and_Perpherals(void);
void Init_Component(void);
uint8_t Inc_Dec_seven_segment(St_7_segment *seven_segment,Inc_Dec_seg Index);
void Reaction_Of_Prass(uint32_t Soruce_pin_index, uint32_t Drain_pin_index);
void Run_Led(En_Led_state state);
void Clear_Buffer(uint8_t *buff, uint8_t st_index, uint8_t end_index);
void Convert_uint8_t_to_uint16_t(uint16_t *_16_buff, uint8_t *_8_buff, uint8_t st_16_index, uint8_t st_8_index, uint8_t len);
uint64_t Convert_Buffer8_to_Variable(uint8_t *Buff, uint8_t len);
uint64_t Convert_Buffer16_to_Variable(uint16_t *Buff, uint8_t len);
uint8_t search_char(uint8_t *buff1, uint8_t *buff2, uint8_t buff1_len, uint8_t buff2_len, data_type type);
uint8_t comapre_two_string(uint8_t *buff1, uint8_t *buff2, uint8_t len);
//==============================================================================


//--------------------------------- FUNCTIONS ----------------------------------

//==============================================================================


#endif