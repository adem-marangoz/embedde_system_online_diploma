/**
 * @file WTDG.c
 * @author adem alnajjar (adem.marangoz@gmail.com)
 * @brief 
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

void WTDG_Init(En_WTDG_Pre Pre)
{
    WDTCR = 00;
    WDTCR |= Pre;
}


void WTDG_Start()
{
    WDTCR |= (1 << WDE);
}


void WTDG_Stop()
{
    WDTCR |= (1 << WDE) | (1 << WDTOE);
    WDTCR &= ~(1 << WDE);
}
//==============================================================================