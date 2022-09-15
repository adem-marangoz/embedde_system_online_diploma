/**
 * @file I2C.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef I2C_H_
#define I2C_H_

#include "Common.h"


//__________________________________ TWCR ______________________________________ 
#define TWIE                                0
#define TWEN                                2
#define TWWC                                3  
#define TWSTO                               4
#define TWSTA                               5
#define TWEA                                6
#define TWINT                               7
//==============================================================================

//_________________________________ TWSR _______________________________________
#define TWPS0                               0
#define TWPS1                               1
#define TWS3                                3
#define TWS4                                4
#define TWS5                                5
#define TWS6                                6
#define TWS7                                7
//==============================================================================


//_________________________________ TWAR _______________________________________
#define TWGCE                               0
#define TWA0                                1
#define TWA1                                2
#define TWA2                                3
#define TWA3                                4
#define TWA4                                5
#define TWA5                                6
#define TWA6                                7
//==============================================================================

//_____________________________ TWSR STATUS ____________________________________

#define SR_MW_START                         0x08
#define SR_MW_REPEATED_START_SR             0x10

#define SR_MW_ADD_ACK                       0x18
#define SR_MW_ADD_NACK                      0x20
#define SR_MW_DATA_ACK                      0x28
#define SR_MW_DATA_NACK                     0x30
#define SR_MW_ARBIT_LOST                    0x38

#define SR_MR_ADD_ACK                       0x40
#define SR_MR_ADD_NACK                      0x48
#define SR_MR_DATA_ACK                      0x50
#define SR_MR_DATA_NACK                     0x58

#define SR_SR_ADD_ACK                       0x60
#define SR_SR_ADD_NACK                      0x68
#define SR_SR_DATA_ACK                      0x80
#define SR_SR_DATA_NACK                     0x88
#define SR_SR_S_OR_P                        0xA0
#define SR_SR_GNCL_ADD_ACK                  0x70
#define SR_SR_GNCL_ADD_NACK                 0x78
#define SR_SR_GNCL_DATA_ACK                 0x90
#define SR_SR_GNCL_DATA_NACK                0x98

#define SR_ST_ADD_ACK                       0xA8
#define SR_ST_ADD_NACK                      0xB0
#define SR_ST_DATA_ACK                      0xB8
#define SR_ST_DATA_NACK                     0xC0
//==============================================================================

// Check TWINT bit
#define IS_TWINT_SET                        (((TWCR)  == 1 << TWINT))

// Check the Status register
#define IS_TWSR_STATE(STATE)                (((STATE) == (TWSR & 0xF8)))

// @ref I2C_Prescaler_define
#define PR_1                                0
#define PR_4                                1
#define PR_16                               16
#define PR_64                               64

// @ref I2C_Interrupt_En_define
#define I2C_interrupt_Dis                   0
#define I2C_interrupt_En                    1

typedef enum
{
  I2C_Slave = 0,
  I2C_Master
}En_I2C_Mode;

//________________________________ I2C_API _____________________________________

typedef struct 
{
    uint32_t SCL_Freq;               /* Specifies The I2C SCL Frequency to configured*/

    uint8_t En_intrrupt;            /* Specifies the I2C intrrupt to be configured
                                    The parameter can be any value of @ref I2C_Interrupt_En_define*/
    uint8_t Prescaler;               /* Specifies the I2C buadrate to be configured
                                    The parameter can be any value of @ref I2C_Prescaler_define*/
    uint8_t Slave_Add;              /* Specifies the I2C intrrupt to be configured*/

}St_I2C_API;

//==============================================================================


//______________________________ Global Function _______________________________

uint8_t I2C_Init(St_I2C_API *I2C);
uint8_t I2C_Send_Start(void);
uint8_t I2C_Send_Stop(void);
uint8_t I2C_Write(uint8_t data);
uint8_t I2C_Read();
//==============================================================================
#endif