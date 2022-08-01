/**
 * @file GPIO.c
 * @author adem mararngoz (adem.marangoz95@gmail.com)
 * @brief This file contains all the functions that control the input and
 * 	      output of the pin
 * @version 0.1
 * @date 2022-05-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "GPIO.h"
#include "EXTI.h"

uint8_t Init_GPIO(St_GPIO *GPIO,GPIO_config *GPIO_config_t)
{
  
    if(!(Check_PORT(GPIO))){return 0;}

	uint8_t io_position = 0;
	uint8_t io_current = 0;
	uint8_t temp = 0;
	for(uint8_t pos = 0 ; pos < GPIO_Number ; pos++)
	{
		io_position = 0x01 << pos;
		io_current = io_position & GPIO_config_t->pin;
		if(io_position == io_current)
		{
			if(GPIO_config_t->mode == OUTPUT)
			{
				temp = GPIO->DDRx;
				temp &= (~(GPIO_config_t->mode << pos));
				temp |= (GPIO_config_t->mode << pos);
				GPIO->DDRx = temp;
			}

			if((GPIO_config_t->mode & EXTI_Mask) == EXTI_Mask)
			{
				if ((io_current == PIN_0) || (io_current == PIN_1))
				{
					temp = MCUCR;
					temp &= (~((GPIO_config_t->mode & EXTI_Mask) << pos*0x02));
					temp |= ((GPIO_config_t->mode & EXTI_Mask) << pos*0x02);
					MCUCR = temp;
				}

				if(io_current == PIN_2)
				{
					temp = MCUCSR;
					temp &= (~((GPIO_config_t->mode & EXTI_2_Mask) << 0x05));
					temp |= ((GPIO_config_t->mode & EXTI_2_Mask) << 0x05);
					MCUCSR = temp;
				}
			}
		}
	}
    return 1;
}


uint8_t Write_Pin(St_GPIO *GPIO, uint8_t Pin,St_Pin_State state)
{
    if(!(Check_PORT(GPIO))){return 0;}

	if(state == High){GPIO->PORTx |= Pin;}
	else {GPIO->PORTx &= ~(Pin);}

	return 1;
}

St_Pin_State Read_Pin(St_GPIO *GPIO, uint8_t Pin)
{
    if(!(Check_PORT(GPIO))){return 0;}

    if((GPIO->PINx & Pin) == High) {return High;}
    else {return Low;}
}


void Toggle_pin(St_GPIO *GPIO,uint8_t Pin)
{
	if(!(Check_PORT(GPIO))){return;}

	GPIO->PORTx ^= Pin;
}

void Write_Port_Register(St_GPIO *GPIO,uint8_t Pin)
{
	if(!(Check_PORT(GPIO))){return;}
	GPIO->PORTx = Pin;
}