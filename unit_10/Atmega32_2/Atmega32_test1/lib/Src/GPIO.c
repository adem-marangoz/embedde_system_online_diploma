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

unsigned char Init_GPIO(St_GPIO *GPIO,GPIO_config *GPIO_config_t)
{
  
    if(!(Check_PORT(GPIO))){return 0;}

	unsigned char io_position = 0;
	unsigned char io_current = 0;
	unsigned char temp = 0;
	for(unsigned char pos = 0 ; pos < GPIO_Number ; pos++)
	{
		io_position = 0x01 << pos;
		io_current = io_position & GPIO_config_t->pin;
		if(io_position == io_current)
		{
			if(GPIO_config_t->mode == OUTPUT)
			{
				temp = GPIO->Un_DDRx.DDRx;
				temp &= (~(GPIO_config_t->mode << pos));
				temp |= (GPIO_config_t->mode << pos);
				GPIO->Un_DDRx.DDRx = temp;
			}

			if((GPIO_config_t->mode & EXTI_Mask) == EXTI_Mask)
			{
				if (GPIO == PORT_D)
				{
					temp = MCUCR;
					if(io_current == PIN_2)
					{
						temp &= 0xFC;
						temp |= GPIO_config_t->mode & 0x03; 
					}else if (io_current == PIN_3)
					{
						temp &= 0xF3;
						temp |= (GPIO_config_t->mode << 2) & 0x0C;
					}
					MCUCR = temp;
				}

				if((io_current == PIN_2) && GPIO == PORT_B)
				{
					temp = MCUCSR;
					temp &= (~((GPIO_config_t->mode & EXTI_2_Mask) << 0x06));
					temp |= ((GPIO_config_t->mode & EXTI_2_Mask) << 0x06);
					MCUCSR = temp;
				}
			}
		}
	}
    return 1;
}


unsigned char Write_Pin(St_GPIO *GPIO, unsigned char Pin,St_Pin_State state)
{
    if(!(Check_PORT(GPIO))){return 0;}

	if(state == High){GPIO->Un_PORTx.PORTx |= Pin;}
	else {GPIO->Un_PORTx.PORTx &= ~(Pin);}

	return 1;
}

St_Pin_State Read_Pin(St_GPIO *GPIO, unsigned char Pin)
{
    if(!(Check_PORT(GPIO))){return 0;}

    if((GPIO->Un_PINx.PINx & Pin) == Pin) {return High;}
    else {return Low;}
}

unsigned char Read_Pins(St_GPIO *GPIO)
{
	if(!(Check_PORT(GPIO))){return 0;}
	return (GPIO->Un_PINx.PINx);

}

void Toggle_pin(St_GPIO *GPIO,unsigned char Pin)
{
	if(!(Check_PORT(GPIO))){return;}

	GPIO->Un_PORTx.PORTx ^= Pin;
}

void Write_Port_Register(St_GPIO *GPIO,unsigned char Pin)
{
	if(!(Check_PORT(GPIO))){return;}
	GPIO->Un_PORTx.PORTx = Pin;
}

void Change_Direction(St_GPIO *GPIO,unsigned char Pin,En_Pin_config state)
{
	if(!(Check_PORT(GPIO))){return;}
	switch (Pin)
	{
	case PIN_0:
		GPIO->Un_DDRx.DDRx_bit.Pin0 = state;
		break;
	case PIN_1:
		GPIO->Un_DDRx.DDRx_bit.Pin1 = state;
		break;
	case PIN_2:
		GPIO->Un_DDRx.DDRx_bit.Pin2 = state;
		break;
	case PIN_3:
		GPIO->Un_DDRx.DDRx_bit.Pin3 = state;
		break;
	case PIN_4:
		GPIO->Un_DDRx.DDRx_bit.Pin4 = state;
		break;
	case PIN_5:
		GPIO->Un_DDRx.DDRx_bit.Pin5 = state;
		break;
	case PIN_6:
		GPIO->Un_DDRx.DDRx_bit.Pin6 = state;
		break;
	case PIN_7:
		GPIO->Un_DDRx.DDRx_bit.Pin7 = state;
		break;
	
	default:
		break;
	}
}

void Write_Dir_Register(St_GPIO *GPIO,unsigned char Pin)
{
	if(!(Check_PORT(GPIO))){return;}
	GPIO->Un_DDRx.DDRx = Pin;
}