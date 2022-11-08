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
	// Lcd_config.Data_Port = PORT_B;
	// Lcd_config.Enable_Port = PORT_D;
	// Lcd_config.RS_Port = PORT_D;
	// Lcd_config.R_W_Port = PORT_D;
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
	GPIO_config config_i_o = {0};
	config_i_o.pin = PIN_5;
	config_i_o.mode = OUTPUT;
	Init_GPIO(PORT_D,&config_i_o);
// =============================================================================

// ---------------------------- PIR Sensor -------------------------------------
	// Pir_config.Input_Port = PORT_D;
	// Pir_config.Input_Pin = PIN_2;
	// Pir_config.method = interrupt;
	// Init_PIR(&Pir_config);

//==============================================================================

//------------------------------- Servo motor ----------------------------------
	config_servo_timer();
//==============================================================================

}
uint16_t counter = 0;
void program(void)
{ 	
	Set_angle(999);
	_delay_ms(1000);
	Set_angle(1499);
	_delay_ms(1000);
	Set_angle(1999);
	_delay_ms(1000);
	
}



ISR(INT0_vect)
{
    Toggle_pin(PORT_A,PIN_0);
}


ISR(INT1_vect)
{
    Toggle_pin(PORT_A,PIN_0);
}


ISR(INT2_vect)
{
    Toggle_pin(PORT_A,PIN_0);
}