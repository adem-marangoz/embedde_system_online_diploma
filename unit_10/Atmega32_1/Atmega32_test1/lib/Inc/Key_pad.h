
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

#include "GPIO.h"

// Main struct config port and pins for key pad
typedef struct 
{
	St_GPIO *Port;
    unsigned char Pins;
}St_key_In_Out;

// 
typedef struct 
{
    St_key_In_Out output;
    St_key_In_Out input;
}St_Key_pad;


uint8_t Key_pad_init(St_Key_pad *key_pad);

void Check_Prass_Button(St_Key_pad *key_pad);


#endif