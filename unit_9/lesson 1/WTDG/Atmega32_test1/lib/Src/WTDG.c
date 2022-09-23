/**
 * @file WTDG.c
 * @author adem alnajjar (adem.marangoz@gmail.com)
 * @brief This File is Used to control for Watachdog 
 * @version 0.1
 * @date 2022-09-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */


//_________________________________ INCLUDES ___________________________________
#include "WTDG.h"
#include <avr/io.h>

//==============================================================================


//________________________________ GLOBAL FUNCTIONS ____________________________

/**
* @brief This function is used to Init Watach dog
*/
void WTDG_Init(En_WTDG_Pre Pre)
{
    WDTCR = 00;
    WDTCR |= Pre;
}


/**
* @brief This Function is used to starts watach dog counting
*/
void WTDG_Start()
{
    WDTCR |= (1 << WDE);
}


/**
* @brief This function is used to Stops watach dog counting and resets
*/
void WTDG_Stop()
{
    WDTCR |= (1 << WDE) | (1 << WDTOE);
    WDTCR &= ~(1 << WDE);
}
//==============================================================================