/**
 * @file ADC.c
 * @author adem alnajjar (adem.maragoz95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//________________________________ INCLUDES ____________________________________
#include "ADC.h"
#include "GPIO.h"
#include <avr/io.h>

//==============================================================================

//_______________________________ GLOBAL FUNCTIONS _____________________________

/**
 * @brief This function is used to Init ADC
 * @param ADCx : ADC data structre containing the ADC parameters
  * @return uint8_t  0 : Fail
  *                  1 : Success
 */
uint8_t ADC_Init(St_ADC_API *ADCx)
{
    // First Clear ADMUX Regiset and Set Vref 
    ADMUX = 0x00;
    ADMUX |= ADCx->Vref << 6;

    // First Clear Scaler ADC and Set Scaler value
    ADCSRA &= ~(ADC_SCALER_128);
    ADCSRA |= ADCx->Freq;

    // Set ADC
    SET_BIT(ADCSRA, 1 << ADEN);
    return 1;
}


/**
 * @brief This function is used to read ADC channel input
 * @param ADCx : ADC data structre containing the ADC parameters
  * @return uint16_t : is return the adc channel value  
 */
uint16_t ADC_Read(St_ADC_API *ADCx)
{
    // Select The ADC channel to read analog value
    ADMUX &= 0xE0;
    ADMUX |= CH_7;

    // Start Conversion
    SET_BIT(ADCSRA, 1 << ADSC);
    ADCSRA |= ADSC;
    while(READ_BIT(ADCSRA, 1 << ADSC));

    return ADC;
}

/**
 * @brief Is used to return the input voltage value to ADC
 * @param ADCx : ADC data structre containing the ADC parameters
 * @param data : input voltage
 * @return uint16_t voltage data as mV
 */
uint16_t ADC_Read_Volt(St_ADC_API *ADCx, uint16_t data)
{
    if(data == ADC_Res - 1){ return VoltRef;}
    uint32_t volt = (uint32_t)data*VoltRef;
    volt /= ADC_Res;
    return volt;
}
//==============================================================================

//_______________________________ ISR FUNCTIONS ________________________________

//==============================================================================