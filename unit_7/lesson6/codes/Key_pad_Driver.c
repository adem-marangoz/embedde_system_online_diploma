

#include "Key_pad_Driver.h"
#include "LCD_Driver.h"

// pad_output_pin array to determine keypad output
static uint32_t pad_output_pin[4]={0};

// pad_input_pin array check keypad input status
static uint32_t pad_input_pin[4]={0};

// Through the matrix pad_output_pin and the matrix pad_input_pin , the type of character is determined
static uint32_t key_pad_keys[4][4] = {{'7','8','9',0x2F},
                                     {'4','5','6','x'},
                                     {'1','2','3',0x2D},
                                     {' ','0','=','+'}};
                                     


extern LCD_16_2 Lcd_config;
extern void _delay_ms(uint32_t time);

/**
 * @brief Used to configure the input and output pins of the keypad
 * 
 * @param[in] key_pad  The keypad data structure containing the port and pins to be configured
 * @retval : 0 Fail
 *           1 succesful 
 */
uint8_t Key_pad_init(St_Key_pad *key_pad)
{
    GPIO_InitTypeDef gpio_key_out = {0};
    gpio_key_out.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_key_out.Speed = GPIO_SPEED_FREQ_10MHZ;
    gpio_key_out.Pin = key_pad->output.Pins;
    Init_GPIO(key_pad->output.Port,&gpio_key_out);

    gpio_key_out.Mode = GPIO_MODE_INPUT;
    gpio_key_out.Pull = GPIO_PULLUP;
    gpio_key_out.Pin = key_pad->input.Pins;
    Init_GPIO(key_pad->input.Port,&gpio_key_out);

    uint8_t temp  = 0;
    for(uint8_t i = 0; i <= GPIO_PIN_NUMBER; i++)
    {
        if(key_pad->output.Pins & 1<<i)
        {
            pad_output_pin[temp] = 1<<i;
            temp++;
        }
    }
    if(temp > 4) return 0;
    temp = 0;
    for(uint8_t i = 0; i <= GPIO_PIN_NUMBER; i++)
    {
        if(key_pad->input.Pins & 1<<i)
        {
            pad_input_pin[temp] = 1<<i;
            temp++;
        }
    }
    if(temp > 4) return 0;
    Reset_pin(key_pad->output.Port,key_pad->output.Pins);

    return 1;

}


/**
 * @brief To check the keys being pressed and send the character to the LCD panel
 * @param[in] key_pad  The keypad data structure containing the port and pins to be configured
 */
void Check_Prass_Button(St_Key_pad const *key_pad)
{
    Reset_pin(key_pad->output.Port,key_pad->output.Pins);
    //Set_pin(key_pad->input.Port,key_pad->input.Pins);
    volatile uint16_t i;
    for(i = 0; i < 4; i++)
    {
        Set_pin(key_pad->output.Port,pad_output_pin[i]);
        for(volatile uint8_t j = 0; j < 4; j++)
        {
            if(Read_pin(key_pad->input.Port,pad_input_pin[j]) == GPIO_PIN_SET)
            {
                while(Read_pin(key_pad->input.Port,pad_input_pin[j]) == GPIO_PIN_SET);
                Reset_pin(key_pad->input.Port,pad_input_pin[j]);
                if((j == 3) && (i == 0)){clean_Lcd(&Lcd_config); return;}
                Write_Character(&Lcd_config,key_pad_keys[j][i]);

                break;
            }
        }
        Reset_pin(key_pad->output.Port,pad_output_pin[i]);
    }
}