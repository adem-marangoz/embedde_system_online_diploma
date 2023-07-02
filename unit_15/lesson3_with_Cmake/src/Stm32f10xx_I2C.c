/**
 * @file Stm32f10xx_I2C.c
 * @author adem alnajjar (adem.marangoz95@gamil.com)
 * @brief The I2C API
 * @version 0.1
 * @date 2022-09-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//______________________________ Include Files _________________________________
#include "Stm32f10xx_I2C.h"
#include "Stm32f10xx_GPIO.h"
#include "Stm32f10xx_RCC.h"
#include <stdio.h>

//==============================================================================


//______________________________ Generic Macro _________________________________

//==============================================================================


//_________________ Decleration Local Functions & Variables ____________________
uint8_t I2C_Clock_Config_Pins(St_I2C_API *I2Cx);
//==============================================================================


//______________________________ External Objects ______________________________
St_I2C_API i2c1_config;
St_I2C_API i2c2_config;
//==============================================================================


//______________________________ Global Function _______________________________

/**
 * @brief Is used to Config I2C
 * @param I2Cx : data Structure for I2C API
 * @return      uint8_t  : 1 = Succesed
 *                         0 = Failed
 */
uint8_t I2C_Init(St_I2C_API *I2Cx)
{
    if(I2Cx->I2C_Modes == I2C_Mode)
    {
        // Check Inputs data to I2C structure
        if(!(IS_I2C_ALL_INSTANCE(I2Cx->I2C_Inst))){return 0;}
        if(!(IS_STRECTCH_ALL(I2Cx->No_Stretch))){return 0;}
        if(!(IS_GENERAL_CALL_ALL(I2Cx->Gneral_Call_En))){return 0;}
        if(!(IS_I2C_MODE_ALL(I2Cx->I2C_Master_Mode))){return 0;}
        if(!(IS_I2C_RX_INTERUPT(I2Cx->RX_Intrrupt_En))){return 0;}
        if(!(IS_I2C_EVENT_INTERRUPT(I2Cx->Event_Interrupt_En))){return 0;}
        if(!(IS_I2C_ERR_INTERRUPT(I2Cx->Error_Interrupt_En))){return 0;}
        // if(!(IS_SLAVE_ADDRESS_MODE(I2Cx->Slave_Address->Address_mode))){return 0;}
        // if(!(IS_DUAL_ADDRESS_ALL(I2Cx->Slave_Address->Dual_address))){return 0;}
        if(!(IS_MASTER_SPEED_MODE(I2Cx->I2C_Master_Mode))){return 0;}
        if(!(IS_FM_DUTY_MODE(I2Cx->FM_Duty_Mode))){return 0;}

        //Initially giving base functions addresses values
        if(I2Cx->P_SB_CallBack == NULL){I2Cx->P_SB_CallBack = SB_CallBack_I2C;}
        if(I2Cx->P_ADDR_CallBack == NULL){I2Cx->P_ADDR_CallBack = ADDR_CallBack_I2C;}
        if(I2Cx->P_ADDR10_CallBack == NULL){I2Cx->P_ADDR10_CallBack = ADDR10_CallBack_I2C;}
        if(I2Cx->P_SB_CallBack == NULL){I2Cx->P_SB_CallBack = STOPF_CallBack_I2C;}
        if(I2Cx->P_BTF_CallBack == NULL){I2Cx->P_BTF_CallBack = BTF_CallBack_I2C;}
        if(I2Cx->P_TXE_CallBack == NULL){I2Cx->P_TXE_CallBack = TXE_CallBack_I2C;}
        if(I2Cx->P_RXNE_CallBack == NULL){I2Cx->P_RXNE_CallBack = RXNE_CallBack_I2C;}
        if(I2Cx->P_OVR_CallBack == NULL){I2Cx->P_OVR_CallBack = OVR_CallBack_I2C;}
        if(I2Cx->P_TIMEOUT_CallBack == NULL){I2Cx->P_TIMEOUT_CallBack = TIMEOUT_CallBack_I2C;}
        if(I2Cx->P_AF_CallBack == NULL){I2Cx->P_AF_CallBack = AF_CallBack_I2C;}
        

        
        // Confige Peripheral Clock Freq
        uint32_t PCLK1 = Get_APB1_Freq();
        uint32_t temp_freq = 0;
        if(I2Cx->Peripheral_Input_Freq < PCLK1)
        {
            
            // Check peripheral clock input with user clock Master clock mode
            if(I2Cx->I2C_Master_Mode == I2C_Master_SM_Mode)
            {
                if(I2Cx->Peripheral_Input_Freq < I2C_Peripheral_input_Freq_2M){return 0;}
            }else
            {
                if(I2Cx->Peripheral_Input_Freq < I2C_Peripheral_input_Freq_4M){return 0;}
            }

            // To config The Peripheral input clock
            I2Cx->I2C_Inst->I2C_CR2 &= ~(I2C_CR2_FREQ);
            temp_freq = (PCLK1 >> 6) & 0x3F;
            I2Cx->I2C_Inst->I2C_CR2 |= temp_freq;
        }else
        {
            return 0;
        }

        // Config I2C SCL Freq base on the Fm or Sm
        if(I2Cx->I2C_Master_Mode == I2C_Master_SM_Mode)
        {
            if(I2Cx->SCL_Freq >= I2C_SCL_SM_Freq_MAX)
            {
                // uint16_t temp = (PCLK1)/(2*I2Cx->SCL_Freq);
                // temp &= 0x0FFF;
                I2Cx->I2C_Inst->I2C_CCR |= (PCLK1)/(2*I2Cx->SCL_Freq);
            }else
            {
                return 0;
            }
        }else
        {
            if(I2Cx->SCL_Freq >= I2C_SCL_FM_Freq_MAX)
            {
                if(I2Cx->FM_Duty_Mode == I2C_FM_Duty_2)
                {
                    I2Cx->I2C_Inst->I2C_CCR |= (uint16_t)((PCLK1)/(3*I2Cx->SCL_Freq));
                }else
                {
                    I2Cx->I2C_Inst->I2C_CCR |= (uint16_t)((PCLK1)/(25*I2Cx->SCL_Freq));
                }
            }else
            {
                return 0;
            }
        }

        // Config The Maximum rise time in Fm/Sm mode
        I2Cx->I2C_Inst->I2C_TRISE &= ~(I2C_TRISE_F_S);
        I2Cx->I2C_Inst->I2C_TRISE |= temp_freq + (uint32_t)1;

        // Set Slave Addressing 1 and select Slave address length
        // I2Cx->I2C_Inst->I2C_OAR1 |= (I2Cx->Slave_Address->Slave_Address1) | (I2Cx->Slave_Address->Address_mode);

        // Select Dual slave Addressing
        // I2Cx->I2C_Inst->I2C_OAR2 |= (I2Cx->Slave_Address->Slave_Address2) | (I2Cx->Slave_Address->Dual_address);

        // Select Rx and Event and Error and Peripheral clock Frequency
        I2Cx->I2C_Inst->I2C_CR2 |= (I2Cx->RX_Intrrupt_En) | (I2Cx->Event_Interrupt_En) | (I2Cx->Error_Interrupt_En) | (I2Cx->Peripheral_Input_Freq);

        // Select F/S & I2C Duty
        I2Cx->I2C_Inst->I2C_CCR |= (I2Cx->I2C_Master_Mode) | (I2Cx->FM_Duty_Mode);

        
        // Set ACK when receive data
        I2Cx->I2C_Inst->I2C_CR1 |= I2C_CR1_ACK | I2Cx->Gneral_Call_En | I2Cx->No_Stretch;

        // Config I2C Pins and Enable I2C clock
        I2C_Clock_Config_Pins(I2Cx);

        // Enable I2C IRQ
        if(I2Cx->RX_Intrrupt_En)
        {
            if(I2Cx->I2C_Inst == I2C1){NVIC_EnableIRQ(I2C1_EV_IRQn);}
            if(I2Cx->I2C_Inst == I2C2){NVIC_EnableIRQ(I2C2_EV_IRQn);}
        }

        if(I2Cx->Error_Interrupt_En)
        {
            if(I2Cx->I2C_Inst == I2C1){NVIC_EnableIRQ(I2C1_ER_IRQn);}
            if(I2Cx->I2C_Inst == I2C2){NVIC_EnableIRQ(I2C2_ER_IRQn);}
        }

        // Set I2C peripheral
        I2Cx->I2C_Inst->I2C_CR1 |= I2C_CR1_PE;

        return 1;
    }else
    {
        // Yet this API is not support SMBus 
        // TODO SMBus configurtion 
        return 0;
    }

}

