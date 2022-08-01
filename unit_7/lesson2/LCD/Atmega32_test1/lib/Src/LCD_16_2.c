

#include "LCD_16_2.h"
#include "GPIO.h"
#include <util/delay.h>
#include <stddef.h>


volatile char LCD_Rows2[16]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'};

void Kick_Enable_pin(const LCD_16_2 *lcd_instance);


void Kick_Enable_pin(const LCD_16_2 *lcd_instance)
{
    Write_Pin(lcd_instance->Enable_Port,lcd_instance->Enable_Pin,Low);
    asm volatile ("nop");
    asm volatile ("nop");
    _delay_ms(1);
    Write_Pin(lcd_instance->Enable_Port,lcd_instance->Enable_Pin,High);
}

unsigned char LCD_init(const LCD_16_2 *lcd_instance)
{
    Change_Direction(lcd_instance->R_W_Port,lcd_instance->R_W_Pin,OUTPUT);
    Change_Direction(lcd_instance->RS_Port,lcd_instance->RS_Pin,OUTPUT);
    Change_Direction(lcd_instance->Enable_Port,lcd_instance->Enable_Pin,OUTPUT);

    Write_Pin(lcd_instance->RS_Port,lcd_instance->RS_Pin,Low); // instruction register
    Write_Pin(lcd_instance->R_W_Port,lcd_instance->R_W_Pin,Low); // Write data
    Write_Pin(lcd_instance->Enable_Port,lcd_instance->Enable_Pin,Low); // Enable read/write


    #ifdef LCD_8_Bit

        Write_Dir_Register(lcd_instance->Data_Port,0xFF);

        _delay_ms(22);
        Write_Command(lcd_instance,CMD_LCD_Clear);
        Write_Command(lcd_instance,CMD_LCD_Function_Set|CMD_LCD_OP_DL|CMD_LCD_OP_N|CMD_LCD_OP_F);   // Function Set
        Write_Command(lcd_instance,CMD_LCD_Entry_Mode_Set|CMD_LCD_OP_I_D);                          // Entry Mode
        Write_Command(lcd_instance,CMD_LCD_Begin_AT_First_Raw);                                     // Begin At First Raw
        Write_Command(lcd_instance,CMD_LCD_Display_On_Off|CMD_LCD_OP_B|CMD_LCD_OP_C|CMD_LCD_OP_D);  // Display Is Active
    #endif
    
    #ifdef LCD_4_Bit
        
        unsigned char temp = 0xF0 & (lcd_instance->Data_Port->Un_DDRx.DDRx);
        Write_Port_Register(lcd_instance->Data_Port,(temp | 0x0F));
        
        temp = 0xF0 & (lcd_instance->Data_Port->Un_PORTx.PORTx);
        Write_Port_Register(lcd_instance->Data_Port,(temp | ((CMD_LCD_Function_Set | CMD_LCD_OP_N | CMD_LCD_OP_F) >> 4)));
        Write_Port_Register(lcd_instance->Data_Port,(temp | (CMD_LCD_Function_Set | CMD_LCD_OP_N | CMD_LCD_OP_F)));
        
        temp = 0xF0 & (lcd_instance->Data_Port->Un_PORTx.PORTx);
        Write_Port_Register(lcd_instance->Data_Port,(temp | ((CMD_LCD_Display_On_Off|CMD_LCD_OP_D|CMD_LCD_OP_C|CMD_LCD_OP_B) >> 4)));
        Write_Port_Register(lcd_instance->Data_Port,(temp | (CMD_LCD_Display_On_Off|CMD_LCD_OP_D|CMD_LCD_OP_C|CMD_LCD_OP_B)));

        temp = 0xF0 & (lcd_instance->Data_Port->Un_PORTx.PORTx);
        Write_Port_Register(lcd_instance->Data_Port,(temp | ((CMD_LCD_Entry_Mode_Set|CMD_LCD_OP_I_D|CMD_LCD_OP_S) >> 4)));
        Write_Port_Register(lcd_instance->Data_Port,(temp | (CMD_LCD_Entry_Mode_Set|CMD_LCD_OP_I_D|CMD_LCD_OP_S)));
        
    #endif
    
    _delay_ms(40);

    /*------------------- Init LCD -------------------*/


}


