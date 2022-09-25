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
#include "ADC.h"
#include <stdlib.h>


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
St_ADC_API adc1_config = {0};
//==============================================================================

//_____________________________ Local Variables ________________________________

uint8_t R_msg[16] = {0};
//==============================================================================

//_____________________________ MACRO Definition _______________________________
#define Master			1
//==============================================================================

void init(void)
{
// Config LCD
	Lcd_config.Data_Port = PORT_B;
	Lcd_config.Enable_Port = PORT_D;
	Lcd_config.RS_Port = PORT_D;
	Lcd_config.R_W_Port = PORT_D;
	Lcd_config.Enable_Pin = PIN_0;
	Lcd_config.R_W_Pin = PIN_1;
	Lcd_config.RS_Pin = PIN_2;
	LCD_init(&Lcd_config);


// Config ADC
	adc1_config.Channel = CH_7;
	adc1_config.Freq = ADC_SCALER_64;
	adc1_config.Vref = VREF_AVCC;	
	ADC_Init(&adc1_config);

}

uint16_t Adc_value = 0;
uint8_t general[17];
uint16_t voltage;
uint8_t Pre ;
uint8_t charge ;
void program(void)
{ 	
	// Read input voltage and calculate as voltage and Percentage 
	Adc_value = ADC_Read(&adc1_config);
	voltage = ADC_Read_Volt(&adc1_config, Adc_value);
	Pre = voltage/50;

	
	snprintf(general, 17,"%d %dmV %d%%",Adc_value, voltage, Pre);
	general[16] = '#';

	Jump_to_coordinator(&Lcd_config,0,First_R);
	Write_String_Stop_with_Character(&Lcd_config, general, '#');

	for(int i = 0; i < 16; i++){general[i] = 0;}
	charge = Pre/6;
	Jump_to_coordinator(&Lcd_config,0,Seconde_R);
	for(int i = 0 ; i < 16; i++)
	{
		if(i < charge)
		{
			Write_Character(&Lcd_config, 0xFF);
		}else
		{
			Write_Character(&Lcd_config, 0);
		}
	}

}

