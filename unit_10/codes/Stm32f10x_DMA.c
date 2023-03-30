/**
 * @file Stm32f10x_DMA.c
 * @author adem alnajjar (adem.marangoz95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

//------------------------------- INCLUDE FILES --------------------------------
#include "Stm32f10x_DMA.h"
#include <stdio.h>

//==============================================================================


//----------------------- External Variables & Functions -----------------------

//==============================================================================


//------------------------------ Local Functions -------------------------------

//==============================================================================


//------------------------------ Global Functions ------------------------------

/**
 * @brief Is used to config DMA
 * @param _DMA_Inst Data Stucture for DMA API
 * @return uint8_t  1 : Successed
 *                  0 : Failed
 */
uint8_t DMA_Init(St_DMA_API *_DMA_Inst)
{
    // Clear DMA channel Flags
    _DMA_Inst->DMA_Inst->DMA_IFCR &= ~(0xFU << _DMA_Inst->channel);

    /*
        configure The Mem2Mem , priority, Memory_data_size, Peri_data_size,
        Memory_inc, Peri_inc, Circular_mode, Data_direction and Interrupt
    */ 
    uint32_t temp = (_DMA_Inst->MEM2MEM << DMA_CCR_MEM2MEM_Pos) || 
                    (_DMA_Inst->Priority << DMA_CCR_PL_Pos) ||
                    (_DMA_Inst->MEM_Data_Size << DMA_CCR_MSIZE_Pos) ||
                    (_DMA_Inst->Peri_Data_Size << DMA_CCR_PINC) ||
                    (_DMA_Inst->Memory_Inc << DMA_CCR_MINC_Pos) ||
                    (_DMA_Inst->Peripheral_Inc << DMA_CCR_PINC_Pos) ||
                    (_DMA_Inst->Circular_mode << DMA_CCR_CIRC_Pos) ||
                    (_DMA_Inst->Data_Dir << DMA_CCR_DIR_Pos) ||
                    (_DMA_Inst->Interrupt << DMA_CCR_TCIE);
    _DMA_Inst->DMA_Inst->DMA_channel_reg[_DMA_Inst->channel].DMA_CCR = temp;

    return 1; 
}


/**
 * @brief used to Reinit DMA channel
 * @param _DMA_Inst Data Stucture for DMA API
 * @return uint8_t  1 : Successed
 *                  0 : Failed
 */ 
 */
uint8_t DMA_ReInit(St_DMA_API *_DMA_Inst)
{
    // Clear DMA channel Flags
    _DMA_Inst->DMA_Inst->DMA_IFCR &= ~(0xFU << _DMA_Inst->channel);

    /*
        reset The Mem2Mem , priority, Memory_data_size, Peri_data_size,
        Memory_inc, Peri_inc, Circular_mode, Data_direction and Interrupt
    */ 
    _DMA_Inst->DMA_Inst->DMA_channel_reg[_DMA_Inst->channel].DMA_CCR &= (uint32_t)0xFFFF;

    return 1; 
}

/**
 * @brief 
 * @param _DMA_Inst Data Stucture for DMA API
 * @param Num_data Number of data transamination
 * @return uint8_t  1 : Successed
 *                  0 : Failed
 */
uint8_t DMA_Set_Number_of_Data(St_DMA_API *_DMA_Inst, uint32_t Num_data)
{
    if(Num_data == 0) return 0;
    if(_DMA_Inst->DMA_Inst->DMA_channel_reg[_DMA_Inst->channel].DMA_CPAR == 0) return 0;
    if(_DMA_Inst->DMA_Inst->DMA_channel_reg[_DMA_Inst->channel].DMA_CMAR == 0) return 0;
    _DMA_Inst->DMA_Inst->DMA_channel_reg[_DMA_Inst->channel].DMA_CNDTR = Num_data;

    return 1;
}


/**
 * @brief 
 * @param _DMA_Inst Data Stucture for DMA API
 * @param Peri_Add Peripheral Address
 * @return uint8_t  1 : Successed
 *                  0 : Failed 
 */
uint8_t DMA_Set_Peripheral_Add(St_DMA_API *_DMA_Inst, uint32_t Peri_Add)
{
    _DMA_Inst->DMA_Inst->DMA_channel_reg[_DMA_Inst->channel].DMA_CPAR = Peri_Add;

    return 1;
}


/**
 * @brief 
 * @param _DMA_Inst Data Stucture for DMA API
 * @param Mem_Add Memory Address
 * @return uint8_t  1 : Successed
 *                  0 : Failed 
 */
uint8_t DMA_Set_Memory_Add(St_DMA_API *_DMA_Inst, uint32_t Mem_Add)
{
    _DMA_Inst->DMA_Inst->DMA_channel_reg[_DMA_Inst->channel].DMA_CMAR = Mem_Add;

    return 1;
}


/**
 * @brief Enable DMA Channel
 * @param _DMA_Inst Data Stucture for DMA API
 * @return uint8_t  1 : Successed
 *                  0 : Failed 
 */
uint8_t DMA_Enable_Channel(St_DMA_API *_DMA_Inst)
{
    _DMA_Inst->DMA_Inst->DMA_channel_reg[_DMA_Inst->channel].DMA_CCR |= (uint32_t)DMA_ENABLE;

    return 1;
}


/**
 * @brief Disable DMA Channle
 * @param _DMA_Inst Data Stucture for DMA API
 * @return uint8_t  1 : Successed
 *                  0 : Failed 
 */
uint8_t DMA_Disable_Channel(St_DMA_API *_DMA_Inst)
{
     _DMA_Inst->DMA_Inst->DMA_channel_reg[_DMA_Inst->channel].DMA_CCR &= ~(uint32_t)DMA_ENABLE;

     return 1;
}


/**
 * @brief Trigger DMA transfer by Software 
 * @param _DMA_Inst Data Stucture for DMA API
 * @return uint8_t  1 : Successed
 *                  0 : Failed 
 */
uint8_t DMA_Soft_Trigger(St_DMA_API *_DMA_Inst)
{

}
//==============================================================================