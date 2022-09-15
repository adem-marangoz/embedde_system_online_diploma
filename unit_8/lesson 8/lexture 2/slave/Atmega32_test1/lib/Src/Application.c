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
#define Master			0
//==============================================================================

void init(void)
{
// Confige The I2C
	i2c_confige.En_intrrupt = I2C_interrupt_Dis;
	i2c_confige.Prescaler = PR_1;
	i2c_confige.SCL_Freq = 0x48;
	i2c_confige.Slave_Add = 0xD0;
	TWAR = i2c_confige.Slave_Add;
	I2C_Init(&i2c_confige);

// Confige 7 segment
	GPIO_config gpio_config = {0};
	gpio_config.mode = OUTPUT;
	gpio_config.pin = ALL_PINS; 
	Init_GPIO(PORT_A, &gpio_config);


}

uint8_t ch = 0;

void program(void)
{ 	
	#if Master == 1
		_delay_ms(500);
		I2C_Send_Start();
		I2C_Write(0xD0);
		while((TWSR & 0xF8) != SR_MW_ADD_ACK);
		I2C_Write(ch++);
		while((TWSR & 0xF8) != SR_MW_DATA_ACK);
		I2C_Send_Stop();
	#else	
		ch = I2C_Read();
		I2C_Write(ch);
		Write_Port_Register(PORT_A, ch);
	#endif
}

