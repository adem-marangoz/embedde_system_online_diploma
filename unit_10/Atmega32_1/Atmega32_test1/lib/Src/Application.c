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
#include "PIR_Sensor_Driver.h"
#include "Timer1.h"
#include "Servo_sg90.h"
#include <stdbool.h>
#include "Data_control.h"

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
St_PIR_Sensor_Typedef Pir_config = {0};
#define F_CPU 8000000UL
//==============================================================================

//_____________________________ Local Variables ________________________________

uint8_t R_msg[16] = {0};
//==============================================================================

//_____________________________ MACRO Definition _______________________________
#define Master			1
//==============================================================================

void init(void)
{
//------------------------------ Config LCD ------------------------------------
	// Lcd_config.Data_Port = PORT_A;
	// Lcd_config.Enable_Port = PORT_C;
	// Lcd_config.RS_Port = PORT_C;
	// Lcd_config.R_W_Port = PORT_C;
	// Lcd_config.Enable_Pin = PIN_0;
	// Lcd_config.R_W_Pin = PIN_1;
	// Lcd_config.RS_Pin = PIN_2;
	// LCD_init(&Lcd_config);
//==============================================================================


//------------------------------ Config ADC ------------------------------------
	// adc1_config.Channel = CH_7;
	// adc1_config.Freq = ADC_SCALER_64;
	// adc1_config.Vref = VREF_AVCC;	
	// ADC_Init(&adc1_config);
//==============================================================================


// ---------------------------- Normal Output ----------------------------------
	// GPIO_config config_i_o = {0};
	// config_i_o.pin = PIN_5;
	// config_i_o.mode = OUTPUT;
	// Init_GPIO(PORT_D,&config_i_o);
// =============================================================================

// ---------------------------- PIR Sensor -------------------------------------
	Pir_config.Input_Port = PORT_D;
	Pir_config.Input_Pin = PIN_2;
	Pir_config.method = interrupt;
	Init_PIR(&Pir_config);

//==============================================================================

//------------------------------- Servo motor ----------------------------------
	config_servo_timer();
//==============================================================================

//--------------------------------- SPI Config ---------------------------------
	spi_confige.Data_Modes = Sample_Ris_Setup_Fall;
	spi_confige.Data_Order = Data_Order_MSB;
	spi_confige.En_interrupt = EN_SPI_Interrupt;
	spi_confige.Slave_Master = SPI_Slave;
	spi_confige.SPI_Freq = F_OSC_4;
	SPI_Init(&spi_confige);
//==============================================================================


//------------------------------ EXti pin config -------------------------------
// GPIO_config config_i_o = {0};
// config_i_o.pin = PIN_2;
// config_i_o.mode = Falling_Ed_Ex_Int;
// Init_GPIO(PORT_D,&config_i_o);
//==============================================================================
	sei();
	Set_angle(_0_angle);
	// Write_Character(&Lcd_config,'w');
}

void program(void)
{ 	
	// volatile static uint8_t counter = 0;
	// if(counter < 10)
	// {
		
    // 	temp = SPI_SlaveReceive_Char(&spi_confige, 0);
    // 	Write_Character(&Lcd_config, temp);
	// 	counter ++;
	// 	if(counter == 10){counter = 0;}
	// }

}



ISR(INT0_vect)
{
	Set_angle(_0_angle);
}


ISR(INT1_vect)
{

}


ISR(INT2_vect)
{

}

ISR(SPI_STC_vect)
{
    uint8_t temp ;
    temp = SPI_SlaveReceive_Char(&spi_confige, 200);
    Data_analysis(temp);

}