void Check_BF(const LCD_16_2 *lcd_instance)
{
    Write_Dir_Register(lcd_instance->Data_Port,~(0xFF << DATA_shift));
    Write_Pin(lcd_instance->R_W_Port,lcd_instance->R_W_Pin,High);
    Write_Pin(lcd_instance->RS_Port,lcd_instance->RS_Pin,Low);
    Kick_Enable_pin(lcd_instance);
    Write_Dir_Register(lcd_instance->Data_Port,0xFF);
    Write_Pin(lcd_instance->R_W_Port,lcd_instance->R_W_Pin,Low);
}

void Shift_R_Cursor(const LCD_16_2 *lcd_instance)
{
    Write_Command(lcd_instance,CMD_LCD_Cursor_Display_Shift|CMD_LCD_OP_R_L);
}

void Shift_L_Cursor(const LCD_16_2 *lcd_instance)
{
    Write_Command(lcd_instance,CMD_LCD_Cursor_Display_Shift);
}

unsigned char Read_Cursor_Add(const LCD_16_2 *lcd_instance)
{

}

unsigned char Write_Character(const LCD_16_2 *lcd_instance,unsigned char ch)
{
    Check_BF(lcd_instance);
    Write_Pin(lcd_instance->RS_Port,lcd_instance->RS_Pin,High);
    #ifdef LCD_8_Bit
        Write_Port_Register(lcd_instance->Data_Port,ch);
    #endif

    #ifdef LCD_4_Bit
        Write_Port_Register(lcd_instance->Data_Port,((lcd_instance->Data_Port.PORTx & 0x0F) | (command & 0xF0)));
        Write_Pin(lcd_instance->RS_Port,lcd_instance->RS_Pin,High);
        Write_Pin(lcd_instance->R_W_Port,lcd_instance->R_W_Pin,Low);
        Write_Port_Register(lcd_instance->Data_Port,((lcd_instance->Data_Port.PORTx & 0x0F) | (command << 0x04)));
        Kick_Enable_pin(lcd_instance);
    #endif
    Write_Pin(lcd_instance->RS_Port,lcd_instance->RS_Pin,High);
    Write_Pin(lcd_instance->R_W_Port,lcd_instance->R_W_Pin,Low);
    Kick_Enable_pin(lcd_instance);
}

unsigned char Write_Character_with_coordinator(const LCD_16_2 *lcd_instance,unsigned char ch,unsigned char column,En_Lcd_Raw Raw)
{
    Jump_to_coordinator(lcd_instance,column,Raw);
    Check_BF(lcd_instance);
    Write_Pin(lcd_instance->RS_Port,lcd_instance->RS_Pin,High);
    Write_Port_Register(lcd_instance->Data_Port,ch);
    Write_Pin(lcd_instance->RS_Port,lcd_instance->RS_Pin,High);
    Write_Pin(lcd_instance->R_W_Port,lcd_instance->R_W_Pin,Low);
    Kick_Enable_pin(lcd_instance);
}

unsigned char Write_String(const LCD_16_2 *lcd_instance,unsigned char *ch)
{
    while((*ch) > 0)
    {
        Write_Character(lcd_instance,*ch);
        ch++;
    }
}

unsigned char Write_String_with_coordinator(const LCD_16_2 *lcd_instance,unsigned char *ch,unsigned char column,En_Lcd_Raw Raw)
{
    Jump_to_coordinator(lcd_instance,column,Raw);
    while((*ch) > 0)
    {
        Write_Character(lcd_instance,*ch);
        ch++;
    }
}

