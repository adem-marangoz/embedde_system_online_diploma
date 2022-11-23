/**
 * @file Servo_sg90.c
 * @author adem alnajjar (adem.alnajjar95@gmail.com)
 * @brief Servo_SG90_Driver
 * @version 0.1
 * @date 2022-11-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//------------------------------- Include Files --------------------------------
#include "Servo_sg90.h"
#include "Timer1.h"
#include "GPIO.h"
#include <avr/io.h>
//==============================================================================


//------------------------------ Global Functions ------------------------------
/**
 * @brief Is used to config timer1 for servo motor
 * @return uint8_t  0 : Fail
 *                  1 : Success */
uint8_t config_servo_timer()
{
    //----------------- Config Timer1 -----------------
    Timer1_Typedef.clk_soruce = Clk_divid_8;
    Timer1_Typedef.init_tick_count = 0;
    Timer1_Typedef.Input_capture_edge = Input_Capture_falling_edge;
    Timer1_Typedef.Input_capture_reg = 19999;
    Timer1_Typedef.Input_nosise = Disable_cancel_input_noise;
    Timer1_Typedef.output_compare_A1 = 0;
    Timer1_Typedef.output_compare_B1 = 0;
    Timer1_Typedef.output_compare_mode = Fast_PWM_Clear_on_compare_set_at_bottom;
    Timer1_Typedef.output_pin = OC1A_pin;
    Timer1_Typedef.timer1_interrput = 0;
    Timer1_Typedef.wave_generation_mode = Fast_pwm_ICR1;
    Init_Timer1();

    return 1;
}

/**
 * @brief Is used to set comperation register
 * @param value compare value
 * @return uint16_t compare value
 */
uint16_t Set_angle(uint16_t value)
{
    OCR1A = value;
    return value;
}
//==============================================================================