/**
 * @file WTDG.h
 * @author adem alnajjar (adem.marangoz95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef WTDG_H_
#define WTDG_H_


typedef enum
{
    Almost_17_ms = 0,
    Almost_33_ms,
    Almost_67_ms,
    Almost_130ms,
    Almost_260ms,
    Almost_1s,
    Almost_2s
}En_WTDG_Pre;
//_______________________________ GLOBAL FUNCTIONS _____________________________

void WTDG_Init(En_WTDG_Pre Pre);
void WTDG_Start();
void WTDG_Stop();
//==============================================================================


#endif