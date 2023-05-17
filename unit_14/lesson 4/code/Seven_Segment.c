/**
 * @file Seven_Segment.c
 * @author adem alnajjar (adem.alnajjar95@gmail.com)
 * @brief This soruce file for run 7 segment base on stm32f10xx
 * @version 0.1
 * @date 2022-10-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//---------------------------------- NOTES --------------------------------------
/*
    - The ability to show a number on 7-segment provided that they are all on 
    the same port. The pin order does not matter,
*/
//==============================================================================

#include "Seven_Segment.h"

uint32_t numbers[10] = {0};

/**
 * @brief This function is to be used to configure ports and pins seven segment
 * @param[in] seven_segment The seven_segment data structure containing the port and pins to be configured
 */
void init_seven_segment(St_7_segment const *seven_segment)
{
    GPIO_InitTypeDef gpio_seven_out = {0};
    gpio_seven_out.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_seven_out.Speed = GPIO_SPEED_FREQ_10MHZ;
    gpio_seven_out.Pin = seven_segment->Pin_D[0] | seven_segment->Pin_D[1] | seven_segment->Pin_D[2] | seven_segment->Pin_D[3];
    Init_GPIO(seven_segment->Port,&gpio_seven_out); 
   
}

/**
 * @brief To print numbers on seven segment
 * @param[in] seven_segment The seven_segment data structure containing the port and pins to be configured
 * @param index The number to be printed
 */
uint8_t Display_seven_segment(St_7_segment *seven_segment, uint8_t index)
{
    if(index > 16){return 0;}
    uint8_t temp = 0;
    for (uint8_t i = 0; i < 4; i++)
    {
        //temp = index & (1 << i) > 0 ? GPIO_PIN_SET : GPIO_PIN_RESET;
        if(index & (1 << i))
            temp = GPIO_PIN_SET;
        else
            temp = GPIO_PIN_RESET;
        Change_State_Pin(seven_segment->Port, seven_segment->Pin_D[i], temp);
    }
    return 1;
}