/**
 * @file defines.h
 * @author adem alnajjar (adem.alnajjar95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef DEFINES_H_
#define DEFINES_H_

//------------------------------- INCLUDE FILES --------------------------------
#include "Stm32f10xx_GPIO.h"
//==============================================================================


//------------------------------ LCD PORT & PINS -------------------------------

    //---------------------------------- DATA ----------------------------------
    #define DATA_PORT           GPIOA
    #define DATA_PINS           GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15
    //-------------------------------- CONTROL ---------------------------------
    #define ENABLE_PROT         GPIOB
    #define ENABLE_PIN          GPIO_PIN_0
    #define RW_PORT             GPIOB
    #define RW_PIN              GPIO_PIN_1
    #define RS_PORT             GPIOB
    #define RS_PIN              GPIO_PIN_3

//==============================================================================


//---------------------------- 7Segment PORT & PINS ----------------------------
    #define SEGMENT_PORT        GPIOA
    #define SEGMENT_PINS        GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_11 | GPIO_PIN_12
//==============================================================================


//----------------------------- keyPad PORT & PINS -----------------------------

    //------------------------------ Drain Output ------------------------------
    #define KEYPAD_DRAIN_PORT   GPIOA
    #define KEYPAD_DRAIN_PINS   GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4
    //------------------------------ Source Input ------------------------------
    #define KEYPAD_SOURCE_PORT  GPIOB
    #define KEYPAD_SOURCE_PINS  GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7

//==============================================================================


//------------------------------ Leds PORT & PINS ------------------------------

    //------------------------------- Green LED --------------------------------
    #define GREAN_LED_PORT      GPIOA
    #define GREAN_LED_PIN       GPIO_PIN_8
    //-------------------------------- Red LED ---------------------------------
    #define RED_LED_PORT        GPIOA
    #define RED_LED_PIN         GPIO_PIN_11


//==============================================================================


//----------------------------- UART1 PORT & PINS ------------------------------

    //---------------------------------- Rx1 -----------------------------------
    #define UART1_RX_PORT       GPIOA
    #define UART1_RX_PIN        GPIO_PIN_10
    //---------------------------------- Tx1 -----------------------------------
    #define UART1_TX_PORT       GPIOA
    #define UART1_TX_PIN        GPIO_PIN_9

//==============================================================================


//----------------------------- UART2 PORT & PINS ------------------------------

    //---------------------------------- Rx2 -----------------------------------
    #define UART2_RX_PORT       GPIOA
    #define UART2_RX_PIN        GPIO_PIN_3
    //---------------------------------- Tx2 -----------------------------------
    #define UART2_TX_PORT       GPIOA
    #define UART2_TX_PIN        GPIO_PIN_2
//==============================================================================


//------------------------------ SPI1 PORT & PINS ------------------------------

    //---------------------------------- SCK -----------------------------------
    #define SPI1_SCK_PORT       GPIOA
    #define SPI1_SCK_PIN        GPIO_PIN_5
    //---------------------------------- MISO ----------------------------------
    #define SPI1_MISO_PORT      GPIOA
    #define SPI1_MISO_PIN       GPIO_PIN_6
    //---------------------------------- MOSI ----------------------------------
    #define SPI1_MOSI_PORT      GPIOA
    #define SPI1_MOSI_PIN       GPIO_PIN_7
    //---------------------------------- NSS1 ----------------------------------
    #define SPI1_NSS1_PORT      GPIOB
    #define SPI1_NSS1_PIN       GPIO_PIN_8
    //---------------------------------- NSS2 ----------------------------------
    #define SPI1_NSS1_PORT      GPIOB
    #define SPI1_NSS1_PIN       GPIO_PIN_9
    //---------------------------------- NSS3 ----------------------------------
    #define SPI1_NSS1_PORT      GPIOB
    #define SPI1_NSS1_PIN       GPIO_PIN_10

//==============================================================================




#endif