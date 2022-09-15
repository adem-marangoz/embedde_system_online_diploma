/**
 * @file I2C_driver.c
 * @author adem alnajjar (adem.marangoz95@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "I2C_driver.h"
#include <avr/io.h>

//___________________________ LOCAL Variables & Functions ______________________ 
#define F_CPU           16000000UL

//==============================================================================


/**
 * @brief           This function is used to initialize the I2C Peripheral
 * @param I2C       UART data structure containing the I2C parameters specified by the user
  * @return uint8_t  0 : Fail
 *                   1 : Success
 */
uint8_t I2C_Init(St_I2C_API *I2C)
{
    // Config I2C Frequency
    TWBR = (((F_CPU/I2C->SCL_Freq)-16)/(2*I2C->Prescaler));
    
    // Config Prescaler
    TWSR = I2C->Prescaler;
    
    // Check Interrupt
    TWCR = I2C->En_intrrupt << TWIE;

    // Set Slave Address
    if(I2C->Slave_Add != 0)
        TWAR = I2C->Slave_Add; 
    return 1;
}


/**
 * @brief This Function is used to send Start Condition to Slave form Master 
 * @return uint8_t  0 : Fail
 *                  1 : Success
 */
uint8_t I2C_Send_Start(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    // Wait until the TWINT to Reset
    while (!(TWCR & (1 << TWINT)));

    // Check The State Register if return ACK
    if ((TWSR & 0xF8) != SR_MW_START)
    {
        I2C_Send_Stop();
        return 0;
    }

    return 1;
}


/**
 * @brief This Function is used to send STOP condition To slave form master
  * @return uint8_t  0 : Fail
  *                  1 : Success
 */
uint8_t I2C_Send_Stop(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}


/**
 * @brief This Fumntion is used to send Data/Address To slave form master
 * @param data send value data To slave
 * @return uint8_t  0 : Fail
 *                  1 : Success
 */
uint8_t I2C_Write(uint8_t data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}


/**
 * @brief This function is used to Read Data & Address become form master
 * @return uint8_t return the received data form master
 */
uint8_t I2C_Read()
{
    // For Read Add data become form Master
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)));
    while((TWSR & 0xF8) != SR_SR_ADD_ACK);

    // For Read Data become from Master
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)));
    while((TWSR & 0xF8) != SR_SR_DATA_ACK);

    return TWDR;
}