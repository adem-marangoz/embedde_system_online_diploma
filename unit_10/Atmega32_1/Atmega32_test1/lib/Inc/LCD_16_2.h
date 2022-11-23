#ifndef LCD_12_6_H_
#define LCD_12_6_H_

#include "GPIO.h"

#define LCD_8_Bit
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** 
 * @ ----------------------------------------- LCD Command Abbreviations -----------------------------------------
 * I/D  :   0 = Increment /  1= Decrement
 * S/C  :   Display shift/ Cusor move
 * S    :   (S = 0 No display shift)(S = 1 display shift)Accompaies display shift
 * D    :   Sets On/Off of all display (D = 0 Display off)(D = 1 Display on)
 * C    :   cursor On/Off (C = 0 Cursor off)(C = 1 Cursor on)       
 * B    :   blink of cursor position character (B = 0 Cursor blink off)(B = 1 Cursor blink on)
 * R/L  :   1 : Shift to Right/ 0 : Shift to Left
 * DL   :   (DL = 1 8_bit). (DL = 0; 4_bit )(Data length)
 * N    :   (N = 1 2_lines). (N = 0 1_line)
 * F    :   (F = 1 5x10 dots)/ (F = 0; 5x8 dots) (font)
 * BF   :   Internally operation / Instructions acceptable
 * DDRAM:   Display data RAM
 * CGRAM:   Character generator RAM
 * ACG  :   CGRAM address
 * ADD  :   DDRAM address (corresponds to cursor address)
 * AC   :   Address counter used for both DDRAM and CGRAM addresses
 * BF   :   Busy Flag
 * RS   :   Register Selects (RS = 0 instruction register / RS = 1 Data register)
 */                                                            // RS,     R/W,    DB7,    DB6,    DB5,    DB4,    DB3,    DB2,    DB1,    DB0
#define CMD_LCD_Clear                               0b00000001 // 0,      0,      0,      0,      0,      0,      0,      0,      0,      1    Execution time 1.64ms
#define CMD_LCD_Re_Home                             0b00000010 // 0,      0,      0,      0,      0,      0,      0,      0,      1,      x    Execution time 1.64ms
#define CMD_LCD_Entry_Mode_Set                      0b00000100 // 0,      0,      0,      0,      0,      0,      0,      1,      I/D,    S    Execution time 40us
#define CMD_LCD_Display_On_Off                      0b00001000 // 0,      0,      0,      0,      0,      0,      1,      D,      C,      B    Execution time 40us
#define CMD_LCD_Cursor_Display_Shift                0b00010000 // 0,      0,      0,      0,      0,      1,      S/C,    R/L,    x,      x    Execution time 40us
#define CMD_LCD_Function_Set                        0b00110000 // 0,      0,      0,      0,      1,      DL,     N,      F,      x,      x    Execution time 40us
#define CMD_LCD_Set_CGRam_Add                       0b01000000 // 0,      0,      0,      1,      CGRAM Add                                    Execution time 40us
#define CMD_LCD_Set_DDRam_Add                       0b10000000 // 0,      0,      1,      DDRAM Add                                            Execution time 40us
#define CMD_LCD_Read_Busy_flag_and_Add_Counter      0b01000000 // 0,      1,      BF,     DDRAM Add                                            Execution time 0us
#define CMD_LCD_Write_To_CGRAM_or_DDRAM             0b10000000 // 1,      0,      WR Data                                                      Execution time 40us
#define CMD_LCD_Read_From_CGRAM_or_DDRAM            0b11000000 // 1,      1,      RD Data                                                      Execution time 40us
#define CMD_LCD_Begin_AT_First_Raw                  0b10000000
#define CMD_LCD_Begin_AT_Seconde_Raw                0b11000000
//------------------------------------------------ Command Options -----------------------------------------------
#define CMD_LCD_OP_I_D                              0x01 << 1
#define CMD_LCD_OP_S_C                              0x01 << 3
#define CMD_LCD_OP_R_L                              0x01 << 2
#define CMD_LCD_OP_DL                               0x01 << 4
#define CMD_LCD_OP_N                                0x01 << 3
#define CMD_LCD_OP_F                                0x01 << 2
#define CMD_LCD_OP_S                                0x01 << 0
#define CMD_LCD_OP_D                                0x01 << 2
#define CMD_LCD_OP_C                                0x01 << 1
#define CMD_LCD_OP_B                                0x01 << 0
#ifdef  LCD_8_Bit
   #define DATA_shift                                0x00 
#else if LCD_4_Bit
   #define DATA_shift                                0x04 
#endif


/**
 * @NOTE: Each Raw can payload Maxsimum 40 charachter
 */
// ------------------------------------------- LCD Command Abbreviations -----------------------------------------
typedef enum
{
    First_R = 0,
    Seconde_R
}En_Lcd_Raw;

typedef struct 
{
	St_GPIO *Data_Port;
    St_GPIO *RS_Port;
    St_GPIO *R_W_Port;
    St_GPIO *Enable_Port;
    unsigned char R_W_Pin;
    unsigned char Enable_Pin;
    unsigned char RS_Pin;
}LCD_16_2;



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char LCD_init(const LCD_16_2 *lcd_instance);
void Check_BF(const LCD_16_2 *lcd_instance);
void Shift_R_Cursor(const LCD_16_2 *lcd_instance);
void Shift_L_Cursor(const LCD_16_2 *lcd_instance);
unsigned char Read_Cursor_Add(const LCD_16_2 *lcd_instance);
unsigned char Write_Character(const LCD_16_2 *lcd_instance,unsigned char ch);
unsigned char Write_Character_with_coordinator(const LCD_16_2 *lcd_instance,unsigned char ch,unsigned char column,En_Lcd_Raw Raw);
unsigned char Write_String(const LCD_16_2 *lcd_instance,unsigned char *ch);
unsigned char Write_String_with_coordinator(const LCD_16_2 *lcd_instance,unsigned char *ch,unsigned char column,En_Lcd_Raw Raw);
uint8_t Write_String_Stop_with_Character(const LCD_16_2 *lcd_instance,unsigned char *ch, uint8_t Stop_char);
void Jump_to_coordinator(const LCD_16_2 *lcd_instance,unsigned char column,En_Lcd_Raw Raw);
void Write_Command(const LCD_16_2 *lcd_instance,unsigned char command);
void write_with_move(const LCD_16_2 *lcd_instance,char *base,En_Lcd_Raw Raw,unsigned char buffersize);
void write_first_raw_with_rot(const LCD_16_2 *lcd_instance,char *base,unsigned char buffersize);
void clean_Lcd(LCD_16_2 *lcd_instance);






#endif