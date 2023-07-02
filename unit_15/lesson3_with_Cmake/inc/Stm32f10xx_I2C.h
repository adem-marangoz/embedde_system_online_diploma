/**
 * @file Stm32f10xx_I2C.h
 * @author adem alnajjar (adem.maragoz95@gmail.com)
 * @brief The I2C API
 * @version 0.1
 * @date 2022-09-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef STM32F10XX_I2C_H_
#define STM32F10XX_I2C_H_

//______________________________ Includes Files ________________________________
#include "Stm32f10xx_Address.h"
#include "Stm32f10xx_Common.h"
#include "BitField_I2C.h"
//==============================================================================


//_____________________________ Generic Macro __________________________________

#define IS_I2C_ALL_INSTANCE(INSTANCE)                 (((INSTANCE) == I2C1)||\
                                                      ((INSTANCE) == I2C2 ))

#define IS_STRECTCH_ALL(STRECTH)                      (((STRECTH) == I2C_Stretch_En)||\
                                                      ((STRECTH) == I2C_stretch_Dis))

#define IS_GENERAL_CALL_ALL(GN_ALL)                   (((GN_ALL) == General_Call_Disable)||\
                                                      ((GN_ALL) == General_Call_Enable))

#define IS_I2C_MODE_ALL(I2CMODE)                      (((I2CMODE) == I2C_Mode)||\
                                                      ((I2CMODE) == SMBuse_Mode))

#define IS_I2C_RX_INTERUPT(RX_INT)                    (((RX_INT) == I2C_Rx_Interrupt_Dis)||\
                                                      ((RX_INT) == I2C_Rx_Interrupt_En))

#define IS_I2C_EVENT_INTERRUPT(EV_INT)                (((EV_INT) == I2C_Event_Interrupt_Dis)||\
                                                      ((EV_INT) == I2C_Event_Interrupt_En))

#define IS_I2C_ERR_INTERRUPT(ERR_INT)                 (((ERR_INT) == I2C_Error_Interrupt_Dis)||\
                                                      ((ERR_INT) == I2C_Error_Interrupt_En))

#define IS_SLAVE_ADDRESS_MODE(SL_AD_MODE)             (((SL_AD_MODE) == I2C_Slave_Add_7)||\
                                                      ((SL_AD_MODE) == I2C_Slave_Add_10))        

#define IS_DUAL_ADDRESS_ALL(DUAL_ADD)                 (((DUAL_ADD) == I2C_Dual_Addressing_Dis)||\
                                                      ((DUAL_ADD) == I2C_Dual_Addressing_En))

#define IS_MASTER_SPEED_MODE(MS_SP_MODE)              (((MS_SP_MODE) == I2C_Master_SM_Mode)||\
                                                      ((MS_SP_MODE) == I2C_Master_FM_Mode))

#define IS_FM_DUTY_MODE(FM_DUTY)                      (((FM_DUTY) == I2C_FM_Duty_2)||\
                                                      ((FM_DUTY) == I2C_FM_Duty_16_div_9))



/**
 * 
 * @ref  I2C_Stretch_line_define
 * @brief NOSTRETCH: Clock stretching disable (Slave mode)
    This bit is used to disable clock stretching in slave mode when ADDR or BTF flag is set, until
    it is reset by software
 */
#define I2C_Stretch_En                                0
#define I2C_stretch_Dis                               I2C_CR1_START

/*** @ref I2C_General_Call_En_define */
#define General_Call_Disable                          0
#define General_Call_Enable                           I2C_CR1_ENGC

/*** @ref I2C_Mode_define*/
#define I2C_Mode                                      0
#define SMBuse_Mode                                   I2C_CR1_SMBUS

/**
 * @ref I2C_Interrupt_Active_deifne
 *  0: TxE = 1 or RxNE = 1 does not generate any interrupt.
    1: TxE = 1 or RxNE = 1 generates Event Interrupt (whatever the state of DMAEN)
 */
#define I2C_Rx_Interrupt_Dis                          0
#define I2C_Rx_Interrupt_En                           I2C_CR2_ITBUFEN

/**
 * @ref I2C_Event_Enable_define
 * This interrupt is generated when:
    – SB = 1 (Master)
    – ADDR = 1 (Master/Slave)
    – ADD10= 1 (Master)
    – STOPF = 1 (Slave)
    – BTF = 1 with no TxE or RxNE event
    – TxE event to 1 if ITBUFEN = 1
    – RxNE event to 1if ITBUFEN = 1
 */
