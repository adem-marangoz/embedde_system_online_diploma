/**
 * @file LCD_Driver.h
 * @author adem marangoz (adem.marangoz95@gmail.com)
 * @brief Contains the commands of the LCD, the structure of the LCD, and the functions that can be used
 * @version 0.1
 * @date 2022-08-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//-----------------------------------------------------------------------------------------------------------------
//___________________________________________Important Notes For Use LCD API ______________________________________
//*****************************************************************************************************************
//The data pins must be consecutive and the same port


//*****************************************************************************************************************
//-----------------------------------------------------------------------------------------------------------------


#ifndef LCD_H_
#define LCD_H_

#include "Stm32f10xx_GPIO.h"

#define LCD_4_Bit
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
 */  


/*
0x01 : clean LCD
0x02 : return to home
0x04 : Set Entry Mode
0x05 : Set Entry Mode,  Disable automatic shift
0x06 : Set Entry Mode, Decrement cursor
0x07 : Set Entry Mode , Disable automatic shift , Decrement cursor
0x08 : Display on/off
0x09 : Display on/off, curosr blink on
0x0A : Display on/off, cursor on
0x0B : Display on/off, cursor blink on , cursor on
0x0C : Display on/off, Display on
0x0D : Display on/off, cursor blink on, Display on
0x0E : Display on/off, cursor on, Display on
0x0F : Display on/off , cursor blink on, cursor on, Display on
0x10 : Cursor Display shift
0x14 : Cursor Display shift , Shift to right
0x18 : Cursor Display shift,   Curosr shift 
0x1C : Cursor Display shift , shift to right, cursor shift
*/
//----------------------------- Genaric Defination -----------------------------

                                                               // RS,     R/W,    DB7,    DB6,    DB5,    DB4,    DB3,    DB2,    DB1,    DB0
#define CMD_LCD_Clear                               0b00000001 // 0,      0,      0,      0,      0,      0,      0,      0,      0,      1    Execution time 1.64ms
#define CMD_LCD_Re_Home                             0b00000010 // 0,      0,      0,      0,      0,      0,      0,      0,      1,      x    Execution time 1.64ms
#define CMD_LCD_Entry_Mode_Set                      0b00000100 // 0,      0,      0,      0,      0,      0,      0,      1,      I/D,    S    Execution time 40us
#define CMD_LCD_Display_On_Off                      0b00001000 // 0,      0,      0,      0,      0,      0,      1,      D,      C,      B    Execution time 40us
#define CMD_LCD_Cursor_Display_Shift                0b00010000 // 0,      0,      0,      0,      0,      1,      S/C,    R/L,    x,      x    Execution time 40us
#define CMD_LCD_Set_CGRam_Add                       0b01000000 // 0,      0,      0,      1,      CGRAM Add                                    Execution time 40us
#define CMD_LCD_Set_DDRam_Add                       0b10000000 // 0,      0,      1,      DDRAM Add                                            Execution time 40us
#define CMD_LCD_Read_Busy_flag_and_Add_Counter      0b01000000 // 0,      1,      BF,     DDRAM Add                                            Execution time 0us
#define CMD_LCD_Write_To_CGRAM_or_DDRAM             0b10000000 // 1,      0,      WR Data                                                      Execution time 40us
#define CMD_LCD_Read_From_CGRAM_or_DDRAM            0b11000000 // 1,      1,      RD Data                                                      Execution time 40us
#define CMD_LCD_Begin_AT_First_Raw                  0b10000000
#define CMD_LCD_Begin_AT_Seconde_Raw                0b11000000
#define CMD_LCD_Begin_AT_Third_Raw                  0b10010000
#define CMD_LCD_Begin_AT_Fourth_Raw                 0b11010000

// ------------------------------- 8 Bit Operation -----------------------------
#ifdef LCD_8_Bit
#define CMD_LCD_Function_Set                        0b00110000 // 0,      0,      0,      0,      1,      DL,     N,      F,      x,      x    Execution time 40us
#define DATA_shift                                  0x00 
#define CMD_LCD_OP_DL                               0x01 << 4
#endif
// ------------------------------- 4 Bit Operation -----------------------------
#ifdef LCD_4_Bit
#define CMD_LCD_Function_Set                        0b00100000 // 0,      0,      0,      0,      1,      DL,     N,      F,      x,      x    Execution time 40us
#define DATA_shift                                  0x04
#define CMD_LCD_OP_DL                               0x00 << 4
#endif

//------------------------------------------------ Command Options -----------------------------------------------
#define CMD_LCD_OP_I_D                              0x01 << 1
#define CMD_LCD_OP_S_C                              0x01 << 3
#define CMD_LCD_OP_R_L                              0x01 << 2
#define CMD_LCD_OP_N                                0x01 << 3
#define CMD_LCD_OP_F                                0x01 << 2
#define CMD_LCD_OP_S                                0x01 << 0
#define CMD_LCD_OP_D                                0x01 << 2
#define CMD_LCD_OP_C                                0x01 << 1
#define CMD_LCD_OP_B                                0x01 << 0
#ifdef  LCD_8_Bit
#endif
#ifdef LCD_4_Bit
   
    
#endif


/**
 * @NOTE: Each Raw can payload Maxsimum 40 charachter
 */
// ------------------------------------------- LCD Command Abbreviations -----------------------------------------
//@ref Raw_LCD
typedef enum
{
    First_R = 0,
    Seconde_R,
    Third_R,
    Fourth_R
}En_Lcd_Raw;

/**
 * @brief Structure to specify : 
 * the Data port and its pins
 * the RS port and its pin
 * the RW port and its pin
 * the Enable port and its pin
 */
typedef struct 
{
	St_GPIO_Typedef *Data_Port;
    St_GPIO_Typedef *RS_Port;
    St_GPIO_Typedef *R_W_Port;
    St_GPIO_Typedef *Enable_Port;
    uint16_t R_W_Pin;
    uint16_t Enable_Pin;
    uint16_t RS_Pin;
    uint32_t Data_Pin;
    uint8_t count_of_first_pin;
}LCD_16_2;



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------- Function API -----------------------------------------------
unsigned char LCD_init(LCD_16_2  *lcd_instance);
void Check_BF( LCD_16_2 *lcd_instance);
void Shift_R_Cursor( LCD_16_2 *lcd_instance);
void Shift_L_Cursor( LCD_16_2 *lcd_instance);
unsigned char Read_Cursor_Add( LCD_16_2 *lcd_instance);
unsigned char Write_Character( LCD_16_2 *lcd_instance,unsigned char ch);
unsigned char Write_Character_with_coordinator( LCD_16_2 *lcd_instance,unsigned char ch,unsigned char column,En_Lcd_Raw Raw);
unsigned char Write_String( LCD_16_2 *lcd_instance,unsigned char *ch);
unsigned char Write_String_with_coordinator( LCD_16_2 *lcd_instance,unsigned char *ch,unsigned char column,En_Lcd_Raw Raw);
void Jump_to_coordinator( LCD_16_2 *lcd_instance,unsigned char column,En_Lcd_Raw Raw);
void Write_Command( LCD_16_2 *lcd_instance,unsigned char command);
void write_with_move( LCD_16_2 *lcd_instance,char *base,En_Lcd_Raw Raw,unsigned char buffersize);
void write_first_raw_with_rot( LCD_16_2 *lcd_instance,char *base,unsigned char buffersize);
void clean_Lcd(LCD_16_2 *lcd_instance);


#endif