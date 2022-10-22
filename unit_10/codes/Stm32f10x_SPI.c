/**
 * @file Stm32f10x_SPI.c
 * @author adem alnajjar (adem.marangoz95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Stm32f10x_SPI.h"
#include "Stm32f10xx_GPIO.h"
#include "Stm32f10xx_RCC.h"
#include <stdio.h>

//_______________________External Variables & Functions ________________________

extern St_SPI_API spi1_config;
extern St_SPI_API spi2_config;
extern St_SPI_API spi3_config;
//==============================================================================

//______________________________ Local Function ________________________________

void Select_SPI_Pins_datasheet(St_SPI_API *SPIx);
void Config_SPI_Pins(St_SPI_API *SPIx, St_GPIO_Typedef *GPIOx, uint16_t CLK, \
                    uint16_t MOSI, uint16_t MISO, uint16_t NSS);

//==============================================================================


/**
 * @brief Is used to Config SPI
 * @param SPIx : Data Structre for SPI API
 * @return uint8_t 1 : Successed
 *                 0 : Failed
 */
uint8_t Init_SPI(St_SPI_API *SPIx)
{
    // Check The SPI Member
    if(!(IS_SPI_ALL_INSTANCE(SPIx->SPI_Inst))){return 0;}
    if(!(IS_SPI_BAURDRATE(SPIx->BaudRate))){return 0;}
    if(!(IS_SPI_MASTER(SPIx->Master_Select))){return 0;}
    if(!(IS_DATA_FORMATE(SPIx->Frame_format))){return 0;}
    if(!(IS_SOFTWARE_MANG(SPIx->Slave_Select_Software))){return 0;}
    if(!(IS_DATA_LENG(SPIx->Data_Legnth_format))){return 0;}
    if(!(IS_CLK_PHASE_POLARIYT(SPIx->CLK_Phase_Polarity))){return 0;}
    if(!(IS_RX_TX_INTERRUPT(SPIx->Rx_Tx_interrupt))){return 0;}
    if(!(IS_HALF_DUPLEX_MODE(SPIx->Half_duplex_Mode))){return 0;}
    if(!(IS_SPI_MODE(SPIx->SPI_Mode))){return 0;}

    // Initially giving base functions addresses values
    if(SPIx->P_Tx_Empty_CallBack == NULL){SPIx->P_Tx_Empty_CallBack = Tx_Empty_CallBack;}
    if(SPIx->P_Rx_Empty_CallBack == NULL){SPIx->P_Rx_Empty_CallBack = RX_Empty_CallBack;}
    if(SPIx->P_Fault_Event_CallBack == NULL){SPIx->P_Fault_Event_CallBack = Fault_Event_CallBack;}
    if(SPIx->P_Overrun_CallBack == NULL){SPIx->P_Overrun_CallBack = Overrun_CallBack;}
    if(SPIx->P_CRC_CallBack == NULL){SPIx->P_CRC_CallBack = CRC_CallBack;} 

    // Config SPI pins
    Select_SPI_Pins_datasheet(SPIx);

    uint16_t SPI_CR1_temp = 0;
    // SPI mode full/half simplex
    SPIx->SPI_Inst->SPI_CR1 |= SPIx->SPI_Mode;

    // SPI BuadRate , Mastre/Slave , MSB/LSB , 8/16 bit, CLK polarity_phase , software slave,
    SPI_CR1_temp = (SPIx->BaudRate << BR) | (SPIx->CLK_Phase_Polarity << CPHA) | (SPIx->Data_Legnth_format << DFF) | (SPIx->Frame_format << LSB_FIRST) | (SPIx->Master_Select << MSTR) | (SPIx->Slave_Select_Software << SSM);
    SPIx->SPI_Inst->SPI_CR1 |= SPI_CR1_temp; 



    if(SPIx->Slave_Select_Software == Software_Mang_Disable)
    {
        // Config MultiMaster
        SPIx->SPI_Inst->SPI_CR2 |= SPIx->NSS_Hardware_Mode;
    }    


    // When slave Mode SSM = 0 (software mang is disable)
    //the NSS pin must be connected to a low level signal during the complete byte transmit sequence
    
    //when Slave Mode SSM = 1 (software mang is Enable)
    //software mode, set the SSM bit and clear the SSI bit

    // when master mode SSM = 0 (software mang is disable) and SSOE = 0 (Output is Enable)
    // The NSS signal is driven low when the master starts the communication and is kept low until the SPI is disabled

    // When master Mode SSM = 0 (software mang is disable) and SSOE = 1 (Output is Disnable)
    // For devices set as slave, the NSS pin acts as classical NSS input: the slave is sleceted when NSS is low and deselected when NSS high
    if(SPIx->Master_Select == SPI_Master)
    {
        if(SPIx->Slave_Select_Software == Software_Mang_Disable)
        {
            // Config NSS Hardware mode
            SPIx->SPI_Inst->SPI_CR2 |= SPIx->NSS_Hardware_Mode;
        }
    }

    // In bidirectional mode, when transmitting (BIDIMODE=1 and BIDIOE=1)
    /*
        – The sequence begins when data are written into the SPI_DR register (Tx buffer).
        – The data are then parallel loaded from the Tx buffer into the 8-bit shift register
        during the first bit transmission and then shifted out serially to the MOSI pin.
        – No data are received.
    */

   // In bidirectional mode, when receiving (BIDIMODE=1 and BIDIOE=0)
   /*
        – The sequence begins as soon as SPE=1 and BIDIOE=0.
        – The received data on the MOSI pin are shifted in serially to the 8-bit shift register
        and then parallel loaded into the SPI_DR register (Rx buffer).
        – The transmitter is not activated and no data are shifted out serially to the MOSI pin.
   */


    // SPI RX/Tx interrupt
    if(SPIx->Rx_Tx_interrupt != SPI_interrupt_Dis)
    {
        // Check which Rx/Tx interrupt active
        SPIx->SPI_Inst->SPI_CR2 |= SPIx->Rx_Tx_interrupt << RXNEIE;

        // Active NVIC SPI interrupt
        if(SPIx->SPI_Inst == SPI1){NVIC_EnableIRQ(SPI1_IRQn);}
        else if (SPIx->SPI_Inst == SPI2){NVIC_EnableIRQ(SPI2_IRQn);}
    }


    // Active SPI
    SPIx->SPI_Inst->SPI_CR1 |= 1 << SPE;
}