/**
 * @brief Is Used to Reset Config I2C Peripheral
 * @param I2Cx : data Structure for I2C API
 * @return      uint8_t  : 1 = Succesed
 *                         0 = Failed
 */
uint8_t I2C_Deinit(St_I2C_API *I2Cx)
{
    if(I2Cx->I2C_Inst == I2C1)
    {
        __APB1RSTR_I2C1RST();
        NVIC_DisableIRQ(I2C1_ER_IRQn);
        NVIC_DisableIRQ(I2C1_EV_IRQn);
    }else
    {
        __APB1RSTR_I2C2RST();
        NVIC_DisableIRQ(I2C2_ER_IRQn);
        NVIC_DisableIRQ(I2C2_EV_IRQn);
    }
}


/**
 * @brief Is Used to Send data form Master to Slave
 * @param I2Cx : data Structure for I2C API
 * @param Add   : The Slave Address
 * @param Tx_Buf    : The Pointer indicating the data to be sent
 * @param data_len : The Length Data of want send
 * @param Stop_cond : condition for send stop condition after send data
 * @param Repeat_start : condition to repate send Start condition or not
 * @param I2Cpollingx : Not used Yet
 * @return      uint8_t  : 1 = Succesed
 *                         0 = Failed
 */
uint8_t I2C_Master_Write(St_I2C_API *I2Cx, uint16_t Add, uint8_t *Tx_Buf, uint8_t data_len,\
                        En_I2C_Stop_condition Stop_cond, En_I2C_RepeatStart Repeat_start,\
                        enum I2C_Polling polling)
{
    // Generate Start Condition
    I2C_GenerateStart(I2Cx,Start,Fun_St_En);