#define I2C_Event_Interrupt_Dis                          0
#define I2C_Event_Interrupt_En                           I2C_CR2_ITEVTEN

/**
 * @ref I2C_Error_En_define
 * This interrupt is generated when:
    – BERR = 1
    – ARLO = 1
    – AF = 1
    – OVR = 1
    – PECERR = 1
    – TIMEOUT = 1
    – SMBALERT = 1
 */
#define I2C_Error_Interrupt_Dis                          0
#define I2C_Error_Interrupt_En                           I2C_CR2_ITERREN

/**
 * @ref I2C_Freq_define
 * The FREQ bits must be configured with the APB clock frequency value (I2C peripheral
    connected to APB)
 */
#define I2C_Peripheral_input_Freq_2M                     2
#define I2C_Peripheral_input_Freq_3M                     3
#define I2C_Peripheral_input_Freq_4M                     4
#define I2C_Peripheral_input_Freq_5M                     5
#define I2C_Peripheral_input_Freq_6M                     6
#define I2C_Peripheral_input_Freq_7M                     7
#define I2C_Peripheral_input_Freq_8M                     8
#define I2C_Peripheral_input_Freq_9M                     9
#define I2C_Peripheral_input_Freq_10M                    10
#define I2C_Peripheral_input_Freq_11M                    11
#define I2C_Peripheral_input_Freq_12M                    12
#define I2C_Peripheral_input_Freq_13M                    13
#define I2C_Peripheral_input_Freq_14M                    14
#define I2C_Peripheral_input_Freq_15M                    15
#define I2C_Peripheral_input_Freq_16M                    16
#define I2C_Peripheral_input_Freq_17M                    17
#define I2C_Peripheral_input_Freq_18M                    18
#define I2C_Peripheral_input_Freq_19M                    19
#define I2C_Peripheral_input_Freq_20M                    20
#define I2C_Peripheral_input_Freq_21M                    21
#define I2C_Peripheral_input_Freq_22M                    22
#define I2C_Peripheral_input_Freq_23M                    23
#define I2C_Peripheral_input_Freq_24M                    24
#define I2C_Peripheral_input_Freq_25M                    25
#define I2C_Peripheral_input_Freq_26M                    26
#define I2C_Peripheral_input_Freq_27M                    27
#define I2C_Peripheral_input_Freq_28M                    28
#define I2C_Peripheral_input_Freq_29M                    29
#define I2C_Peripheral_input_Freq_30M                    30
#define I2C_Peripheral_input_Freq_31M                    31
#define I2C_Peripheral_input_Freq_32M                    32
#define I2C_Peripheral_input_Freq_33M                    33
#define I2C_Peripheral_input_Freq_34M                    34
#define I2C_Peripheral_input_Freq_35M                    35
#define I2C_Peripheral_input_Freq_36M                    36
#define I2C_Peripheral_input_Freq_37M                    37
#define I2C_Peripheral_input_Freq_38M                    38
#define I2C_Peripheral_input_Freq_39M                    39
#define I2C_Peripheral_input_Freq_40M                    40
#define I2C_Peripheral_input_Freq_41M                    41
#define I2C_Peripheral_input_Freq_42M                    42

// @brief Maximum of SCL Speed in Sm mode and Fm
// @ref Max_speed_of_SCL_define
#define I2C_SCL_SM_Freq_MAX                              100000
#define I2C_SCL_FM_Freq_MAX                              400000

/*** @ref I2C_Slave_Address_length_define*/
#define I2C_Slave_Add_7                                  0
#define I2C_Slave_Add_10                                 I2C_OAR1_ADDMODE

/*** @ref I2C_Dual_addressing_define*/
#define I2C_Dual_Addressing_Dis                          0
#define I2C_Dual_Addressing_En                           I2C_OAR2_ENDUAL

/*** @ref I2C_Master_mode_define*/
#define I2C_Master_SM_Mode                               0
#define I2C_Master_FM_Mode                               I2C_CCR_F_S

/**
 * @ref FM_Duty_Mode_define
 *  0: Fm mode tlow/thigh = 2
    1: Fm mode tlow/thigh = 16/9 (see CCR)
 */
#define I2C_FM_Duty_2                                    0
#define I2C_FM_Duty_16_div_9                             I2C_CCR_DUTY