/**
 * @brief Is used to Reset SPI Peripheral and API
 * @param SPIx : Data Structre for SPI API
 */
void Deinit_SPI(St_SPI_API *SPIx)
{

    // Wait to until the BSY flag to be cleard
    while(SPIx->SPI_Inst->SPI_SR & 1 << BSY);

    if(SPIx->SPI_Inst == SPI1)
    {
        // Reset SPI1 and Disable SPI1_IRQ
        __APB2RSTR_SPI1RST();
        NVIC_DisableIRQ(SPI1_IRQn);
    }else if(SPIx->SPI_Inst == SPI2)
    {
        // Reset SPI2 and Disable SPI2_IRQ
        __APB1RSTR_SPI2RST();
        NVIC_DisableIRQ(SPI2_IRQn);
    }else
    {
        // Reset SPI3 and Disable SPI3_IRQ
        __APB1ENR_SPI3EN_EN();
    }

    // Reset pointer to SPI peripheral
    SPIx->SPI_Inst = NULL;
}


/**
 * @brief Is Used to Send Data To Slave through SPI
 * @param SPIx : Data Structre for SPI API
 * @param Tx_buffer  : Tx buffer of Sending data through SPI form Master
 * @param polling  : Is Used to check Flag control by interrupt or polling
 * @return uint16_t : Sent data
 */
uint16_t SPI_Send_Char(St_SPI_API *SPIx,uint16_t *Tx_buffer ,enum En_SPI_polling polling)
{
    // (Master) First check TXE must be 1 & BSY must be 0
    
    // check if polling if enable & Wait until to set TXE 
    if(polling == SPI_Pol_Enable)
        while(!(SPIx->SPI_Inst->SPI_SR & (1 << TXE)));

    // Write The Data to SPI Data register
    SPIx->SPI_Inst->SPI_DR = *Tx_buffer;
    

    return *Tx_buffer;
}


/**
 * @brief Is used to Receive Data throgh SPI form Slave
 * @param SPIx : Data Structre for SPI API
 * @param Rx_buffer : The buffer address that will read the received data
 * @param polling : Is Used to check Flag control by interrupt or polling
 * @return uint16_t Received Data
 */
