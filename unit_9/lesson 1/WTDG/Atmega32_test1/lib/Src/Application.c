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
#include "SPI_driver.h"
#include "I2C_driver.h"
#include "Time0.h"
#include "WTDG.h"

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

//____________________________ Genaric Objectes ________________________________
volatile LCD_16_2 Lcd_config = {0};
volatile St_Key_pad key_pad = {0};
St_SPI_API spi_confige = {0};
St_I2C_API i2c_confige = {0};
//==============================================================================

//_____________________________ Local Variables ________________________________

uint8_t R_msg[16] = {0};
//==============================================================================

//_____________________________ MACRO Definition _______________________________
#define Master			1
//==============================================================================

void init(void)
{
// Config Pins
	GPIO_config gpio_config = {0};
	gpio_config.mode = OUTPUT;
	gpio_config.pin = PIN_0;
	Init_GPIO(PORT_A,&gpio_config);
// Config WTDG
	WTDG_Init(Almost_2s);
	Write_Pin(PORT_A,PIN_0,High);
	
	sei();


}

void program(void)
{ 	
	WTDG_Start();
	_delay_ms(500);
	Toggle_pin(PORT_A,PIN_0);
	WTDG_Stop();

}