// For Check multi bit in same time
#define I2C_Event_Master_Byet_Transmitting            ((uint32_t)0x00070080) /* TRA, BUSY, MSL, TXE flags*/

enum I2C_Polling
{
   I2C_Disable_polling,
   I2C_Enable_polling
};

// It is used to send a stop condition or not
typedef enum 
{
   I2C_Without_Stop,
   I2C_With_Stop
}En_I2C_Stop_condition;


// It is used to check the state of the line if it is in busy mode
typedef enum 
{
   Start,
   Repeated_Start
}En_I2C_RepeatStart;


// It is used to send start condition or not
typedef enum
{
   Fun_St_Dis = 0,
   Fun_St_En
}En_FunctionState;


// Flag states
typedef enum
{
   Reset = 0,
   Set
}En_I2C_FlagState;


// Flags that are checked while the program is running
typedef enum
{
   I2C_FLAG_MSL = 0,
   I2C_FLAG_BUSY,
   I2C_FLAG_TRA,
   I2C_FLAG_GENCALL,
   I2C_FLAG_SMBDEFAULT,
   I2C_FLAG_SMBHOST,
   I2C_FLAG_DUALF,
   I2C_FLAG_SB,
   I2C_FLAG_ADDR,
   I2C_FLAG_BTF,
   I2C_FLAG_ADD10,
   I2C_FLAG_STOPF,
   I2C_FLAG_RXNE,
   I2C_FLAG_TXE,
   I2C_FLAG_BERR,
   I2C_FLAG_ARLO,
   I2C_FLAG_AF,
   I2C_FLAG_OVR,
   I2C_FLAG_PECERR,
   I2C_FLAG_TIMEOUT,
   I2C_FLAG_SMBALERT,
   Master_Byet_Transmitting = ((uint32_t)0x00070080)
}EN_I2C_Flag;


typedef enum
{
   I2C_Write = 0,
   I2C_Read
}En_I2C_direction;

//==============================================================================


//_________________________________ I2C_API ____________________________________
typedef struct 
{
    uint16_t Address_mode;                      // This member configures The I2C slave address length
                                                // This parameter must be set base on @ref I2C_Slave_Address_length_define
    uint16_t Slave_Address1;                    // This memeber configures The I2C slave Address

    uint8_t Dual_address;                       // This memeber configures The I2C slave dual address
                                                // This parameter must be set base on @ref I2C_Dual_addressing_define
    uint8_t Slave_Address2;                     // This member confiugres The I2C slave seconde Address

}I2C_Address;



typedef struct _St_I2C_API
{
    St_I2C_Typedef *I2C_Inst;                                  // Specifies the I2C Peripheral
                                                               // This parameter must be set base on @ref I2C_Peripheral_define
    I2C_Address *Slave_Address;                                // This member configures The I2C slave Address
    
    uint32_t No_Stretch;                                       // This member configures the i2c stratch
                                                               // This parameter must be set base on @ref I2C_Stretch_line_define
    uint32_t Gneral_Call_En;                                   // This member configures the I2c Gneranl call enable
                                                               // This paramtetre must be set base on @ref I2C_General_Call_En_define
    uint32_t I2C_Modes;                                        // This member configures the I2C Mode
                                                               // This parametere must be set base on @ref I2C_Mode_define
    uint32_t RX_Intrrupt_En;                                   // This member configures the I2C Interrupt active
                                                               // This paramerte must be set base on @ref I2C_Interrupt_Active_deifne
    uint32_t Event_Interrupt_En;                               // This meember configures the I2C Event interrupt enable
                                                               // This parametre must be set base on @ref I2C_Event_Enable_define
    uint32_t Error_Interrupt_En;                               // This memeber configures The I2C Error interrupt 
                                                               // This pareamerte must be set base on @ref I2C_Error_En_define
    uint32_t Peripheral_Input_Freq;                            // This memeber configures The I2C Freq
                                                               // This paremetre must be set base on @ref I2C_Freq_define
    uint32_t I2C_Master_Mode;                                  // This member configures The I2C Master Mode
                                                               // This parametre must be set base on @ref I2C_Master_mode_define
    uint32_t FM_Duty_Mode;                                     // This member configures The I2C FM mode when as master
                                                               // This parameter must be set base on @ref FM_Duty_Mode_define 
   uint32_t SCL_Freq;                                          // This member configure The I2C SCL Frequency
                                                               // This parameter value must be less then according to Mode @ref Max_speed_of_SCL_define
   uint8_t *Tx_Buff;                                           // This mmmber to Write data to SDA line
   uint8_t Rx_Buff;                                            // This member to Receive data form SDA line
   void (*P_SB_CallBack)(struct _St_I2C_API *I2Cx);            // I2C SB CallBack Function pointer
   void (*P_ADDR_CallBack)(struct _St_I2C_API *I2Cx);          // I2C ADDR CallBack Function pointer
   void (*P_ADDR10_CallBack)(struct _St_I2C_API *I2Cx);        // I2C ADDR10 CallBack Function pointer
   void (*P_STOPF_CallBack)(struct _St_I2C_API *I2Cx);         // I2C STOPF CallBack Function pointer
   void (*P_BTF_CallBack)(struct _St_I2C_API *I2Cx);           // I2C BTF CallBack Function pointer
   void (*P_TXE_CallBack)(struct _St_I2C_API *I2Cx);           // I2C TXE CallBack Function pointer
   void (*P_RXNE_CallBack)(struct _St_I2C_API *I2Cx);          // I2C RXNE CallBack Function pointer
   void (*P_OVR_CallBack)(struct _St_I2C_API *I2Cx);           // I2C OVR CallBack Function pointer
   void (*P_AF_CallBack)(struct _St_I2C_API *I2Cx);            // I2C AF CallBack Function pointer
   void (*P_TIMEOUT_CallBack)(struct _St_I2C_API *I2Cx);       // I2C TIMEOUT CallBack Function pointer

}St_I2C_API;                                    

