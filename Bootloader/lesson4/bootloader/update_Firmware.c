/**
 * @file update_Firmware.c
 * @author adem alnajjar (adem.marangoz95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */


//------------------------------- Include Files --------------------------------
#include "update_Firmware.h"
#include "Stm32f10x_UART.h"
#include "Stm32f10xx_GPIO.h"
#include "Stm32_f10xx_Systick.h"
#include "Stm32f10xx_Flash.h"
//==============================================================================



//------------------------------- Local Objects --------------------------------
uint16_t application_size = 0;
uint16_t application_write_idx = 0;

static uint8_t Check_Connection(void);
//==============================================================================


//------------------------------ External Objects ------------------------------
extern St_Uart_API uart1_config;
extern St_Uart_API uart2_config;
//==============================================================================

//------------------------------ Global Functions ------------------------------
static uint8_t Check_Connection(void)
{
    uint8_t tx = 'g';
    uint8_t rx = 0;
    uint8_t ret = 2;
    uint8_t count = 0;

    Send_Text_Uart(&uart1_config,"\r\nCheck connection with uart\r\n", Enable);
    Set_pin(GPIOC,GPIO_PIN_13);
    Delay_ms(1000);
    Reset_pin(GPIOC,GPIO_PIN_13);
    Delay_ms(1000);
    Set_pin(GPIOC,GPIO_PIN_13);
    Delay_ms(1000);

    while(1)
    {
        Send_Char_Uart(uart2_config.UARTx,(uint16_t*)&tx, Enable);
        ret = Receive_String_Uart(&uart2_config, &rx, 1, 500);

        if((ret == 1) || (rx == 'r'))
        {
            Send_Text_Uart(&uart1_config,"Firmware Update started.. \r\n", Enable);
            break;
        }

        if(count == 100)
        {
            Send_Text_Uart(&uart1_config,"No Data received for Firmware Update.. \r\n", Enable);
            break;
        }
        
        count++;
        Delay_ms(20);

    }   
    
    return ret;
}


uint8_t update_firmware(void)
{
    uint8_t xx = 0;
    uint8_t yy = 0;
    uint8_t x = 'x';
    uint8_t y = 'y';
    uint8_t ret = 2;
    uint16_t current_app_size = 0;
    uint16_t counter = 0;
    uint8_t Block[Page_Size];

    clear_buffer(Block, 0, Page_Size, 0); // clear buffer
    do
    {

        if(Check_Connection() == 1)
        {
            
            Send_Char_Uart(uart2_config.UARTx,(uint16_t*)&y, Enable); // send y character
            ret = Receive_String_Uart(&uart2_config, &yy, 1, 5000); // receive 1 byte application size
            // check error receive
            if(ret == 0) 
            {
                Send_Text_Uart(&uart1_config,"Get Application size error yy .. HALT.. \r\n", Enable);
                break;
            }

            Send_Char_Uart(uart2_config.UARTx,(uint16_t*)&x, Enable); // send x character
            ret = Receive_String_Uart(&uart2_config, &xx, 1, 5000); // receive 1 byte application size
            // check error receive
            if(ret == 0) 
            {
                Send_Text_Uart(&uart1_config,"Get Application size error xx .. HALT.. \r\n", Enable);
                break;
            }

            application_size = yy | (xx << 8); // Total application size
            // Display the total application size
            uint8_t str[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            add_unsigned_int_to_str(str, application_size);
            Send_Text_Uart(&uart1_config,"Application size = ", Enable);
            Send_Text_Uart(&uart1_config, str, Enable);
            Send_Text_Uart(&uart1_config,"\r\n", Enable);
            clear_buffer(str, 0, 10, 0); // clear buffer

            while(1)
            {
                // after receive 1 kilobyte write data into flash
                if((counter == Page_Size) || (current_app_size >= application_size))
                {
                    uint16_t rec_block = current_app_size/Page_Size;
                    add_unsigned_int_to_str(str, rec_block);
                    Send_Text_Uart(&uart1_config,"Received  Block[ ", Enable);
                    Send_Text_Uart(&uart1_config, str, Enable);
                    Send_Text_Uart(&uart1_config,"]\r\n", Enable);

                    // write to flash
                    write_data_into_flash(Block, Page_Size, (current_app_size <= Page_Size));

                    clear_buffer(str, 0, 10, 0);
                    counter = 0;
                }
                // after receive all data of firmware break
                if(current_app_size >= application_size){break;}

                Send_Char_Uart(uart2_config.UARTx,(uint16_t*)&y, Enable); // send y character
                ret = Receive_String_Uart(&uart2_config, &yy, 1, 5000); // receive 1 byte application data
                // check error receive
                if(ret == 0) 
                {
                    Send_Text_Uart(&uart1_config,"Get Application size error yy .. HALT.. \r\n", Enable);
                    break;
                }

                Send_Char_Uart(uart2_config.UARTx,(uint16_t*)&x, Enable); // send x character
                ret = Receive_String_Uart(&uart2_config, &xx, 1, 5000); // receive 1 byte application data
                // check error receive
                if(ret == 0) 
                {
                    Send_Text_Uart(&uart1_config,"Get Application size error xx .. HALT.. \r\n", Enable);
                    break;
                }

                // write data intro Block
                Block[counter++] = yy;
                Block[counter++] = xx;
                current_app_size += 2;
            }
        }


    } while (0);
    
    return 1;

}


uint8_t write_data_into_flash(uint8_t *data, uint16_t data_len, bool is_first)
{
    State_Typedef ret;
    do
    {
        ret = Flash_Unlock();
        if(ret != Ok) {break;}
        uint32_t App_start_add = 0x08004400;
        uint32_t PageN = 50;

        if(is_first)
        {
            Send_Text_Uart(&uart1_config,"Erasing the Flash memory.. \r\n", Enable);
            if(Flash_Erase_Pages(App_start_add,PageN) != Ok) { return ret;}

            application_write_idx = 0;
        }

        for(int i = 0; i < data_len/2; i++)
        {
            uint16_t halfword_data = data[i * 2] | (data[i * 2 +1] << 8);
            ret = Flash_Program(App_start_add + application_write_idx, halfword_data);
            
            if(ret == Ok){application_write_idx += 2;}
            else
            {
                Send_Text_Uart(&uart1_config,"Flash write error \r\n", Enable);
                return ret;
            }
        }

        Flash_Lock();
    } while (false);

    return ret;
    
}

//==============================================================================