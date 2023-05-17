/**
 * @file Application.h
 * @author adem alnajjar (adem.alnajjar@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

//------------------------------- INCLUDE FILES --------------------------------
#include "Stm32f10xx_GPIO.h"
#include "Stm32f10xx_EXTI.h"
#include "Stm32f10xx_RCC.h"
#include "Stm32f10xx_AFIO.h"
#include "Stm32f10xx_Address.h"
#include <stdio.h>
#include "Stm32f10xx_Common.h"

//==============================================================================

//------------------------------- DATA STRUCTURE -------------------------------


//==============================================================================

//------------------------------ GLOBAL OBJECTES -------------------------------



//==============================================================================


//--------------------------------- FUNCTIONS ----------------------------------
void config_Drives_and_Perpherals(void);
void Infinite_loop();
//==============================================================================


#endif