uint16_t SPI_Receive_Char(St_SPI_API *SPIx, uint16_t *Rx_buffer,enum En_SPI_polling polling)
{
    // (Master) Check BSY must be 1 & wait until RXNE to 1
    // (Slave) when received Data BSY cleard & RNXE is 1
    // Simplex and halfduplex Receive only not need look to BSY 

    // check if polling if enable & Wait until to set TXE 
    if(polling == SPI_Pol_Enable)
        while(!(SPIx->SPI_Inst->SPI_SR & (1 << RXNE)));
    
    // Receive The Data form SPI Data Register
    *Rx_buffer = SPIx->SPI_Inst->SPI_DR;

    return *Rx_buffer;

}


/**
 * @brief Is Used to Send string through SPI to Slave
 * @param SPIx : Data Structre for SPI API
 * @param Tx_buffer  : Tx buffer of Sending data through SPI form Master
 * @param len : Length of Sending Data to Slave through SPI 
 * @param polling  : Is Used to check Flag control by interrupt or polling
 * @return uint16_t* : The send Tx buffer address
 */
uint16_t * SPI_Send_String(St_SPI_API *SPIx , uint16_t *Tx_buffer ,uint8_t len, enum En_SPI_polling polling)
{
    static uint8_t counter = 0;
    while(counter != len)
    {
        SPI_Send_Char(SPIx,Tx_buffer,polling);
        Tx_buffer++;
        counter++;
    }
    counter = 0;
    while (! ( SPIx->SPI_Inst->SPI_SR & (1 << BSY)));
    
    return Tx_buffer;
}


/**
 * @brief Is used to Receive String through SPI form Slave
 * @param SPIx : Data Structre for SPI API
 * @param Rx_buffer : Rx buffer of Receive Data through SPI form Slave
 * @param len : Length of receiving Data to Slave through SPI 
 * @param polling  : Is Used to check Flag control by interrupt or polling
 * @return uint16_t* : The Receive Rx buffer address
 */
uint16_t * SPI_Receive_String(St_SPI_API *SPIx , uint16_t *Rx_buffer, uint8_t len , enum En_SPI_polling polling)
{
    static uint8_t counter = 0;
    while(counter != len)
    {
        SPI_Send_Char(SPIx,Rx_buffer,polling);
        Rx_buffer++;
        counter++;
    }
    counter = 0;
    while (! ( SPIx->SPI_Inst->SPI_SR & (1 << BSY)));
    
}


/**
 * @brief Tx Buffer Empty interrupt defualt Callback
 * @param SPIx : Data Structre for SPI API
 * @return None 
 */
__weak void Tx_Empty_CallBack(St_SPI_API *SPIx)
{
    UNUSED(SPIx);
}


/**
 * @brief Rx Buffer is Received Data interrupt defualt Callback
 * @param SPIx : Data Structre for SPI API
 * @return None 
 */
__weak void RX_Empty_CallBack(St_SPI_API *SPIx)
{
    UNUSED(SPIx);
}


/**
 * @brief Fault Event interrupt defualt Callback
 * @param SPIx : Data Structre for SPI API
 * @return None 
 */
__weak void Fault_Event_CallBack(St_SPI_API *SPIx)
{
    UNUSED(SPIx);
}


/**
 * @brief Over run interrupt defualt Callback
 * @param SPIx : Data Structre for SPI API
 * @return None 
 */
__weak void Overrun_CallBack(St_SPI_API *SPIx)
{
    UNUSED(SPIx);
}


/**
 * @brief CRC interrupt defualt Callback
 * @param SPIx : Data Structre for SPI API
 * @return None 
 */
__weak void CRC_CallBack(St_SPI_API *SPIx)
{
    UNUSED(SPIx);
}


/**
 * @brief Is used to send Pins to Config_SPI_Pins function base on SPIx for config for SPI
 * @param SPIx : Data Structre for SPI API
 */