    // Check if SB is Set
    while(I2C_Get_FlagStatus(I2Cx, I2C_FLAG_SB));
    
    uint32_t dummy_read = I2Cx->I2C_Inst->I2C_SR1;

    // Write Device Address to I2C_DR
    I2C_Send_Add(I2Cx, Add, I2C_Write);

    // Read ADDR Bit in I2C_SR1 register
    while(!(I2C_Get_FlagStatus(I2Cx, I2C_FLAG_ADDR)));

    // Check MSL , BUSY, TRA and TXE flags
    while(!(I2C_Get_FlagStatus(I2Cx, Master_Byet_Transmitting)));


    while(data_len)
    {
        // Write Data to I2C_Dr
        I2Cx->I2C_Inst->I2C_DR = *Tx_Buf;
        
        // Wait until Set TxE flag
        while(!(I2C_Get_FlagStatus(I2Cx, I2C_FLAG_TXE)));
        Tx_Buf++;
        data_len--;
    }

    if(Stop_cond == I2C_With_Stop)
    {
        I2C_GenerateStop(I2Cx,Fun_St_En);
    }else
    {
        return 0 ;
    }
}

/**
 * @brief Is Used to send Stop condition form master 
 * @param I2Cx : data Structure for I2C API
 * @param FunctionState Is used to Clear Or Set Stop conditon in I2C_CR1 register
 * @return      uint8_t  : 1 = Succesed
 *                         0 = Failed
 */
uint8_t I2C_GenerateStop(St_I2C_API *I2Cx, En_FunctionState FunctionState)
{
    if(FunctionState == Fun_St_En)
    {
        I2Cx->I2C_Inst->I2C_CR1 |= I2C_CR1_STOP;
    }else
    {
        I2Cx->I2C_Inst->I2C_CR1 &= ~(I2C_CR1_STOP);
    }

    return 1;
}

/**
 * @brief Is Used to Send Device Address via SDA to Slave
 * @param I2Cx : data Structure for I2C API
 * @param Add : The Device Address
 * @param direction : Determining the mode of the master while sending the address of the slave
 * @return      uint8_t  : 1 = Succesed
 *                         0 = Failed 
 */
uint8_t I2C_Send_Add(St_I2C_API *I2Cx, uint16_t Add, En_I2C_direction direction)
{  
    Add = (Add << 1);
    //if Address mode is 10 bit
    if((I2Cx->Slave_Address->Address_mode & I2C_Slave_Add_10) == I2C_Slave_Add_10)
    {
        // Send Header to Slave
        uint8_t temp_add = (uint8_t)(Add >> 8);
        temp_add = temp_add & 0x06;
        temp_add |= (0xF0 | temp_add);
        I2Cx->I2C_Inst->I2C_DR = (uint8_t)(temp_add | direction);
        while(!(I2C_Get_FlagStatus(I2Cx, I2C_FLAG_ADD10)));         
         // Send Address to Slave 
        I2Cx->I2C_Inst->I2C_DR = (uint8_t)Add;  

    }else
    {
        // Write Device Address with I2C Direction transimitter or receiver
        I2Cx->I2C_Inst->I2C_DR = (Add | direction);  
    }

    return 1;
}


