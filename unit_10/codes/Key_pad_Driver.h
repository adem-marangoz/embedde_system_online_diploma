
/**
 * @file Key_pad.h
 * @author adem mararngoz (adem.marangoz95@gmail.com)
 * @brief This file contains all the definitions by which the input and
 *        output Key pad
 * @version 0.1
 * @date 2022-08-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef KEY_PAD_H_
#define KEY_PAD_H_

#include "Stm32f10xx_GPIO.h"

#define Input_Output_Pins_Num           4
#define KeyPad_Drain                    3
#define KeyPad_Source                   4
// Main struct config port and pins for key pad
typedef struct 
{
	St_GPIO_Typedef *Port;
    uint32_t Pins;
}St_key_In_Out;


// Struct input and output keypad 
typedef struct 
{
    St_key_In_Out Drain;
    St_key_In_Out Soruce;
}St_Key_pad;


uint8_t Key_pad_init(St_Key_pad *key_pad);
uint8_t Check_Prass_Button(St_Key_pad const *key_pad);
void Reaction_Of_Prass(uint32_t Soruce_pin_index, uint32_t Drain_pin_index);
uint8_t Check_Key_Soruce_Pins(St_Key_pad const *key_pad);
void Set_Key_Drain_Pins(St_Key_pad const *key_pad);

#endif