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

//------------------------------- Include Files --------------------------------
#include "PIR_Sensor_Driver.h"
#include "EXTI.h"

//==============================================================================


//------------------------------ Generaic Objects ------------------------------

//==============================================================================


//------------------------------ Global Functions ------------------------------

uint8_t Init_PIR(St_PIR_Sensor_Typedef *Instance)
{
    GPIO_config config_i_o = {0};
    config_i_o.pin = Instance->Input_Pin;
	if(Instance->method)
    {
        config_i_o.mode = Rising_Ed_Ex_Int;
        if((Instance->Input_Pin == PIN_2) && (Instance->Input_Port == PORT_D))
        {
            Enable_EXTI_0();
        }else if ((Instance->Input_Pin == PIN_3) && (Instance->Input_Port == PORT_D))
        {
            Enable_EXTI_1();
        }else if ((Instance->Input_Pin == PIN_2) && (Instance->Input_Port == PORT_B))
        {
            Enable_EXTI_2();
        }
	    Enable_Global_EXTI();
    }else
    {
        config_i_o.mode = INPUT;
    }
	Init_GPIO(Instance->Input_Port,&config_i_o);

    return 1;
}


uint8_t Wait_Car(St_PIR_Sensor_Typedef *Instance)
{

}




//==============================================================================