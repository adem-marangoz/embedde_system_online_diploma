/**
 * @file Stm32f10xx_Flash.c
 * @author adem alnajjar (adem.marangoz95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Stm32f10xx_Flash.h"
#include "Stm32_f10xx_Systick.h"

//------------------------------- Local Objects --------------------------------

//==============================================================================


//------------------------------- Extern Objects -------------------------------

//==============================================================================


//------------------------------ Global Function -------------------------------


/**
  * @brief  Unlock the FLASH control register access
  * @retval 0 Successful
  *         1 Fail
  */
uint8_t Flash_Unlock(void)
{
    uint8_t ret = 0;
    
    if(READ_BIT(FLASH->CR, FLASH_CR_LOCK) != 0)
    {
        /* Authorize the FLASH Registers access */
        WRITE_REG(FLASH->KEYR, FLASH_KEY1);
        WRITE_REG(FLASH->KEYR, FLASH_KEY2);

        /* Verify Flash is unlocked */
        if(READ_BIT(FLASH->CR, FLASH_CR_LOCK) != 0)
        {
            ret = 1;
        }
    }
    return ret;
}


/**
  * @brief  Locks the FLASH control register access
  * @retval 0 Successful
  *         1 Fail
  */
uint8_t Flash_Lock(void)
{
    /* Set the LOCK Bit to lock the FLASH Registers access */
    FLASH->CR |= FLASH_CR_LOCK;
    return 0;
}


/**
  * @brief  Erase the specified FLASH memory page
  * @param PageAdd FLASH page to erase
  *         The value of this parameter depend on device used within the same series    
  * @retval 0 Successful
  *         1 Fail
  */
uint8_t Flash_Erase_Page(uint32_t PageAdd)
{
    /* Proceed to erase the page */
    SET_BIT(FLASH->CR, FLASH_CR_PER);
    WRITE_REG(FLASH->AR, PageAdd);
    SET_BIT(FLASH->CR, FLASH_CR_STRT);

    return 0;
}


uint8_t Flash_Erase_Pages(uint32_t PageAdd, uint8_t NPage)
{
    volatile uint32_t address = 0;
    for(address = PageAdd; address < ((NPage * Flash_Page_Size) + PageAdd); address += Flash_Page_Size)
    {
        Flash_Erase_Page(address);
        Flash_Wait_Operation((uint32_t)FLASH_TIMEOUT_VALUE);
        CLEAR_BIT(FLASH->CR, FLASH_CR_PER);
    }

    return 0;
}


/**
 * @brief 
 * 
 * @param Address 
 * @param Data 
 * @return uint8_t 
 */
uint8_t Flash_Program_HalfWord(uint32_t Address, uint16_t Data)
{
    Flash_Wait_Operation((uint32_t)FLASH_TIMEOUT_VALUE);
    
    SET_BIT(FLASH->CR, FLASH_CR_PG);
    *(__IO uint16_t*)Address = Data;

    Flash_Wait_Operation((uint32_t)FLASH_TIMEOUT_VALUE);

    CLEAR_BIT(FLASH->CR, FLASH_CR_PG);

    return 0;
}


/**
 * @brief 
 * 
 * @param PageAdd 
 * @param NPage 
 * @return uint8_t 
 */
uint16_t Flash_Program(uint32_t PageAdd, uint8_t Data_len, uint8_t *Data)
{
    uint8_t ret = 0;
    uint16_t ota_fw_received_size = 0;
    for(int i = 2; i < (Data_len + 2)/2; i = i + 2)
    {
        ret = Flash_Program_HalfWord(PageAdd + ota_fw_received_size, Data[2+i]);    
        ota_fw_received_size += 2;
    }
    return 0;
}

/**
  * @brief  Wait for a FLASH operation to complete.
  * @param  Timeout  maximum flash operation timeout
  * @retval 0 Successful
  *         1 Fail
  */
uint8_t Flash_Wait_Operation(uint32_t Timeout)
{
    /* Wait for the Flash operation to complate by polling on Busy Flag to be reset*/
    uint32_t start_tick = Get_Tick();

    while (__Flash_Get_Flag(FLASH_SR_BSY))
    {
        if(Timeout != Max_Delay)
        {
            if((Timeout == 0U) || ((Get_Tick() - start_tick) > Timeout))
            {
                return 1;
            }
        }
    }
    
    return 0;
}


//==============================================================================