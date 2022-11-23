/**
 * @file Data_control.c
 * @author adem alnajjar (adem.alnajjar95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//------------------------------- INCLUDE FILES --------------------------------
#include "Data_control.h"
#include "Servo_sg90.h"
#include "SPI_driver.h"
//==============================================================================


//------------------------------ GENERAIC OBJECTS ------------------------------
extern St_SPI_API spi_confige;
//==============================================================================


//------------------------------- DATA STRUCTURE -------------------------------

//==============================================================================


//------------------------------ GLOBAL FUNCTIONS ------------------------------
uint8_t Data_analysis(uint8_t *data)
{
    uint8_t retval = 0;
    if(data == Open_entry_gate1)
    {
        Set_angle(positive_90_angle);
        retval++;
    }else if(data == Close_entry_gate1)
    {

        retval++;
    }else if(data == Open_exit_gate2)
    {

        retval++;
    }else if(data == Close_exit_gate2)
    {

        retval++;
    }else
    {

    }
    return retval;
}
//==============================================================================