/**
 * @brief Is Used to Receive data form Slave to master
 * @param I2Cx : data Structure for I2C API
 * @param Add   : The Slave Address
 * @param Tx_Buf    : The Pointer indicating the data to be receive
 * @param data_len : The Length Data of want send
 * @param Stop_cond : condition for send stop condition after send data
 * @param Repeat_start : condition to repate send Start condition or not
 * @param I2Cpollingx : Not used Yet
 * @return      uint8_t  : 1 = Succesed
 *                         0 = Failed
 */
uint8_t I2C_Master_Read(St_I2C_API *I2Cx, uint16_t Add, uint8_t *Tx_Buf, uint8_t data_len,\
                        En_I2C_Stop_condition Stop_cond, En_I2C_RepeatStart Repeat_start,\
                        enum I2C_Polling polling)
{
    // Generate Start Condition
    I2C_GenerateStart(I2Cx,Repeat_start,Fun_St_En);

    // Check if SB is Set
    while(I2C_Get_FlagStatus(I2Cx, I2C_FLAG_SB));
    
    uint32_t dummy_read = I2Cx->I2C_Inst->I2C_SR1;

    // Write Device Address to I2C_DR
    I2C_Send_Add(I2Cx, Add, I2C_Read);

    // Read ADDR To Reset in I2C_SR1 register
    while(!(I2C_Get_FlagStatus(I2Cx, I2C_FLAG_ADDR)));

    // Read sended Data form Slave
    while(data_len)
    {
        // Wait until Set RXNE flag
        while(!(I2C_Get_FlagStatus(I2Cx, I2C_FLAG_RXNE)));

        // Read I2C_DR and write to Buffer
        *Tx_Buf = I2Cx->I2C_Inst->I2C_DR;
        Tx_Buf++;
        data_len--;
    }

    // Disable ACK to Stop Receive data form Slave
    I2C_Disable_ACK(I2Cx);

    // Read Last Received Data from Slave
    *Tx_Buf = I2Cx->I2C_Inst->I2C_DR;

    // Send Stop Condition
    if(Stop_cond == I2C_With_Stop)
    {
        I2C_GenerateStop(I2Cx, Fun_St_En);
    }

    // Return Set ACK I2C
    I2C_Enable_ACK(I2Cx);

    return 1;
}

/**
 * @brief Is used to transmit data form slave by Interrupt mode
 * @param I2Cx : data Structure for I2C API
 * @return      uint8_t  : 1 = Succesed
 *                         0 = Failed
 */
uint8_t I2C_Slave_Write_IT(St_I2C_API *I2Cx)
{
    // Write data to I2C_DR data register
    uint32_t temp = *(I2Cx->Tx_Buff);
    I2Cx->I2C_Inst->I2C_DR = temp;
    (I2Cx->Tx_Buff)++;
}


/**
 * @brief Is Used to Receive data form Master to slave by Interrupt
 * @param I2Cx : data Structure for I2C API
 * @return      uint8_t  : 1 = Succesed
 *                         0 = Failed
 */
uint8_t I2C_Slave_Read_IT(St_I2C_API *I2Cx)
{
    I2Cx->Rx_Buff = I2Cx->I2C_Inst->I2C_DR;
    (I2Cx->Rx_Buff)++;
    // return received data form Master
    return (uint8_t)I2Cx->I2C_Inst->I2C_DR;
}


/**
 * @brief Is Used to Transimit data from slave to master by polling mechanics 
 * @param I2Cx : data Structure for I2C API
 * @param data : The Pointer indicating the data to be sent
 * @param data_length : The length of data to wand send
 * @return      uint8_t  : 1 = Succesed
 *                         0 = Failed
 */
uint8_t I2C_Slave_Write(St_I2C_API *I2Cx, uint8_t *data, uint8_t data_length)
{
    // Wait until Set ADDR bit in I2C_SR1 register
    while(!(I2C_Get_FlagStatus(I2Cx, I2C_FLAG_ADDR)));

    uint32_t dummy_read = I2Cx->I2C_Inst->I2C_SR2;

    while (data_length)
    {
        // Wait until Set TXE bit in I2C_SR1 register
        while(!(I2C_Get_FlagStatus(I2Cx, I2C_FLAG_TXE)));

        I2Cx->I2C_Inst->I2C_DR = *data;
        data++;
        data_length--;
    }

    // When Master Send NACK is set by hardware AF(Acknowledge Failure) bit in I2C_SR1
    // Must Clear AF bit 
    I2Cx->I2C_Inst->I2C_SR1 &= ~(I2C_SR1_AF); 

}


