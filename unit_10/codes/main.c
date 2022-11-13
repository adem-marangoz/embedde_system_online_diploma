/*
*@author 	Adem Alnajjar
*@data		24.11.2021
*/

//_________________________________ Include Files ______________________________
#include "Application.h"
#include "Stm32f10xx_Common.h"
//==============================================================================


//______________________________ Generic Macro _________________________________


//==============================================================================


//_____________________ Generica Function & Data Structure _____________________
void config_Drives_and_Perpherals(void);
void Init_Component(void);
extern void _delay_ms(uint32_t time);

    //______________________ Data Structre of Drives ___________________________

    //==========================================================================

// uint16_t Rx_Buff[14] = {0};

//==============================================================================
int main(void)
{
    config_Drives_and_Perpherals(); // config Drives and Peripherals
    Init_Component();
    // uint16_t Tx_Buff[] = {'Y','O','U',' ','C', 'A','N',' ','D','O',' ','I','T'};
    // uint16_t test[] = {'A' , 'D', 'E', 'D', ' ', 'M', 'A', 'R', 'A', 'N', 'G', 'O', 'Z'};
    // // Send_String_Uart(UART1, Tx_Buff,Enable);
    // Enable_Write_EEPROM_25xx(&EEPORM_25xx_config);
    
    // // Write_Byte_EEPROM_25xx(&EEPORM_25xx_config, 0x0002, 0xFF);
    // Write_Bytes_EEPROM_25xx(&EEPORM_25xx_config, 0x0002, 13, Tx_Buff);
    // delay_us(10000);
    // Read_Byte_EEPROM_25xx(&EEPORM_25xx_config, 0x0002, 13, Rx_Buff);
    // Send_String_Uart(UART1, Rx_Buff,Enable);


    while (1)
    {
        // Send_String_Uart(UART1, Tx_Buff,Enable);
        // _delay_ms(100);
    }    

    return 1;
}
