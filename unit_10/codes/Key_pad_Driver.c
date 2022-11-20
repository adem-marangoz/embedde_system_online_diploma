/**
 * @file Key_pad_Driver.c
 * @author adem alnajjar (adem.alnajjar95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//-------------------------------- Include Files -------------------------------
#include "Key_pad_Driver.h"
#include "Stm32f10xx_EXTI.h"
#include "LCD_Driver.h"
#include "Application.h"
#include "Stm32_f10xx_Systick.h"

//==============================================================================

//------------------------------- Local Objects --------------------------------
uint8_t Check_Keypad_Pins(uint16_t Pins, uint8_t max_error, uint32_t *Put_to_array);

static uint8_t Drain_Set_Counter = 0;

// pad_Drain_pin array to determine keypad Drain
static uint32_t pad_Drain_pin[KeyPad_Drain]={0};

// pad_Soruce_pin array check keypad Soruce status
static uint32_t pad_Soruce_pin[KeyPad_Source]={0};

// Source Pin's PORT
St_GPIO_Typedef *GPIOx = NULL;

// Through the matrix pad_Drain_pin and the matrix pad_Soruce_pin , the type of character is determined
// static uint32_t key_pad_keys[Soruce_Drain_Pins_Num][Soruce_Drain_Pins_Num] = {{'7','8','9',0x2F},
//                                                                               {'4','5','6','x'},
//                                                                               {'1','2','3',0x2D},
//                                                                               {' ','0','=','+'}};

const uint8_t KeyPad_Keys[KeyPad_Source][KeyPad_Drain] = { {'1', '2', '3'},
                                                            {'4', '5', '6'},
                                                            {'7', '8', '9'},
                                                            {'*', '0', '#'}};


//==============================================================================


//------------------------------ External Objects ------------------------------
extern LCD_16_2 Lcd_config;
extern void _delay_ms(uint32_t time);
extern const uint16_t EXTI_Streem[16][16];
//==============================================================================


/**
 * @brief Used to configure the Soruce and Drain pins of the keypad
 * 
 * @param[in] key_pad  The keypad data structure containing the port and pins to be configured
 * @retval : 0 Fail
 *           1 succesful 
 */
uint8_t Key_pad_init(St_Key_pad *key_pad)
{
    uint8_t temp = 0;

    // Put Soruce and Drain pins to array
    temp = Check_Keypad_Pins(key_pad->Drain.Pins, KeyPad_Drain, pad_Drain_pin);
    if(temp == 0) return 0;
    temp = Check_Keypad_Pins(key_pad->Soruce.Pins, KeyPad_Source, pad_Soruce_pin);
    if(temp == 0) return 0;

    // Config Drain Pins
    GPIO_InitTypeDef gpio_key_config = {0};
    gpio_key_config.Mode = GPIO_MODE_INPUT;
    gpio_key_config.Pull = GPIO_PULLUP;
    gpio_key_config.Pin = key_pad->Soruce.Pins;
    Init_GPIO(key_pad->Soruce.Port,&gpio_key_config);

    // Config Soruce Pins
    gpio_key_config.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_key_config.Speed = GPIO_SPEED_FREQ_10MHZ;
    gpio_key_config.Pin = key_pad->Drain.Pins;
    Init_GPIO(key_pad->Drain.Port,&gpio_key_config);

    // Init The Drain Pins to 0
    Reset_pin(key_pad->Drain.Port,key_pad->Drain.Pins);


    return 1;
}


/**
 * @brief Is used to replace Pins to array
 * @param Pins : Selected Pins 
 * @param max_error : Maximum of replace pins
 * @param Put_to_array : Array first Address
 * @return uint8_t 0 : Seted Pins larger then max_error value
 *                 1 : No problem
 */
uint8_t Check_Keypad_Pins(uint16_t Pins, uint8_t max_error, uint32_t *Put_to_array)
{
    uint8_t temp  = 0;
    for(uint8_t i = 0; i <= GPIO_PIN_NUMBER; i++)
    {
        if(Pins & 1 << i)
        {
            Put_to_array[temp] = 1<<i;
            temp++;
        }
    }
    if(temp > max_error){return 0;}
    return 1;
}


/**
 * @brief Set Drain Keypad pin
 * @param key_pad The keypad data structure containing the port and pins to be configured
 */
void Set_Key_Drain_Pins(St_Key_pad const *key_pad)
{
    // Reset All Drain Pins
    uint8_t temp;
    for(temp = 0 ; temp < KeyPad_Drain; temp++)
    {
        Reset_pin(key_pad->Drain.Port,pad_Drain_pin[temp]);
    }

    // Set one Drain pin
    if(Drain_Set_Counter >= KeyPad_Drain)
        Drain_Set_Counter = 0xFF;
    Drain_Set_Counter++;

    Set_pin(key_pad->Drain.Port,pad_Drain_pin[Drain_Set_Counter]);   
}


/**
 * @brief Is used to check the Soruce pins is set or not
 * @param key_pad The keypad data structure containing the port and pins to be configured
 * @return uint8_t : when sets a Soruce pin return Index of set Soruce pin
 *                 : when no set any pin return 0xFF
 */
uint8_t Check_Key_Soruce_Pins(St_Key_pad const *key_pad)
{
    uint8_t counter = 0;
    for(counter = 0; counter < KeyPad_Source; counter++)
    {
        if(Read_pin(key_pad->Soruce.Port,pad_Soruce_pin[counter]) == GPIO_PIN_SET)
        {
            return counter;
        }
    }
    return 0xFF;
}





/**
 * @brief To check the keys being pressed and send the character to the LCD panel
 * @param[in] key_pad  The keypad data structure containing the port and pins to be configured
 */
uint8_t Check_Prass_Button(St_Key_pad const *key_pad)
{
    // Set Drain pin
    Set_Key_Drain_Pins(key_pad);

    uint8_t temp = 0;
    temp = Check_Key_Soruce_Pins(key_pad);
    if(temp == 0xFF){return 0;}
    while(Read_pin(key_pad->Soruce.Port,pad_Soruce_pin[temp]) == GPIO_PIN_SET);
    Reset_pin(key_pad->Soruce.Port,pad_Soruce_pin[temp]);
    Reset_pin(key_pad->Soruce.Port,pad_Soruce_pin[temp]);
    Reaction_Of_Prass(temp, Drain_Set_Counter);
    delay_us(200);

    return 1;
}