void Select_SPI_Pins_datasheet(St_SPI_API *SPIx)
{
    if(SPIx->SPI_Inst == SPI1)
    {
        __APB2ENR_SPI1EN_En();
        Config_SPI_Pins(SPIx, GPIOA,GPIO_PIN_5, GPIO_PIN_7, GPIO_PIN_6, GPIO_PIN_4);
    }
    else if(SPIx->SPI_Inst == SPI3)
    {
        __APB1ENR_SPI2EN_EN();
        Config_SPI_Pins(SPIx, GPIOB,GPIO_PIN_3, GPIO_PIN_5, GPIO_PIN_4, GPIO_PIN_15);
    }else
    {
        __APB1ENR_SPI3EN_EN();
        Config_SPI_Pins(SPIx, GPIOB,GPIO_PIN_5, GPIO_PIN_7, GPIO_PIN_6, GPIO_PIN_4);
    }
}


/**
 * @brief Is used to config CLK, MOSI ,MISO and NSS base on user input
  * @param SPIx : Data Structre for SPI API
 * @param GPIOx : which config Pins Port base on SPIx
 * @param CLK  : CLK pin base on SPIx
 * @param MOSI : MOSI pin base on SPIx
 * @param MISO  : MISO pin base on SPIx
 * @param NSS  : NSS pin base on SPIx
 */
void Config_SPI_Pins(St_SPI_API *SPIx, St_GPIO_Typedef *GPIOx, uint16_t CLK, uint16_t MOSI, uint16_t MISO, uint16_t NSS)
{
    GPIO_InitTypeDef gpio_config = {0};
    // Config Pin mode base on Master or Slave
    if(SPIx->Master_Select == SPI_Master)
    {
        // config CLK pin
        gpio_config.Mode =  GPIO_MODE_AF_PP;
        gpio_config.Speed = GPIO_SPEED_FREQ_10MHZ;
        gpio_config.Pin = CLK;
        Init_GPIO(GPIOx, &gpio_config);

        // Config The MOSI
        gpio_config.Pin = MOSI;
        Init_GPIO(GPIOx, &gpio_config);
        
        // Check if SPI mode is Not Simplex
        // Because this pin can used as a GPIO
        if(SPIx->SPI_Mode != Simplex_Only_Rx)
        {
            // Config The MSIO
            gpio_config.Mode = GPIO_MODE_AF_INPUT;
            gpio_config.Speed = GPIO_SPEED_INPUT_Mode;
            gpio_config.Pin = MISO;
            Init_GPIO(GPIOx, &gpio_config);
        }
        
        // Check if Software Manangement is Disable
        if(SPIx->Slave_Select_Software == Software_Mang_Disable)
        {
            // Check if Have system multiMaster
            if(SPIx->NSS_Hardware_Mode == NSS_Hardware_Output_Dis_MultiMaster_En)
            {
                // config NSS if one master on system
                gpio_config.Mode =  GPIO_MODE_AF_PP;
                gpio_config.Speed = GPIO_SPEED_FREQ_10MHZ;
            }else
            {   
                // config NSS if MultiMaster on system
                gpio_config.Mode =  GPIO_MODE_AF_INPUT;
                gpio_config.Speed = GPIO_SPEED_INPUT_Mode;
            }
            gpio_config.Pin = NSS;
            Init_GPIO(GPIOx, &gpio_config);
        }else
        {
            // when Enable software management and set the SSI for driven the NSS by normal GPIO pin
            SPIx->SPI_Inst->SPI_CR1 |= 1 << SSI;
        }
        

    }else
    {
        // config CLK pin
        gpio_config.Mode =  GPIO_MODE_AF_INPUT;
        gpio_config.Speed = GPIO_SPEED_INPUT_Mode;
        gpio_config.Pin = CLK;
        Init_GPIO(GPIOx, &gpio_config);

        // Check if SPi mode is not Simplex
        // Becuase if mode is simplex can use MODI as a GPIO
        if((SPIx->SPI_Mode != Simplex_Only_Tx) || (SPIx->SPI_Mode != Simplex_Only_Rx))
        {
            // Config The MOSI
            gpio_config.Pin = MOSI;
            Init_GPIO(GPIOx, &gpio_config);
        }

        // Chekc if slave management
        if(SPIx->Slave_Select_Software == Software_Mang_Enable)
        {
            // Config The MSIO
            gpio_config.Mode = GPIO_MODE_AF_OD;
        }else
        {
            // Config The MSIO
            gpio_config.Mode = GPIO_MODE_AF_PP;
        }
        gpio_config.Pin = MISO;
        Init_GPIO(GPIOx, &gpio_config);

        
        // Check if Software Manangement is Disable
        if(SPIx->Slave_Select_Software == Software_Mang_Disable)
        {

            // config NSS if MultiMaster on system
            gpio_config.Mode =  GPIO_MODE_AF_INPUT;
            gpio_config.Speed = GPIO_SPEED_INPUT_Mode;
            gpio_config.Pin = NSS;
            Init_GPIO(GPIOx, &gpio_config);
        }else
        {
            SPIx->SPI_Inst->SPI_CR1 |= 1 << SSI;
        }

    }
}