void Jump_to_coordinator(const LCD_16_2 *lcd_instance,unsigned char column,En_Lcd_Raw Raw)
{
    switch (Raw)
    {
    case First_R:
        Write_Command(lcd_instance,CMD_LCD_Begin_AT_First_Raw + column);

        break;
    case Seconde_R:
        Write_Command(lcd_instance,CMD_LCD_Begin_AT_Seconde_Raw + column);
        break;
    default:
        break;
    }
}

void Write_Command(const LCD_16_2 *lcd_instance,unsigned char command)
{
    #ifdef LCD_8_Bit
    Check_BF(lcd_instance);
    
    Write_Port_Register(lcd_instance->Data_Port,command);
    
    #endif
    
    #ifdef LCD_4_Bit
        Write_Port_Register(lcd_instance->Data_Port,((lcd_instance->Data_Port.PORTx & 0x0F) | (command & 0xF0)));
        Write_Pin(lcd_instance->RS_Port,lcd_instance->RS_Pin,Low);
        Write_Pin(lcd_instance->R_W_Port,lcd_instance->R_W_Pin,Low);    
        Kick_Enable_pin(lcd_instance);    
        Write_Port_Register(lcd_instance->Data_Port,((lcd_instance->Data_Port.PORTx & 0x0F) | (command << 4)));
    #endif

    Write_Pin(lcd_instance->RS_Port,lcd_instance->RS_Pin,Low);
    Write_Pin(lcd_instance->R_W_Port,lcd_instance->R_W_Pin,Low);
    Kick_Enable_pin(lcd_instance);
}

void write_first_raw_with_rot(const LCD_16_2 *lcd_instance,char *base,unsigned char buffersize)
{
    static char *base_temp = NULL;
	static unsigned char temp = 0;
	if(base_temp == NULL)
    {
        Jump_to_coordinator(lcd_instance,15,First_R);
        base_temp = base;
    }
    Write_Character(lcd_instance,*base_temp);
    Write_Command(lcd_instance,CMD_LCD_Cursor_Display_Shift|CMD_LCD_OP_S_C);
    temp++;
    if(*(base_temp) != '\0')
    {
        base_temp++;
    }
    if(temp > buffersize + 16)
    {
        Jump_to_coordinator(lcd_instance,15,First_R);
        temp = 0;
        base_temp = base;
    }
}

void write_with_move(const LCD_16_2 *lcd_instance,char *base,En_Lcd_Raw Raw,unsigned char buffersize)
{
    static char *base_temp = NULL;
    static char *till_temp = NULL;
    static char *current_loc = NULL;
    static unsigned char counter = 0;
    if(base_temp == NULL)
    {
        base_temp = base;
        till_temp = base;
        current_loc = base;
        Write_Command(lcd_instance,CMD_LCD_Entry_Mode_Set);                          // Entry Mode
    }
    Jump_to_coordinator(lcd_instance,15,First_R);
    counter++;
    while(current_loc >= base_temp)
    {
        Write_Character(lcd_instance,*current_loc);
        current_loc--;
    }
    if(*till_temp != '\0')
    {
        till_temp++;
        current_loc = till_temp;
    }else
    {
        for(int i = 0; i < 16; i++)
        {
            Write_Command(lcd_instance,CMD_LCD_Cursor_Display_Shift|CMD_LCD_OP_S_C);
            _delay_ms(70);
        }
        Write_Command(lcd_instance,CMD_LCD_Clear);
        LCD_init(lcd_instance);
        Write_Command(lcd_instance,CMD_LCD_Entry_Mode_Set);                          // Entry Mode
        counter = 0;
        base_temp = base;
        till_temp = base_temp;
        current_loc = base;
    }
    if(counter > 15)
    {
        base_temp++;
    }
}

void clean_Lcd(LCD_16_2 *lcd_instance)
{
    Write_Command(lcd_instance,CMD_LCD_Clear);
}