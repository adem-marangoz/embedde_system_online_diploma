/**
 * @file Stm32f10xx_AFIO.h
 * @author Adem marangoz (adem.marangoz95@gmail.com)
 * @brief This Header file for AFIO Regsiter and Declerat function and Macro dircetive
 * @version 0.1
 * @date 2022-05-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef AFIO_H_
#define AFIO_H_

#include "Stm32f10xx_Common.h"


/* AFIO Registers*/
typedef struct 
{
    __IO uint32_t EVCR;
    __IO uint32_t MAPR;
    __IO uint32_t EXTICR[4];
         uint32_t RESERVED0;
    __IO uint32_t MAPR2;
}St_AFIO;


/* AFIO Register start at 0x40010000 address */
#define AFIO                ((St_AFIO *) 0x40010000)

/* Mask 4 Bit For GPIOS Mux to Line */
#define AFIO_Line_Mask      0xFU






#endif