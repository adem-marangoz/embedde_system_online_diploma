/**
 * @file Stm32f10x_DMA.h
 * @author adem alnajjar (adem.marangoz95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef STM32F10XX_DMA_H
#define STM32F10XX_DMA_H

//------------------------------- INCLUDE FILES --------------------------------
#include "Stm32f10xx_Address.h"
#include "Stm32f10xx_Common.h"
#include "BitField_DMA.h"
//==============================================================================


//------------------------------ GENERAIC OBJECTS ------------------------------

/*** @ref DMA_MEM2MEM_EN_define */
#define DMA_MEM2MEM_DIS                         0  
#define DMA_MEM2MEM_EN                          1

/*** @ref DMA_CHANNEL_PRIORITY_define*/
#define DMA_CHANNEL_PRIORITY_LOW                0
#define DMA_CHANNEL_PRIORITY_MEDIUM             1
#define DMA_CHANNEL_PRIORITY_HIGH               2
#define DMA_CHANNEL_PRIORITY_VERYHIGH           3

/*** @ref DMA_DATA_SIZE_define*/
#define DMA_DATA_SIZE_8                         0
#define DMA_DATA_SIZE_16                        1
#define DMA_DATA_SIZE_32                        2

/*** @ref DMA_ADDRESS_INC_define*/
#define DMA_INC_DIS                             0
#define DMA_INC_EN                              1

/*** @ref DMA_CIRCULAR_MODE_define*/
#define DMA_CIRCULAR_MODE_DIS                   0
#define DMA_CIRCULAR_MODE_EN                    1

/*** @ref DMA_DATA_DIR_define*/
#define DMA_PERI_TO_MEMORY                      0
#define DMA_MEMORY_TO_PERI                      1

/*** @ref DMA_INTERRUPT_define*/
#define DMA_ERROR_INT_DIS                       0
#define DMA_ERROR_INT_EN                        4
#define DMA_HALF_INT_DIS                        0
#define DMA_HALF_INT_EN                         2
#define DMA_COMPLETE_INT_DIS                    0
#define DMA_COMPLETE_INT_EN                     1

/*** @ref DMA_ENABLE_define*/
#define DMA_DISALBE                             0
#define DMA_ENABLE                              1

/*** @ref DMA_CHANNEL_define*/
#define DMA_CHANNEL_1                           0
#define DMA_CHANNEL_2                           1
#define DMA_CHANNEL_3                           2
#define DMA_CHANNEL_4                           3
#define DMA_CHANNEL_5                           4
#define DMA_CHANNEL_6                           5
#define DMA_CHANNEL_7                           6



//==============================================================================

//------------------------------- DATA STRUCTURE -------------------------------
typedef struct 
{
    St_DMA_Typedef *DMA_Inst;                   // Specifies the DMA Peripheral
                                                // This parameter must be set base on @ref DMA_Peripheral_define
    uint8_t channel;                            // This parameter for select DMA channel 
                                                // This parameter must be set base on @ref DMA_CHANNEL_define
    uint8_t MEM2MEM;                            // This parameter configures the dma memory to memory        
                                                // This parameter must be set base on @ref DMA_MEM2MEM_EN_define
    uint8_t Priority;                           // This parameter configures the dma channel priority
                                                // This parameter must be set base on @ref DMA_CHANNEL_PRIORITY_define
    uint8_t Peri_Data_Size;                     // This parameter confiugre the peripheral data size
                                                // This parameter must be set base on @ref DMA_DATA_SIZE_define 
    uint8_t MEM_Data_Size;                      // This parameter confiugre the memory data size
                                                // This parameter must be set base on @ref DMA_DATA_SIZE_define 
    uint8_t Peripheral_Inc;                     // This parameter configure the Peripheral address increment
                                                // This parameter must be set base on @ref DMA_ADDRESS_INC_define
    uint8_t Memory_Inc;                         // This parameter configure the memeory address increment
                                                // This parameter must be set base on @ref DMA_ADDRESS_INC_define
    uint8_t Circular_mode;                      // This parameter configure the ciruclar mode
                                                // This parameter must be set base on @ref DMA_CIRCULAR_MODE_define
    uint8_t Data_Dir;                           // This parameter configure the data direction
                                                // This parameter must be set base on @ref DMA_DATA_DIR_define
    uint8_t Interrupt;                          // This parameter confiugre the DMA interrupt
                                                // This parameter must be set base on @ref DMA_INTERRUPT_define
}St_DMA_API;

//==============================================================================

//------------------------------ GLOBAL FUNCTIONS ------------------------------
uint8_t DMA_Init(St_DMA_API *_DMA_Inst);
uint8_t DMA_ReInit(St_DMA_API *_DMA_Inst);
uint8_t DMA_Set_Peripheral_Add(St_DMA_API *_DMA_Inst, uint32_t Peri_Add);
uint8_t DMA_Set_Memory_Add(St_DMA_API *_DMA_Inst, uint32_t Mem_Add);
uint8_t DMA_Set_Number_of_Data(St_DMA_API *_DMA_Inst, uint32_t Num_data);
uint8_t DMA_Enable_Channel(St_DMA_API *_DMA_Inst);
uint8_t DMA_Disable_Channel(St_DMA_API *_DMA_Inst);
uint8_t DMA_Soft_Trigger(St_DMA_API *_DMA_Inst);



//==============================================================================

#endif