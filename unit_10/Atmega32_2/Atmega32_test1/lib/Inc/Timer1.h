/**
 * @file Timer1.h
 * @author adem alnajjar (adem.alnajjar95@gmail.com)
 * @brief Timer1 driver
 * @version 0.1
 * @date 2022-10-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef TIMER1_H_
#define TIMER1_H_

//------------------------------- Include Files --------------------------------
#include "Common.h"

//==============================================================================


//------------------------------ Generaic Object -------------------------------

// @ref Timer1_Compare_output_mode_define
typedef enum
{
    Normal_Port = 0, // non-PWM
    Non_PWM_Toggle_Output, // non-PWM
    Non_PWM_Clear_Output, // non-PWM
    Non_PWM_Set_Output, // non-PWM
    Fast_PWM_Toggle_on_compare = 1, // Fast PWM
    Fast_PWM_Clear_on_compare_set_at_bottom, // Fast PWM
    Fast_PWM_Set_on_compare_clear_at_bottom, // Fast PWM
    Correct_PWM_Toggle_on_compare = 1, // Phase correct and Phase and Frequency correct PWM
    Correct_PWM_Clear_on_compare_set_at_bottom, // Phase correct and Phase and Frequency correct PWM
    Correct_PWM_Set_on_compare_clear_at_bottom, // Phase correct and Phase and Frequency correct PWM
}En_Compare_Output_mode;


// @ref Wave_Generation_Mode_define
typedef enum
{
    Normal = 0, // (TOP = 0xFFFF) (update of OCR1x = Immediate) (TOV1 flag set on = MAX)
    Pwm_phase_8bit, // (TOP = 0X00FF) (update of OCR1x = TOP) (TOV1 flag set on = BOTTOM)
    Pwm_phase_9bit, // (TOP = 0X01FF) (update of OCR1x = TOP) (TOV1 flag set on = BOTTOM)
    Pwm_phase_10bit, // (TOP = 0X03FF) (update of OCR1x = TOP) (TOV1 flag set on = BOTTOM)
    CTC_OCR1A, // (TOP = OCR1A) (update of OCR1x = Immediate) (TOV1 flag set on = MAX)
    Fast_pwm_8bit, // (TOP = 0X00FF) (update of OCR1x = BOTTOM) (TOV1 flag set on = TOP)
    Fast_pwm_9bit, // (TOP = 0X01FF) (update of OCR1x = BOTTOM) (TOV1 flag set on = TOP)
    Fast_pwm_10bit, // (TOP = 0X03FF) (update of OCR1x = BOTTOM) (TOV1 flag set on = TOP)
    Pwm_phase_frequency_correct_ICR1, // (TOP = ICR1) (update of OCR1x = BOTTOM) (TOV1 flag set on = BOTTOM)
    Pwm_phase_frequency_correct_OCR1A, // (TOP = OCR1A) (update of OCR1x = BOTTOM) (TOV1 flag set on = BOTTOM)
    Pwm_phase_ICR1, // (TOP = ICR1) (update of OCR1x = TOP) (TOV1 flag set on = BOTTOM)
    Pwm_phase_OCR1A, // (TOP = OCR1A) (update of OCR1x = TOP) (TOV1 flag set on = BOTTOM)
    CTC_ICR1, // (TOP = ICR1) (update of OCR1x = Immediate) (TOV1 flag set on = MAX)
    Reserved_condition, // 
    Fast_pwm_ICR1, // (TOP = ICR1) (update of OCR1x = BOTTOM) (TOV1 flag set on = TOP)
    Fast_pwm_OCR1A // (TOP = OCR1A) (update of OCR1x = BOTTOM) (TOV1 flag set on = TOP)

}En_Wave_Generation_Mode;


// @ref Input_noise_cancel_define
#define Enable_cancel_input_noise           128
#define Disable_cancel_input_noise          0

// @ref Input_capture_edge_define
#define Input_Capture_falling_edge          0
#define Input_Capture_rising_edge           64

// @ref Timer1_Clock_source_define
#define No_clock                            0
#define Clk_divid_1                         1
#define Clk_divid_8                         2
#define Clk_divid_64                        3
#define Clk_divid_256                       4
#define Clk_divid_1024                      5
#define External_clk_falling_edge           6
#define External_clk_rising_edge            7

// @ref Timer1_interrupt_define
#define En_TICIE1                           32
#define En_OCIE1A                           16
#define En_OCIE1B                           8
#define En_TOIE1                            4


enum Top_register
{
    ICR1_Reg = 0,
    OCR1A_Reg,
    OCR1B_Reg
};

// @ref Timer1_output_pin_define
typedef enum
{
    non_pin = 0,
    OC1A_pin = 6,
    OC1B_pin = 4
}En_output_pin;

typedef struct 
{
    uint16_t init_tick_count;                       /*The initial value of the counter can take any value from 0 to 0xFFFF*/
    uint16_t output_compare_A1;                     /*The comparison value can be taken from 0 to 0xFFFF*/
    uint16_t output_compare_B1;                     /*The comparison value can be taken from 0 to 0xFFFF*/
    uint16_t Input_capture_reg;                     /*The comparison value can be taken from 0 to 0xFFFF*/
    En_Compare_Output_mode output_compare_mode;     /*!< Specifies The Timer1 to be configured the output comapre mode.
                                                    This parameter can be any value of @ref Timer1_Compare_output_mode_define */
    En_output_pin output_pin;                       /*!< Specifies The Timer1 to be configured the output Pin.
                                                    This parameter can be any value of @ref Timer1_output_pin_define */
    En_Wave_Generation_Mode wave_generation_mode;   /*!< Specifies The Timer1 to be configured the PWM.
                                                    This parameter can be any value of @ref Wave_Generation_Mode_define */
    uint8_t Input_nosise;                           /*!< Specifies The Timer1 to be configured the Input noise filter.
                                                    This parameter can be any value of @ref Input_noise_cancel_define */
    uint8_t Input_capture_edge;                     /*!< Specifies The Timer1 to be configured the Input capture edge.
                                                    This parameter can be any value of @ref Input_capture_edge_define */
    uint8_t clk_soruce;                             /*!< Specifies The Timer1 to be configured the Timer1 clock source.
                                                    This parameter can be any value of @ref Timer1_Clock_source_define */
    uint8_t timer1_interrput;                       /*!< Specifies The Timer1 to be configured the Timer1 interrupt.
                                                    This parameter can be any value of @ref Timer1_interrupt_define */

}St_Timer1;

extern St_Timer1 Timer1_Typedef;
//==============================================================================


//------------------------------ Global Function -------------------------------
uint8_t Init_Timer1();
uint8_t Timer1_Stop();
uint8_t Set_Compare_value(enum Top_register top, uint16_t value);
uint16_t Get_Compare_value(enum Top_register top);
uint8_t Set_Tick_Count_(uint16_t value);
uint16_t Get_Tick_Count();
uint8_t En_Disable_Interupt(uint8_t value);

//==============================================================================


#endif