//==============================================================================


//______________________________ Gloabl Functions ______________________________
uint8_t I2C_Init(St_I2C_API *I2Cx);
uint8_t I2C_Deinit(St_I2C_API *I2Cx);  
uint8_t I2C_Master_Write(St_I2C_API *I2Cx, uint16_t Add, uint8_t *Tx_Buf, uint8_t data_len,\
                        En_I2C_Stop_condition Stop_cond, En_I2C_RepeatStart Repeat_start,\
                        enum I2C_Polling polling);
uint8_t I2C_Master_Read(St_I2C_API *I2Cx, uint16_t Add, uint8_t *Tx_Buf, uint8_t data_len,\
                        En_I2C_Stop_condition Stop_cond, En_I2C_RepeatStart Repeat_start,\
                        enum I2C_Polling polling);
uint8_t I2C_Slave_Write(St_I2C_API *I2Cx, uint8_t *data, uint8_t data_length);
uint8_t I2C_Slave_Read(St_I2C_API *I2Cx, uint8_t *data, uint8_t data_length);
uint8_t I2C_Slave_Write_IT(St_I2C_API *I2Cx);
uint8_t I2C_Slave_Read_IT(St_I2C_API *I2Cx);
uint8_t I2C_GenerateStart(St_I2C_API *I2Cx, En_I2C_RepeatStart Repeat_start,En_FunctionState FunctionState);
uint8_t I2C_GenerateStop(St_I2C_API *I2Cx, En_FunctionState FunctionState);
uint8_t I2C_Send_Add(St_I2C_API *I2Cx, uint16_t Add, En_I2C_direction direction);
En_I2C_FlagState I2C_Get_FlagStatus(St_I2C_API *I2Cx,EN_I2C_Flag Flag);
void I2C_Enable_ACK(St_I2C_API *I2Cx);
void I2C_Disable_ACK(St_I2C_API *I2Cx);
void SB_CallBack_I2C(struct _St_I2C_API *I2Cx);
void ADDR_CallBack_I2C(struct _St_I2C_API *I2Cx);
void ADDR10_CallBack_I2C(struct _St_I2C_API *I2Cx);
void STOPF_CallBack_I2C(struct _St_I2C_API *I2Cx);
void BTF_CallBack_I2C(struct _St_I2C_API *I2Cx);
void TXE_CallBack_I2C(struct _St_I2C_API *I2Cx);
void RXNE_CallBack_I2C(struct _St_I2C_API *I2Cx);
void OVR_CallBack_I2C(struct _St_I2C_API *I2Cx);
void AF_CallBack_I2C(struct _St_I2C_API *I2Cx);
void TIMEOUT_CallBack_I2C(struct _St_I2C_API *I2Cx);
//==============================================================================


#endif