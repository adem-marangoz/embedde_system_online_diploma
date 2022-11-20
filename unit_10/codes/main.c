/*
*@author 	Adem Alnajjar
*@data		24.11.2021
*/

//_________________________________ Include Files ______________________________
#include "Application.h"
#include "Stm32f10xx_Common.h"
#include "Key_pad_Driver.h"
//==============================================================================


//______________________________ Generic Macro _________________________________


//==============================================================================


//_____________________ Generica Function & Data Structure _____________________
void config_Drives_and_Perpherals(void);
void Init_Component(void);
extern void _delay_ms(uint32_t time);
extern St_Key_pad key_pad_config;

    //______________________ Data Structre of Drives ___________________________

    //==========================================================================

// uint16_t Rx_Buff[14] = {0};

//==============================================================================
int main(void)
{
    config_Drives_and_Perpherals(); // config Drives and Peripherals
    Init_Component();
    

    while (1)
    {
        Check_Prass_Button(&key_pad_config);
    }    

    return 1;
}
