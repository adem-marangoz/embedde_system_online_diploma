/**
 * @file GPIO.h
 * @author adem mararngoz (adem.marangoz95@gmail.com)
 * @brief This file contains all the definitions by which the input and
 *        output of the pin can be controlled
 * @version 0.1
 * @date 2022-05-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <Common.h>
#include <avr/io.h>
/* Pin Modes*/
typedef enum
{
    INPUT               = 0x00,
    OUTPUT              = 0x01,
    Low_Level_Ex_Int    = 0x80,
    Any_Ch_Ex_Int       = 0x81,
    Falling_Ed_Ex_Int   = 0x82,
    Rising_Ed_Ex_Int    = 0x83
}En_Pin_config;

/*Pin configed as Input Pull-up resistor mode */
typedef enum
{
    Tri_State,
    Pull_low,
}En_PUD;

/* General GPIOs data structure base datesheet */
typedef struct 
{
    volatile unsigned char Pin0 : 1;
    volatile unsigned char Pin1 : 1;
    volatile unsigned char Pin2 : 1;
    volatile unsigned char Pin3 : 1;
    volatile unsigned char Pin4 : 1;
    volatile unsigned char Pin5 : 1;
    volatile unsigned char Pin6 : 1;
    volatile unsigned char Pin7 : 1;
}St_GPIO_Pins;

typedef struct 
{
    union 
    {
        volatile unsigned char PINx;
        St_GPIO_Pins PINx_bit;
    }Un_PINx;
    
    union 
    {
        volatile unsigned char DDRx;
        St_GPIO_Pins DDRx_bit;
    }Un_DDRx;

    union 
    {
        volatile unsigned char PORTx;
        St_GPIO_Pins PORTx_bit;
    }Un_PORTx;
}St_GPIO;

/* API for GPIO for more easier*/
typedef struct
{
    unsigned char pin;
    En_Pin_config mode;
    En_PUD PUPD;
}GPIO_config;

/* Pin State*/
typedef enum
{
    Low = 0x00,
    High = 0x01,
}St_Pin_State;

/*PORTS start Address*/
#define PORT_A                  ((volatile St_GPIO*)0x39)
#define PORT_B                  ((volatile St_GPIO*)0x36)
#define PORT_C                  ((volatile St_GPIO*)0x33)
#define PORT_D                  ((volatile St_GPIO*)0x30)


#define GPIO_Number             (0x08)
#define PIN_0                   (0x01)
#define PIN_1                   (0x02)
#define PIN_2                   (0x04)
#define PIN_3                   (0x08)
#define PIN_4                   (0x10)
#define PIN_5                   (0x20)
#define PIN_6                   (0x40)
#define PIN_7                   (0x80)


/* Check GPIO if Not exist */
#define Check_PORT(PORT_t)      (((PORT_t) == PORT_A)   ||\
                                ((PORT_t) == PORT_B)    ||\
                                ((PORT_t) == PORT_C)    ||\
                                ((PORT_t) == PORT_D))


/**
 * @brief This function is used to configure pins
 * @param GPIO 
 * @param GPIO_config_t 
 * @return 1: no problem
 *         0: exist problem in program 
 */
unsigned char Init_GPIO(St_GPIO *GPIO,GPIO_config *GPIO_config_t);

/**
 * @brief This function is used to write on a pin, whether it is high or low
 * @param GPIO 
 * @param Pin 
 * @param state 
 * @return 1: no problem
 *         0: exist problem in program s
 */
unsigned char Write_Pin(St_GPIO *GPIO, unsigned char Pin,St_Pin_State state);

/**
 * @brief This function is used to read the status pin
 * @param GPIO 
 * @param Pin 
 * @return St_Pin_State  @arg : High
 *                       @arg : Low
 */
St_Pin_State Read_Pin(St_GPIO *GPIO, unsigned char Pin);

/**
 * @brief This function is used to read the status of Pins port
 * @param GPIO 
 * @return Pins state 
 */
unsigned char Read_Pins(St_GPIO *GPIO);

/**
 * @brief used to toggle pin status
 * @param GPIO 
 * @param Pin 
 */
void Toggle_pin(St_GPIO *GPIO,unsigned char Pin);

/**
 * @brief use to write 8 bit register
 * @param GPIO 
 * @param Pin 
 */
void Write_Port_Register(St_GPIO *GPIO,unsigned char Pin);

/**
 * @brief used to change Pin direction
 * 
 * @param GPIO 
 * @param Pin 
 * @param state
 */
void Change_Direction(St_GPIO *GPIO,unsigned char Pin,En_Pin_config state);

/**
 * @brief used to write 8 bit in DDRx register
 * 
 * @param GPIO 
 * @param Pin 
 */
void Write_Dir_Register(St_GPIO *GPIO,unsigned char Pin);
#endif