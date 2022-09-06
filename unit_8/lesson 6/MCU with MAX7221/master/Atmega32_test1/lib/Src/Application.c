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

#define F_CPU       1000000UL

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
St_SPI_API spi_confige = {0};


uint8_t R_msg[16] = {0};

void init(void)
{
// Confige The SPI
	spi_confige.Data_Modes = Sample_Ris_Setup_Fall;
	spi_confige.Data_Order = Data_Order_MSB;
	spi_confige.En_interrupt = Dis_SPI_Interrupt;
	spi_confige.Slave_Master = SPI_Master;
	spi_confige.SPI_Freq = F_OSC_16;
	SPI_Init(&spi_confige);
// Confige MAX7221
	Max7212_Default_Init();
}

uint8_t x=0;
void program(void)
{ 	
	
	for(uint8_t i = 8; i > 0; i--)
	{
		SPI_MasterTransmit_ADD_Data(&spi_confige,i,x++ );
		_delay_ms(100);
	}

}

