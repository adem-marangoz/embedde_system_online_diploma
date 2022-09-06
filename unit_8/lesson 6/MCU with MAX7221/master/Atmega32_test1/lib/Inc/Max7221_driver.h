/**
 * @file Max7221_driver.h
 * @author adem alnajjar (adem.marangoz95@gmail.com)
 * @brief The MAX7221 are compact, serial input/outpuyt common-cathode display
 *          drivers that interface microprocessors
 * @version 0.1
 * @date 2022-09-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MAX7221_DRIVER_H_
#define MAX7221_DRIVER_H_

#include "Common.h"

/*
---------------------------- Serial Data Foramt --------------------------------
D15 D14 D13 D12 D11 D10 D9  D8  D7  D6  D5  D4  D3  D2  D1  1
X   X   X   X   ____Address___  MSB ________Data__________LSB
================================================================================
*/


//_______________________________ ADDRESS ______________________________________

#define Command_No_Op               0x00
#define Command_Digit0              0x01
#define Command_Digit1              0x02
#define Command_Digit2              0x03
#define Command_Digit3              0x04
#define Command_Digit4              0x05
#define Command_Digit5              0x06
#define Command_Digit6              0x07
#define Command_Digit7              0x08
#define Command_Decode_Mode         0x09    //@ref Decode_Mode_define
#define Commnad_Intensity           0x0A
#define Command_Scan_Limit          0x0B    //@ref Scan_Mode_define
#define Command_Shoutdown           0x0C    //@ref Mode_Operation_define
#define Command_Display_Test        0x0F    //@ref Display_Test_Mode_define
//==============================================================================


//_______________________________ Data Command _________________________________

//@ref Mode_Operation_define
#define Shutdown_Mode               0x00
#define Normal_Operation            0x01

//@ref Decode_Mode_define
#define No_decode_7_0               0x00
#define Code_B_Digit0               0x01
#define Code_B_Digit0_3             0x0F
#define Code_B_Digit0_7             0xFF

// Display Can show Charachter 
#define E_Charachter                0x0B
#define H_Charachter                0x0C
#define L_Charachter                0x0D
#define P_Charachter                0x0E
#define Hyphen_Charachter           0x0A


//@ref Scan_Mode_define
#define Display_Digit0              0x00
#define Display_Digit0To1           0x01
#define Display_Digit0To2           0x02
#define Display_Digit0To3           0x03
#define Display_Digit0To4           0x04
#define Display_Digit0To5           0x05
#define Display_Digit0To6           0x06
#define Display_Digit0To7           0xF7

//@ref Display_Test_Mode_define
#define Normal_Operation_Test       0x00
#define Dispaly_Test_Mode           0x01

//==============================================================================

//______________________________ Global Function _______________________________
void Max7212_Default_Init(void);
void Max7221_Send_Command_with_data(uint8_t command, uint8_t data);
void Max7221_On(void);
void Max7221_Off(void);
//==============================================================================

#endif