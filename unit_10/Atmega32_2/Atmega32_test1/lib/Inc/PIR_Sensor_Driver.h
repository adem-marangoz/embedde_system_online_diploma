/**
 * @file PIR_Sensor_Driver.h
 * @author adem alnajjar (adem.alnajjar95@gmail.com)
 * @brief PIR Driver
 * @version 0.1
 * @date 2022-10-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PIR_SENSOR_DRIVER_H_
#define PIR_SENSOR_DRIVER_H_

//------------------------------- Include Files --------------------------------
#include "GPIO.h"
//==============================================================================

enum En_Gate_working_method
{
    polling = 0,
    interrupt
};
//------------------------------ Generaic Objects ------------------------------

typedef struct 
{
    St_GPIO *Input_Port;
    unsigned char Input_Pin;
    enum En_Gate_working_method method;
}St_PIR_Sensor_Typedef;

//==============================================================================


//------------------------------ Global Functions ------------------------------
uint8_t Init_PIR(St_PIR_Sensor_Typedef *Instance);
uint8_t Wait_Car(St_PIR_Sensor_Typedef *Instance);
//==============================================================================


#endif