/**
 * @brief Is used to Receive data form master by polline  mechanics
 * @param I2Cx : data Structure for I2C API
 * @param data : The Pointer indicating the data to be received
 * @param data_length : The Length Data of want receive
 * @return      uint8_t  : 1 = Succesed
 *                         0 = Failed
 */
uint8_t I2C_Slave_Read(St_I2C_API *I2Cx, uint8_t *data, uint8_t data_length)
{
    // Wait until Set ADDR bit in I2C_SR1 register
    while(!(I2C_Get_FlagStatus(I2Cx, I2C_FLAG_ADDR)));

    while(data_length)
    {
        // Wait until Set RXNE bit in I2C_SR1 register
        while(!(I2C_Get_FlagStatus(I2Cx, I2C_FLAG_RXNE)));
        
        // Write data to Buffer
        *data = I2Cx->I2C_Inst->I2C_DR;
        data++;
        data_length--;
    }

}


/**
 * @brief Is Used to generate The START condition By master
 * @param I2Cx : data Structure for I2C API
 * @param Repeat_start : condition to repate send Start condition or not
 * @param FunctionState : Is used to repate send start condition or not
 * @return      uint8_t  : 1 = Succesed
 *                         0 = Failed
 */
uint8_t I2C_GenerateStart(St_I2C_API *I2Cx, En_I2C_RepeatStart Repeat_start,En_FunctionState FunctionState)
{
    if (Repeat_start == Start)
    {
        // Check if the I2C bus if Busy by detection of SDA or SCL
        while (I2C_Get_FlagStatus(I2Cx, I2C_FLAG_BUSY));
    }else
    {

    }

    // For Check to Generate Start condition
    if(FunctionState == Fun_St_En)
    {
        I2Cx->I2C_Inst->I2C_CR1 |= I2C_CR1_START;
    }else
    {
        I2Cx->I2C_Inst->I2C_CR1 &= ~(I2C_CR1_START);
    }
    return 1;
}


/**
 * @brief Is Used to check flags after doing any process
 * @param I2Cx : data Structure for I2C API
 * @param Flag : flag to check
 * @return En_I2C_FlagState  : Return the state of the flag 
 *                         0 : Reset
 *                         1 : Set
 */
