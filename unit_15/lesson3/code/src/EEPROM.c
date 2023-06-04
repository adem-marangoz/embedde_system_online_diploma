/**
 * @file EEPROM.c
 * @author adem alnajjar (adem.marangoz@gmail.com)
 * @brief The EEPROM API using I2C
 * @version 0.1
 * @date 2022-09-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//______________________________ Include Files _________________________________
#include "EEPROM.h"
#include "Stm32f10xx_I2C.h"
//==============================================================================


//______________________________ Extern Objects ________________________________
extern St_I2C_API i2c1_config;
//==============================================================================


//______________________________ Global Functions ______________________________

/**
 * @brief Is Used to initialize EEPROM By I2C peripheral
 * @return uint8_t 1 : Successed
 *                 0 : Failed
 */
uint8_t EEPORM_Init(void)
{
    i2c1_config.I2C_Inst = I2C1;
    i2c1_config.Gneral_Call_En = General_Call_Enable;
    i2c1_config.I2C_Modes = I2C_Mode;
    i2c1_config.Event_Interrupt_En = I2C_Event_Interrupt_Dis;
    i2c1_config.Error_Interrupt_En = I2C_Error_Interrupt_Dis;
    i2c1_config.Peripheral_Input_Freq = I2C_Peripheral_input_Freq_8M;
    i2c1_config.I2C_Master_Mode = I2C_Master_SM_Mode;
    i2c1_config.SCL_Freq = I2C_SCL_SM_Freq_MAX;
    i2c1_config.Slave_Address->Address_mode = I2C_Slave_Add_7;
    I2C_Init(&i2c1_config);
}


/**
 * @brief Is Used to Send data From Master (CPU) To EEPROM
 * @param Memory_Add : EEEPROM's address
 * @param data : The Pointer indicating the data to be sent
 * @param data_length : The length data of want send
 * @return      uint8_t  : 1 = Succesed
 *                         0 = Failed
 */
uint8_t EEPROM_Write_NBytes(uint16_t Memory_Add, uint8_t *data, uint8_t data_length)
{
    uint8_t i = 0;
    uint8_t _temp_buf[256];
    _temp_buf[0] = Memory_Add;
    _temp_buf[1] = Memory_Add >> 8;

    for(i = 2 ; i < (data_length + 2) ; i++)
    {
        _temp_buf[i] = data[i - 2];
    }
    I2C_Master_Write(&i2c1_config, EEPROM_Address, _temp_buf, data_length + 2,\
                     I2C_With_Stop, Start, I2C_Disable_polling);

    return 1;
}


/**
 * @brief Is Used to Receive (CPU) data form EEPORM by I2C
 * @param Memory_Add : EEEPROM's address
 * @param data : The Pointer indicating the data to be receive
 * @param data_length : The length data of want send
 * @return      uint8_t  : 1 = Succesed
 *                         0 = Failed 
 */
uint8_t EEPROM_Read_Byte(uint16_t Memory_Add, uint8_t *data, uint8_t data_length)
{
    uint8_t _temp_buf[2];
    _temp_buf[0] = Memory_Add;
    _temp_buf[1] = Memory_Add >> 8;

    I2C_Master_Write(&i2c1_config, EEPROM_Address, _temp_buf, sizeof(_temp_buf),\
                     I2C_Without_Stop, Start, I2C_Disable_polling);

    I2C_Master_Read(&i2c1_config, EEPROM_Address, data, data_length ,\
                    I2C_With_Stop, Repeated_Start, I2C_Disable_polling);

    return 1;

}
//==============================================================================