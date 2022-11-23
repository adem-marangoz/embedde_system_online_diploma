/**
 * @file ADC.h
 * @author adem alnajjar (adem.marangoz95@gamil.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ADC_H_
#define ADC_H_

/* To find the ADC value base on input voltage -->> ADC = (input.2^N)/Vref
N : ADC Res
*/

// ADC1 have 8 channel in PortA to measart input value

//________________________________ INCLUDES ____________________________________
#include "Common.h"

//==============================================================================

//_______________________________ GENERAIC OBJECTS _____________________________



#define VoltRef                 5000 // 5V
#define ADC_Res                 1024 // 10 bit ADC Res


// @ref ADC_Vref_define
typedef enum
{
    VREF_AREF = 0,
    VREF_AVCC,
    VREF_256,
    VREF_External_2_56
}En_ADC_Vref_Typedef;


// @ref ADC_Freq_Scaler_define
//Must ADC freq must be highter then 30KHz
typedef enum
{
    ADC_SCALER_2 = 1,
    ADC_SCALER_4 = 2,
    ADC_SCALER_8,
    ADC_SCALER_16,
    ADC_SCALER_32,
    ADC_SCALER_64,
    ADC_SCALER_128
}En_ADC_Scaler_Typedef;

// @ref ADC_Channel_define
typedef enum
{
    CH_0 = 0,
    CH_1,
    CH_2,
    CH_3,
    CH_4,
    CH_5,
    CH_6,
    CH_7
}En_ADC_Channel_Typedef;

//==============================================================================


//__________________________________ ADC API ___________________________________
typedef struct 
{
    En_ADC_Vref_Typedef Vref;
    
    En_ADC_Scaler_Typedef Freq;

    En_ADC_Channel_Typedef Channel;
}St_ADC_API;
//==============================================================================

//_____________________________ GLOBAL FUCNTIONS _______________________________
uint8_t ADC_Init(St_ADC_API *ADCx);
uint16_t ADC_Read(St_ADC_API *ADCx);
uint16_t ADC_Read_Volt(St_ADC_API *ADCx, uint16_t data);
//==============================================================================


#endif