En_I2C_FlagState I2C_Get_FlagStatus(St_I2C_API *I2Cx,EN_I2C_Flag Flag)
{
    En_I2C_FlagState Flag_state = Reset;
    uint32_t flag1 = 0, flag2 = 0, lastevent = 0;
    // To Check Flag state
    switch (Flag)
    {
        case I2C_FLAG_MSL:
            if((I2Cx->I2C_Inst->I2C_SR2 & I2C_SR2_MSL) == I2C_SR2_MSL) {Flag_state = Set;}
            break;
        case I2C_FLAG_BUSY:
            if((I2Cx->I2C_Inst->I2C_SR2 & I2C_SR2_BUSY) == I2C_SR2_BUSY) {Flag_state = Set;}
            break;
        case I2C_FLAG_TRA:
            if((I2Cx->I2C_Inst->I2C_SR2 & I2C_SR2_TRA) == I2C_SR2_TRA) {Flag_state = Set;}
            break;
        case I2C_FLAG_GENCALL:
            if((I2Cx->I2C_Inst->I2C_SR2 & I2C_SR2_GENCALL) == I2C_SR2_GENCALL) {Flag_state = Set;}
            break;
        case I2C_FLAG_SMBDEFAULT:
            if((I2Cx->I2C_Inst->I2C_SR2 & I2C_SR2_SMBDEFAULT) == I2C_SR2_SMBDEFAULT) {Flag_state = Set;}
            break;
        case I2C_FLAG_SMBHOST:
            if((I2Cx->I2C_Inst->I2C_SR2 & I2C_SR2_SMBHOST) == I2C_SR2_SMBHOST) {Flag_state = Set;}
            break;
        case I2C_FLAG_DUALF:
            if((I2Cx->I2C_Inst->I2C_SR2 & I2C_SR2_DUALF) == I2C_SR2_DUALF) {Flag_state = Set;}
            break;
        case I2C_FLAG_SB:
            if((I2Cx->I2C_Inst->I2C_SR1 & I2C_SR1_SB) == I2C_SR1_SB) {Flag_state = Set;}
            break;
        case I2C_FLAG_ADDR:
            if((I2Cx->I2C_Inst->I2C_SR1 & I2C_SR1_ADDR) == I2C_SR1_ADDR) 
            {
                Flag_state = Set;
                flag2 = I2Cx->I2C_Inst->I2C_SR2;
            }else
            {
                Flag_state = Reset;
            }
            break;
        case I2C_FLAG_BTF:
            if((I2Cx->I2C_Inst->I2C_SR1 & I2C_SR1_BTF) == I2C_SR1_BTF) {Flag_state = Set;}
            break;
        case I2C_FLAG_ADD10:
            if((I2Cx->I2C_Inst->I2C_SR1 & I2C_SR1_ADD10) == I2C_SR1_ADD10) {Flag_state = Set;}
            break;
        case I2C_FLAG_STOPF:
            if((I2Cx->I2C_Inst->I2C_SR1 & I2C_SR1_STOPF) == I2C_SR1_STOPF) {Flag_state = Set;}
            break;
        case I2C_FLAG_RXNE:
            if((I2Cx->I2C_Inst->I2C_SR1 & I2C_SR1_RXNE) == I2C_SR1_RXNE) {Flag_state = Set;}
            break;
        case I2C_FLAG_TXE:
            if((I2Cx->I2C_Inst->I2C_SR1 & I2C_SR1_TXE) == I2C_SR1_TXE) {Flag_state = Set;}
            break;
        case I2C_FLAG_BERR:
            if((I2Cx->I2C_Inst->I2C_SR1 & I2C_SR1_BERR) == I2C_SR1_BERR) {Flag_state = Set;}
            break;
        case I2C_FLAG_ARLO:
            if((I2Cx->I2C_Inst->I2C_SR1 & I2C_SR1_ARLO) == I2C_SR1_ARLO) {Flag_state = Set;}
            break;
        case I2C_FLAG_AF:
            if((I2Cx->I2C_Inst->I2C_SR1 & I2C_SR1_AF) == I2C_SR1_AF) {Flag_state = Set;}
            break;
        case I2C_FLAG_OVR:
            if((I2Cx->I2C_Inst->I2C_SR1 & I2C_SR1_OVR) == I2C_SR1_OVR) {Flag_state = Set;}
            break;
        case I2C_FLAG_PECERR:
            if((I2Cx->I2C_Inst->I2C_SR1 & I2C_SR1_PECERR) == I2C_SR1_PECERR) {Flag_state = Set;}
            break;
        case I2C_FLAG_TIMEOUT:
            if((I2Cx->I2C_Inst->I2C_SR1 & I2C_SR1_TIMEOUT) == I2C_SR1_TIMEOUT) {Flag_state = Set;}
            break;
        case I2C_FLAG_SMBALERT:
            if((I2Cx->I2C_Inst->I2C_SR1 & I2C_SR1_SMBALERT) == I2C_SR1_SMBALERT) {Flag_state = Set;}
            break;
        case Master_Byet_Transmitting:
            flag1 = I2Cx->I2C_Inst->I2C_SR1;
            flag2 = I2Cx->I2C_Inst->I2C_SR2;
            flag2 = flag2 << 16;
            lastevent = (flag1 | flag2) & ((uint32_t)0x00FFFFFF);
            if((lastevent & Flag) == Flag)
            {
                Flag_state = Set;
            }else
            {
                Flag_state = Reset;
            }
            break;
        default:
            break;
    }
    return Flag_state;
}


/**
 * @brief Is Used to active the ACK bit
 * @param I2Cx : data Structure for I2C API
 */
void I2C_Enable_ACK(St_I2C_API *I2Cx)
{
    I2Cx->I2C_Inst->I2C_CR1 |= I2C_CR1_ACK;
}

/**
 * @brief Is used to Reset The ACK bit
 * @param I2Cx : data Structure for I2C API
 */
void I2C_Disable_ACK(St_I2C_API *I2Cx)
{
    I2Cx->I2C_Inst->I2C_CR1 &= ~(I2C_CR1_ACK);
}


/**
 * @brief Start condtion Interrupt defualt CallBacks
 * @param I2Cx : data Structure for I2C API
 */
