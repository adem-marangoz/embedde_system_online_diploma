/**
 * @file Application.c
 * @author adem mararngoz (adem.marangoz95@gmail.com)
 * @brief This file contains an initialization function to start the program 
 *        and a function that will run continuously
 * @version 0.1
 * @date 2022-05-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "GPIO.h"
#include <avr/io.h>
#include <util/delay.h>
#include "EXTI.h"
#include "avr/interrupt.h"
#include "Seven_Segment.h"
#include "LCD_16_2.h"
#include "Key_pad.h"
#include <stddef.h>
#include "UART_driver.h"

/**
 * @brief In this function, the peripherials are initialized and the variables 
 *        that need to be configured before the program works
 * @arg : None
 * @retval: None
 */
void init(void);

/**
 * @brief In this function, the program is located inside an infinite loop that 
 *        will run continuously
 * @arg : None
 * @retval : None
 */
void program(void);

volatile LCD_16_2 Lcd_config = {0};
volatile St_Key_pad key_pad = {0};

void init(void)
{
	Lcd_config.Data_Port = PORT_A;
	Lcd_config.Enable_Port = PORT_B;
	Lcd_config.RS_Port = PORT_C;
	Lcd_config.R_W_Port = PORT_D;
	Lcd_config.Enable_Pin = PIN_0;
	Lcd_config.R_W_Pin = PIN_2;
	Lcd_config.RS_Pin = PIN_0;
	LCD_init(&Lcd_config);
	// key_pad.input.Port = PORT_B;
	// key_pad.input.Pins = PIN_1|PIN_2|PIN_3|PIN_4;
	// key_pad.output.Port = PORT_C;
	// key_pad.output.Pins =PIN_1|PIN_2|PIN_3|PIN_4;
	// Key_pad_init(&key_pad);

	UART_Config.BuadRate = 9600;
	UART_Config.Char_Size = Eight_bit;
	UART_Config.Clk_Polarity = Rising_Edge;
	UART_Config.Communcation_Mode = Full_Duplex;
	UART_Config.Parity = Disable;
	UART_Config.Mode = Asynchronous;
	UART_Config.Stop = One_bit;
	UART_Config.Speed = Normal_Speed;
	Init_Uart(&UART_Config);
	unsigned char str[] = "You can do it \n\r";
	Uart_Send_String(str);
	Write_String(&Lcd_config,str);
	Jump_to_coordinator(&Lcd_config,0,Seconde_R);
}

uint8_t R_msg = 0;
void program(void)
{ 
	//Check_Prass_Button(&key_pad);
	R_msg = Uart_Receive();
	Write_Character(&Lcd_config,R_msg);
}

