/**
 * @file Seven_Segment.h
 * @author adem marangoz (adem.marangoz95@gmail.com)
 * @brief seven_segment driver
 * @version 0.1
 * @date 2022-08-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SEVEN_SEGMENT
#define SEVEN_SEGMENT

#include "Stm32f10xx_GPIO.h"
#include "Stm32f10xx_Common.h"


// Main struct config port and pins for seven segment
typedef struct 
{
	St_GPIO_Typedef *Port;
    uint16_t Pin_D[4];
}St_7_segment;

void init_seven_segment(St_7_segment const *seven_segment);
void Display_seven_segment(St_7_segment *seven_segment, uint8_t index);


#endif