__weak void SB_CallBack_I2C(struct _St_I2C_API *I2Cx)
{
    UNUSED(I2Cx);
}


/**
 * @brief ADDR Interrupt defualt CallBacks
 * @param I2Cx : data Structure for I2C API
 */
__weak void ADDR_CallBack_I2C(struct _St_I2C_API *I2Cx)
{
    uint32_t dummy_read = I2Cx->I2C_Inst->I2C_SR1;
    dummy_read = I2Cx->I2C_Inst->I2C_SR2;
    if(I2C_Get_FlagStatus(I2Cx, I2C_SR2_MSL)) // if Master Mode
    {

        // I2C_Master_Write_IT(I2Cx);
    }else // If Slave Mode
    {
        if(!(I2C_Get_FlagStatus(I2Cx, I2C_SR2_TRA))) // if Transmitter Mode
        {
            I2C_Slave_Write_IT(I2Cx);
        }else // if Receiver Mode
        {

        }
    }
    UNUSED(I2Cx);
}


/**
 * @brief ADDR10 Interrupt defualt CallBacks
 * @param I2Cx : data Structure for I2C API
 */
__weak void ADDR10_CallBack_I2C(struct _St_I2C_API *I2Cx)
{
    uint32_t dummy_read = I2Cx->I2C_Inst->I2C_SR1;
    // Now the Master Not doing anything until to send address to Slave and set ADDR
    UNUSED(I2Cx);
}


/**
 * @brief Stop condtion Interrupt defualt CallBacks
 * @param I2Cx : data Structure for I2C API
 */
__weak void STOPF_CallBack_I2C(struct _St_I2C_API *I2Cx)
{
    UNUSED(I2Cx);
}


/**
 * @brief BTF Interrupt defualt CallBacks
 * @param I2Cx : data Structure for I2C API
 */
__weak void BTF_CallBack_I2C(struct _St_I2C_API *I2Cx)
{
    UNUSED(I2Cx);
}


/**
 * @brief TxE empty Interrupt defualt CallBacks
 * @param I2Cx : data Structure for I2C API
 */
__weak void TXE_CallBack_I2C(struct _St_I2C_API *I2Cx)
{
    if(I2C_Get_FlagStatus(I2Cx, I2C_SR2_MSL))
    {
        // For Master
    }else
    {
        if(!(I2C_Get_FlagStatus(I2Cx, I2C_SR2_TRA)))
        {
            I2C_Slave_Write_IT(I2Cx);
        }
    }
    UNUSED(I2Cx);
}


/**
 * @brief RxNe Not Empty Interrupt defualt CallBacks
 * @param I2Cx : data Structure for I2C API
 */
__weak void RXNE_CallBack_I2C(struct _St_I2C_API *I2Cx)
{
    if(I2C_Get_FlagStatus(I2Cx, I2C_SR2_MSL))
    {
        // For Master
    }else
    {
        if(I2C_Get_FlagStatus(I2Cx, I2C_SR2_TRA)) // if Transmitter Mode 
        {
        }else // if Receiver Mode
        {
            I2C_Slave_Read_IT(I2Cx);
        }
    }
    UNUSED(I2Cx);
}


/**
 * @brief Overrun  Interrupt defualt CallBacks
 * @param I2Cx : data Structure for I2C API
 */
__weak void OVR_CallBack_I2C(struct _St_I2C_API *I2Cx)
{
    UNUSED(I2Cx);
}


/**
 * @brief Timeout Interrupt defualt CallBacks
 * @param I2Cx : data Structure for I2C API
 */
__weak void TIMEOUT_CallBack_I2C(struct _St_I2C_API *I2Cx)
{
    UNUSED(I2Cx);
}

/**
 * @brief Acknowledge Interrupt defualt CallBacks
 * @param I2Cx : data Structure for I2C API
 */
__weak void AF_CallBack_I2C(struct _St_I2C_API *I2Cx)
{
    if((I2Cx->I2C_Inst->I2C_SR2 & I2C_SR2_MSL) == I2C_SR2_MSL)
    {
        // For master
    }else
    {
        I2Cx->I2C_Inst->I2C_SR1 &= ~(I2C_SR1_AF);
    }
    UNUSED(I2Cx);
}

/**
 * @brief This function handles I2C1 Event global interrupt.
 */
