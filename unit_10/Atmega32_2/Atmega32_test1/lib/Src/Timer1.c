/**
 * @file Timer1.c
 * @author adem alnajjar (adem.alnajjar95@gmail.com)
 * @brief Timer1 Driver
 * @version 0.1
 * @date 2022-10-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//--------------------------------- Include Files ------------------------------
#include "Timer1.h"
#include "GPIO.h"
#include <avr/io.h>
#include "avr/interrupt.h"
//==============================================================================

//------------------------------- Local Objects --------------------------------
void config_pwm_pin(En_output_pin pin);
//==============================================================================

St_Timer1 Timer1_Typedef;

//-------------------------------- Global Function -----------------------------

/**
 * @brief Is used to confige the Timer1
 * @return uint8_t  0 : Fail
 *                  1 : Success */
uint8_t Init_Timer1()
{
    
    TCCR1A = ((Timer1_Typedef.output_compare_mode << Timer1_Typedef.output_pin) | (Timer1_Typedef.wave_generation_mode &0x03));
    TCCR1B = ((Timer1_Typedef.wave_generation_mode & 0x0C) << 1) | (Timer1_Typedef.Input_nosise) | (Timer1_Typedef.Input_capture_edge) | (Timer1_Typedef.clk_soruce);
    
    if((Timer1_Typedef.wave_generation_mode == CTC_OCR1A) | (Timer1_Typedef.wave_generation_mode == Pwm_phase_frequency_correct_OCR1A) | (Timer1_Typedef.wave_generation_mode == Pwm_phase_OCR1A) | (Timer1_Typedef.wave_generation_mode == Fast_pwm_OCR1A))
    {
        OCR1A = Timer1_Typedef.output_compare_A1;
    }else if ((Timer1_Typedef.wave_generation_mode == Fast_pwm_ICR1) | (Timer1_Typedef.wave_generation_mode == CTC_ICR1)| (Timer1_Typedef.wave_generation_mode == Pwm_phase_ICR1) | (Timer1_Typedef.wave_generation_mode == Pwm_phase_frequency_correct_ICR1))
    {
        ICR1 = Timer1_Typedef.Input_capture_reg;
    }
    TCNT1 = Timer1_Typedef.init_tick_count;
    // Reset ICF1, OCF1A, OCR1B, TOV1
    // TIFR &= ~(0x3C);  
    
    TIMSK |= Timer1_Typedef.timer1_interrput;
    if(Timer1_Typedef.output_pin != non_pin)
        config_pwm_pin(Timer1_Typedef.output_pin);   
    
    return 1;
}


/**
 * @brief Is used to config pwm pin
 * @param pin PD4 or PD5
 */
void config_pwm_pin(En_output_pin pin)
{
    GPIO_config servo_pin_config;
    servo_pin_config.mode = OUTPUT;
    if(pin == OC1A_pin)
        servo_pin_config.pin = PIN_5;
    else
        servo_pin_config.pin = PIN_4;

    Init_GPIO(PORT_D, &servo_pin_config);
}
/**
 * @brief Is used to stop Timer1
 * @return uint8_t  0 : Fail
 *                  1 : Success */ 
uint8_t Timer1_Stop()
{
    TCCR1B &= (0x07);
    return 1;
}

/**
 * @brief Is used to set compare register according to value
 * @param top which compare register
 * @param value The comparison value given to the register
 * @return uint8_t  0 : Fail
 *                  1 : Success */ 
uint8_t Set_Compare_value(enum Top_register top, uint16_t value)
{
    switch (top)
    {
    case ICR1_Reg:
        ICR1 = value;
        break;
    case OCR1A_Reg:
        OCR1A = value;
        break;
    case OCR1B_Reg:
        OCR1B = value;
        break;
    default:
        break;
    }
    return 1;
}


/**
 * @brief Is used to get the compare register value
 * @param top which compare register 
 * @return uint16_t return the comapre register value
 */
uint16_t Get_Compare_value(enum Top_register top)
{
    uint16_t buffer = 0;
    switch (top)
    {
    case ICR1_Reg:
        buffer = ICR1;
        break;
    case OCR1A_Reg:
        buffer = OCR1A;
        break;
    case OCR1B_Reg:
        buffer = OCR1B;
        break;
    default:
        break;
    }
    return buffer;
}

/**
 * @brief Is used to Set timer1 tick value
 * @param value The comparison value given to the register 
 * @return uint8_t  0 : Fail
 *                  1 : Success */ 
uint8_t Set_Tick_Count_(uint16_t value)
{
    TCNT1 = value;
    return 1;
}

/**
 * @brief Is used to get the timer1/counter
 * @return uint16_t return Timer1/counter
 */
uint16_t Get_Tick_Count()
{
    return TCNT1;
}

/**
 * @brief Is used to Enable or disable any Timer1 interrupt
 * @param value whick Timer1 interrupt
 * @return uint8_t  0 : Fail
 *                  1 : Success */ 
uint8_t En_Disable_Interupt(uint8_t value)
{
    TIMSK = Timer1_Typedef.timer1_interrput;
    return 1;
}
//==============================================================================


ISR(TIMER1_OVF_vect)
{
 
}

ISR(TIMER1_CAP_vect)
{

}


