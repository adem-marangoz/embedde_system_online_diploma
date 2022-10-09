/**
 * @file Buzzer.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */


//_____________________________ Include Files __________________________________
#include "Stm32f10xx_Common.h"
#include "Stm32f10xx_GPIO.h"
//==============================================================================


//______________________________ Generic Macro _________________________________

enum En_Buzzer_State
{
    Mute = 0,
    Unmute
};

typedef struct 
{
    St_GPIO_Typedef *GPIOx;         // Buzzer GPIO Port
    uint32_t pin;                   // Buzzer Pin
    enum En_Buzzer_State State;     // Buzzer First State
}St_Buzzer_Typedef;

//==============================================================================


//______________________________ Global Functions ______________________________
void Init_Buzzer(St_Buzzer_Typedef *Buzzerx);
void Deinit_Buzzer(St_Buzzer_Typedef *Buzzerx);
//==============================================================================