/**
 * @file Application.C
 * @author adem alnajjar (adem.alnajjar@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */


//------------------------------- INCLUDE FILES --------------------------------
#include "Application.h"
#include "Stm32_f10xx_Systick.h"
#include <string.h>
#include <stdio.h>
//==============================================================================


//----------------------------- EXTERNAL OBJECTES ------------------------------

//==============================================================================


//------------------------------- LOCAL OBJECTS --------------------------------

//==============================================================================


//--------------------------------- FUNCTIONS ----------------------------------


void config_Drives_and_Perpherals(void)
{
    //---------------------------- Systick Config ------------------------------
    Systick_API.Clock_Source = Processor_Clock_AHB;
    Systick_API.Current_Value = 0;
    Systick_API.Enable_Interrupt = Enable_Systick_Req;
    Systick_API.Reload_Value = 7999;
    Init_Systick();
    //==========================================================================
}


/**
 * @brief infinite loop
 */
void Infinite_loop()
{

    
}


//==============================================================================


//------------------------------- DATA STRUCTURE -------------------------------

//==============================================================================