void I2C1_EV_Handler(void)
{
    if((I2C1->I2C_SR1 & I2C_SR1_SB) == I2C_SR1_SB)
        i2c1_config.P_SB_CallBack(&i2c1_config);
    else if((I2C1->I2C_SR1 & I2C_SR1_ADDR) == I2C_SR1_ADDR)
        i2c1_config.P_ADDR_CallBack(&i2c1_config);
    else if((I2C1->I2C_SR1 & I2C_SR1_ADD10) == I2C_SR1_ADD10)
        i2c1_config.P_ADDR10_CallBack(&i2c1_config);
    else if((I2C1->I2C_SR1 & I2C_SR1_STOPF) == I2C_SR1_STOPF)
        i2c1_config.P_STOPF_CallBack(&i2c1_config);
    else if((I2C1->I2C_SR1 & I2C_SR1_BTF) == I2C_SR1_BTF)
        i2c1_config.P_BTF_CallBack(&i2c1_config);
    if((I2C1->I2C_CR2 & I2C_CR2_ITBUFEN) == I2C_CR2_ITBUFEN)
    {
        if((I2C1->I2C_SR1 & I2C_SR1_TXE) == I2C_SR1_TXE)
            i2c1_config.P_TXE_CallBack(&i2c1_config);
        else if((I2C1->I2C_SR1 & I2C_SR1_RXNE) == I2C_SR1_RXNE)
            i2c1_config.P_RXNE_CallBack(&i2c1_config);
    }
    
}   


/**
 * @brief This function handles I2C1 Error global interrupt. 
 */
void I2C1_ER_Handler(void)
{

}


/**
 * @brief This function handles I2C2 Event global interrupt.
 */
void I2C2_EV_Handler(void)
{
    if((I2C2->I2C_SR1 & I2C_SR1_SB) == I2C_SR1_SB)
        i2c2_config.P_SB_CallBack(&i2c2_config);
    else if((I2C2->I2C_SR1 & I2C_SR1_ADDR) == I2C_SR1_ADDR)
        i2c2_config.P_ADDR_CallBack(&i2c2_config);
    else if((I2C2->I2C_SR1 & I2C_SR1_ADD10) == I2C_SR1_ADD10)
        i2c2_config.P_ADDR10_CallBack(&i2c2_config);
    else if((I2C2->I2C_SR1 & I2C_SR1_STOPF) == I2C_SR1_STOPF)
        i2c2_config.P_STOPF_CallBack(&i2c2_config);
    else if((I2C2->I2C_SR1 & I2C_SR1_BTF) == I2C_SR1_BTF)
        i2c2_config.P_BTF_CallBack(&i2c2_config);
    if((I2C2->I2C_CR2 & I2C_CR2_ITBUFEN) == I2C_CR2_ITBUFEN)
    {
        if((I2C2->I2C_SR1 & I2C_SR1_TXE) == I2C_SR1_TXE)
            i2c2_config.P_TXE_CallBack(&i2c2_config);
        else if((I2C2->I2C_SR1 & I2C_SR1_RXNE) == I2C_SR1_RXNE)
            i2c2_config.P_RXNE_CallBack(&i2c2_config);
    }
    
}


/**
 * @brief This function handles I2C1 Error global interrupt.
 */
void I2C2_ER_Handler(void)
{

}





//==============================================================================


//________________________ Local Functions Definition __________________________
/**
 * @brief Is Used to config Pins for I2C peripheral
 * @param I2Cx : data Structure for I2C API
 * @return      uint8_t  : 1 = Succesed
 *                         0 = Failed
 */
uint8_t I2C_Clock_Config_Pins(St_I2C_API *I2Cx)
{
    GPIO_InitTypeDef gpio_config = {0};
    gpio_config.Mode = GPIO_MODE_AF_OD;
    gpio_config.Speed = GPIO_SPEED_FREQ_10MHZ;
    if(I2Cx->I2C_Inst == I2C1)
    {   
        __APB1ENR_I2C1EN_EN();
        
        // Config The SCL
        gpio_config.Pin = GPIO_PIN_6;
        Init_GPIO(GPIOB, &gpio_config);
        
        // Config The SDA
        gpio_config.Pin = GPIO_PIN_7;
        Init_GPIO(GPIOB, &gpio_config);
    }else
    {
        __APB1ENR_I2C1EN_EN();

          // Config The SCL
        gpio_config.Pin = GPIO_PIN_10;
        Init_GPIO(GPIOB, &gpio_config);
        
        // Config The SDA
        gpio_config.Pin = GPIO_PIN_11;
        Init_GPIO(GPIOB, &gpio_config);
    }

    return 1;
}
//==============================================================================