/**
* @brief SPI2 Handling IRQ requist 
 */
void SPI1_Handler(void)
{
    if((SPI1->SPI_SR & 1 << TXE) == 1 << TXE)
        spi1_config.P_Tx_Empty_CallBack(&spi1_config);   //  jump to defualt Tx_Empty_CallBack function
    else if((SPI1->SPI_SR & 1 << RXNE) == 1 << RXNE)
        spi1_config.P_Rx_Empty_CallBack(&spi1_config);  //  jump to defualt Rx_Empty_CallBack function
    else if((SPI1->SPI_SR & 1 << MODF) == 1 << MODF)
        spi1_config.P_Fault_Event_CallBack(&spi1_config);      //  jump to defualt Fault_Event_CallBack function
    else if((SPI1->SPI_SR & 1 << OVR) == 1 << OVR)
        spi1_config.P_Overrun_CallBack(&spi1_config);  //  jump to defualt Overrun_CallBack function
    else if((SPI1->SPI_SR & 1 << CRC_ERR) == 1 << CRC_ERR)
        spi1_config.P_CRC_CallBack(&spi1_config);      //  jump to defualt CRC_CallBack function
    
}


/**
 * @brief SPI2 Handling IRQ requist
 */
void SPI2_Handler(void)
{
    if((SPI2->SPI_SR & 1 << TXE) == 1 << TXE)
        spi2_config.P_Tx_Empty_CallBack(&spi1_config);   //  jump to defualt Tx_Empty_CallBack function
    else if((SPI2->SPI_SR & 1 << RXNE) == 1 << RXNE)
        spi2_config.P_Rx_Empty_CallBack(&spi1_config);  //  jump to defualt Rx_Empty_CallBack function
    else if((SPI2->SPI_SR & 1 << MODF) == 1 << MODF)
        spi2_config.P_Fault_Event_CallBack(&spi1_config);      //  jump to defualt Fault_Event_CallBack function
    else if((SPI2->SPI_SR & 1 << OVR) == 1 << OVR)
        spi2_config.P_Overrun_CallBack(&spi1_config);  //  jump to defualt Overrun_CallBack function
    else if((SPI2->SPI_SR & 1 << CRC_ERR) == 1 << CRC_ERR)
        spi2_config.P_CRC_CallBack(&spi1_config);      //  jump to defualt CRC_CallBack function
}


/**
 * @brief Is used to send and receive data through SPI
* @param SPIx : Data Structre for SPI API
 * @param Rx_buffer : Rx buffer of Receive Data through SPI form Slave
 * @param Tx_buffer  : Tx buffer of Sending data through SPI form Master
 * @param polling  : Is Used to check Flag control by interrupt or polling
 * @return uint16_t* : The Receive Rx buffer address
 */
uint16_t * SPI_Tx_Rx_Char(St_SPI_API *SPIx , uint16_t *Rx_buffer, uint16_t *Tx_buffer, enum En_SPI_polling polling)
{
    // check if polling if enable & Wait until to set TXE 
    if(polling == SPI_Pol_Enable)
        while(!(SPIx->SPI_Inst->SPI_SR & (1 << TXE)));

    // Write The Data to SPI Data register
    SPIx->SPI_Inst->SPI_DR = *Tx_buffer;

        // check if polling if enable & Wait until to set TXE 
    if(polling == SPI_Pol_Enable)
        while(!(SPIx->SPI_Inst->SPI_SR & (1 << RXNE)));
    
    // Receive The Data form SPI Data Register
    *Rx_buffer = SPIx->SPI_Inst->SPI_DR;

    return Tx_buffer;
}