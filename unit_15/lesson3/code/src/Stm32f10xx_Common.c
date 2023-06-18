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

/**
 * @brief 
 * 
 * @param src 
 * @param des 
 * @param len 
 * @return uint8_t 
 */
uint8_t strcmp_(uint8_t *src, uint8_t *des, uint32_t len)
{
    for(uint32_t i = 0; i < len; i++)
    {
        if(src[i] != des[i]){return 1;}
    }
    return 0;
}


// Example : BL_Print_Message("Passed -> Program ROP to Level : 0x%X \r\n", ROP_Level);
void Print_With_Uart(char *format, ...)
{
    char Messsage[100] = {0};
	/* holds the information needed by va_start, va_arg, va_end */
	va_list args;
	/* Enables access to the variable arguments */
	va_start(args, format);
	/* Write formatted data from variable argument list to string */
	vsprintf(Messsage, format, args);

    #if (Print_By_Uart == Enable_Print_By_Uart)
        #if (Use_Hal == Enable_Hal)
            /* Trasmit the formatted data through the defined UART */
            HAL_UART_Transmit(BL_DEBUG_UART, (uint8_t *)Messsage, 
                                sizeof(Messsage), HAL_MAX_DELAY);
        #else
            /* Trasmit the formatted data through the defined UART */

        #endif
    #endif
    /* Performs cleanup for an ap object initialized by a call to va_start */
	va_end(args);
}

//==============================================================================