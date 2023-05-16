/**
 * @file Stm32f10xx_Common.c
 * @author adem alnajjar (adem.marangoz95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */


//------------------------------- Include Files --------------------------------
#include "Stm32f10xx_Common.h"
//==============================================================================


//------------------------------- Local Objects --------------------------------

//==============================================================================


//------------------------------ Global Functions ------------------------------
uint32_t add_unsigned_int_to_str(char *str, uint32_t num)
{
    uint16_t digits[12] = {0};

    int i = 0;
    while (num != 0)
    {
        digits[i] = num % 10;
        num /= 10;
        i++;
    }

    uint16_t idx = 0;
    for(int j = i - 1; j >= 0; j--){
        str[idx++] = digits[j] + '0';
    }
    str[idx] = 0;
    return idx;

}

void clear_buffer(uint8_t *str, uint16_t start_add, uint16_t end_add, uint8_t ch)
{
    uint16_t i = start_add;
    for(i ; i < end_add; i++)
    {
        *str = ch;
        str++;
    }
}
//==============================================================================