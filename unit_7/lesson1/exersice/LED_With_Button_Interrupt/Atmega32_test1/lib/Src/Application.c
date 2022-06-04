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




void init(void)
{
    /*Config PA0, PA1, PA2, PA3, PA4, PA5, PA6 and PA7  pin as Output */
    GPIO_config config_i_o = {0};
	config_i_o.pin = PIN_0| PIN_1 | PIN_2 | PIN_3 | PIN_4 | PIN_5 | PIN_6 | PIN_7;
	config_i_o.mode = OUTPUT;
	Init_GPIO(PORT_A,&config_i_o);
	
	/*Config PB2 pin as External interrupt*/
	config_i_o.pin = PIN_2;
	config_i_o.mode = Rising_Ed_Ex_Int;
	Init_GPIO(PORT_B,&config_i_o);

	/*Enable INT2 interrupt and Global interrupt*/
	Enable_EXTI_2();
	Enable_Global_EXTI();

}

void program(void)
{ 	
}

/**
 * @brief Construct a new ISR object
 * @brief This function was defined by this name based on the startup file 
 *        and was called from within the interrupt file
 * @param: Hardware Interrupt Source base interupt vector table
 * @retval: None
 */
ISR(INT2_vect)
{
    volatile static uint8_t counter = 0;
    if(counter < 8)
    {
	    Write_Pin(PORT_A,PIN_0 << counter, High);
	    counter ++;
    }
}

