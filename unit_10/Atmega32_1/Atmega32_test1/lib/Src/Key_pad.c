

#include "Key_pad.h"
#include "LCD_16_2.h"
#include <avr/delay.h>

static uint8_t pad_output_pin[4]={0};
static uint8_t pad_input_pin[4]={0};
static uint8_t key_pad_keys[4][4] = {{'7','8','9',0x2F},
                                     {'4','5','6','x'},
                                     {'1','2','3',0x2D},
                                     {' ','0','=','+'}};
                                     


extern LCD_16_2 Lcd_config;

uint8_t Key_pad_init(St_Key_pad *key_pad)
{
    GPIO_config key_out = {0};
    key_out.mode = OUTPUT;
    key_out.pin = key_pad->output.Pins;
    Init_GPIO(key_pad->output.Port,&key_out);
    //Write_Pin(key_pad->output.Port,key_pad->output.Pins,High);
    uint8_t temp  = 0;
    for(uint8_t i = 0; i < 8; i++)
    {
        if(key_pad->output.Pins & 1<<i)
        {
            pad_output_pin[temp] = 1<<i;
            temp++;
        }
    }
    if(temp > 4) return 0;
    temp = 0;
    for(uint8_t i = 0; i < 8; i++)
    {
        if(key_pad->input.Pins & 1<<i)
        {
            pad_input_pin[temp] = 1<<i;
            temp++;
        }
    }
    if(temp > 4) return 0;
    Write_Pin(key_pad->input.Port,key_pad->input.Pins,High);
    Write_Pin(key_pad->output.Port,key_pad->output.Pins,High);

    return 1;

}



void Check_Prass_Button(St_Key_pad *key_pad)
{
    Write_Pin(key_pad->output.Port,key_pad->output.Pins,High);
    Write_Pin(key_pad->input.Port,key_pad->input.Pins,High);
    for(volatile uint8_t i = 0; i < 4; i++)
    {
        Write_Pin(key_pad->output.Port,pad_output_pin[i],Low);
        for(volatile uint8_t j = 0; j < 4; j++)
        {
            while(Read_Pin(key_pad->input.Port,pad_input_pin[j]) == Low)
            {
                Write_Pin(key_pad->output.Port,pad_output_pin[i],High);
                while(Read_Pin(key_pad->input.Port,pad_input_pin[j]) == Low);
                Write_Pin(key_pad->input.Port,key_pad->input.Pins,High);
                Write_Pin(key_pad->input.Port,key_pad->input.Pins,High);
                if((j == 3) && (i == 0)){clean_Lcd(&Lcd_config); return;}
                Write_Character(&Lcd_config,key_pad_keys[j][i]);

                break;
            }
        }
    }
}