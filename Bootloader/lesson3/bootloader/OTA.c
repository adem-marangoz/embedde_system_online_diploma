/**
 * @file OTA.c
 * @author adem alnajjar (adem.marangoz95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "OTA.h"
#include "Stm32f10x_UART.h"
#include "Stm32f10xx_Flash.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

//------------------------------- Local Objects --------------------------------
/* Buffer to hold the received data */
static uint8_t Rx_Buffer[ ETX_OTA_PACKET_MAX_SIZE ];

/* OTA State */
static ETX_OTA_STATE_ ota_state = ETX_OTA_STATE_IDLE;

/* Firmware Total Size that we are going to receive */
static uint32_t ota_fw_total_size;
/* Firmware image's CRC32 */
static uint32_t ota_fw_crc;
/* Firmware Size that we have received */
static uint32_t ota_fw_received_size;


static uint16_t etx_receive_chunk( uint8_t *buf, uint16_t max_len );
static ETX_OTA_EX_ etx_process_data( uint8_t *buf, uint16_t len );
static uint8_t write_data_to_flash_app( uint8_t *data,
                                        uint16_t data_len, bool is_first_block );
//==============================================================================


//------------------------------- Extern Objects -------------------------------
extern St_Uart_API uart1_config;
extern St_Uart_API uart2_config;
//==============================================================================


//------------------------------ Global Function -------------------------------

/**
  * @brief Download the application from UART and flash it.
  * @param None
  * @retval ETX_OTA_EX_
  */
ETX_OTA_EX_ etx_ota_download_and_flash( void )
{
    ETX_OTA_EX_ ret  = ETX_OTA_EX_OK;
    uint16_t    len;

    /* Reset the variables */
    ota_fw_total_size    = 0u;
    ota_fw_received_size = 0u;
    ota_fw_crc           = 0u;
    ota_state            = ETX_OTA_STATE_START;

    do
    {
        // Clear The Buffer
        volatile uint16_t index = 0;
        for(;index < ETX_OTA_PACKET_MAX_SIZE; index++)
            Rx_Buffer[index] = 0;

        len = etx_receive_chunk(Rx_Buffer, ETX_OTA_PACKET_MAX_SIZE);

        if(len != 0)
        {
            ret = etx_process_data( Rx_Buffer, len );
        }else
        {
            ret = ETX_OTA_EX_ERR; // didn't received data. break.
        }

    } while (0);
    
}

/**
  * @brief Process the received data from UART4.
  * @param buf buffer to store the received data
  * @param max_len maximum length to receive
  * @retval ETX_OTA_EX_
  */
static ETX_OTA_EX_ etx_process_data( uint8_t *buf, uint16_t len )
{
    ETX_OTA_EX_ ret = ETX_OTA_EX_ERR;

    do
    {
        if( ( buf == NULL ) || ( len == 0u) )
        {
        break;
        }

        //Check we received OTA Abort command
        ETX_OTA_COMMAND_ *cmd = (ETX_OTA_COMMAND_*)buf;
        if( cmd->packet_type == ETX_OTA_PACKET_TYPE_CMD )
        {
            if( cmd->cmd == ETX_OTA_CMD_ABORT )
            {
                break; // Received OTA Abort command. Stop the process
            }
        }

        switch (ota_state)
        {
            case ETX_OTA_STATE_IDLE:
            {
                Send_Text_Uart(&uart1_config,"ETX_OTA_STATE_IDLE...\r\n", Enable);
                ret = ETX_OTA_EX_OK;
                break;
            }

            case ETX_OTA_STATE_START:
            {
                ETX_OTA_COMMAND_ *cmd = (ETX_OTA_COMMAND_*)buf;
                if( cmd->packet_type == ETX_OTA_PACKET_TYPE_CMD )
                {
                    if( cmd->cmd == ETX_OTA_CMD_START )
                    {
                        Send_Text_Uart(&uart1_config,"Received OTA START Command.\r\n", Enable);
                        ota_state = ETX_OTA_STATE_HEADER;
                        ret = ETX_OTA_EX_OK;
                    }
                }
                break;
            }

            case ETX_OTA_STATE_HEADER:
            {
                ETX_OTA_HEADER_ *header = (ETX_OTA_HEADER_*)buf;
                if( header->packet_type == ETX_OTA_PACKET_TYPE_HEADER )
                {
                    ota_fw_total_size = header->meta_data.package_size;
                    ota_fw_crc        = header->meta_data.package_crc;
                    Send_Text_Uart(&uart1_config,"Received OTA Header. FW Size.\r\n", Enable);
                    ota_state = ETX_OTA_STATE_DATA;
                    ret = ETX_OTA_EX_OK;
                }
                break;
            }

            case ETX_OTA_STATE_DATA:
            {
                ETX_OTA_DATA_ *data = (ETX_OTA_DATA_*)buf;
                uint16_t data_len = data->data_len;

                if( data->packet_type == ETX_OTA_PACKET_TYPE_DATA )
                {

                }
                break;
            }
            default:
                break;
        }

    } while (0);
    
}



/**
  * @brief Write data to the Application's actual flash location.
  * @param data data to be written
  * @param data_len data length
  * @is_first_block true - if this is first block, false - not first block
  * @retval HAL_StatusTypeDef
  */
static uint8_t write_data_to_flash_app( uint8_t *data,
                                        uint16_t data_len, bool is_first_block )
{
    uint8_t ret = 0;
    ret = Flash_Unlock();
    do
    {
        if(ret != 0)
        {
            break;
        }
        
        if(is_first_block)
        {
            Send_Text_Uart(&uart1_config,"Erasing the Flash memory ...\r\n", Enable);
            Flash_Erase_Pages()// TODO : start Erase Address and how many page
            
             
        }

    } while (false);
    
    
}

/**
  * @brief Receive a one chunk of data.
  * @param buf buffer to store the received data
  * @param max_len maximum length to receive
  * @retval ETX_OTA_EX_
  */
static uint16_t etx_receive_chunk( uint8_t *buf, uint16_t max_len )
{
    int16_t  ret;
    uint16_t index     = 0u;
    uint16_t data_len;

    do
    {
        //receive SOF byte (1byte)
        Receive_Char_Uart8(uart1_config.UARTx,&buf[index],Enable); // index = 0
        // Check Receive Data By Uart
        if(buf[index] == 0)
        {
            Send_Text_Uart(&uart1_config,"1.Error Not Receive Any Data\r\n", Enable);
            break;
        }

        // Check if Received SOF (1byte)
        if(buf[index++] != ETX_OTA_SOF) // index = 0 -> index = 1
        {
            Send_Text_Uart(&uart1_config,"Error Receive SOF Byte\r\n", Enable);
            ret = ETX_OTA_EX_ERR;
            break;
        }

        // Receive The Packet Type (1byte)
        Receive_Char_Uart8(uart1_config.UARTx,&buf[index++],Enable); // index = 1 -> index = 2
        // Check Receive Data By Uart
        if(buf[index] == 0) // index = 2
        {
            Send_Text_Uart(&uart1_config,"2.Error Not Receive Any Data\r\n", Enable);
            break;
        }

        // Get the data length (2bytes)
        Receive_Char_Uart8(uart1_config.UARTx,&buf[index++],Enable); // index = 2 -> index = 3
        Receive_Char_Uart8(uart1_config.UARTx,&buf[index],Enable); // index = 3
        index--; // index = 2
        data_len = *(uint16_t *)&buf[index];
        index += 2u; // index = 4

        // Receive Data
        for(uint16_t i = 0u; i < data_len; i++)
        {
            Receive_Char_Uart8(uart1_config.UARTx,&buf[index],Enable); // index = 4 -> index = 5
            // Check Receive Data By Uart
            if(buf[index] == 0)
            {
                Send_Text_Uart(&uart1_config,"3.Error Not Receive Any Data\r\n", Enable);
                break;
            }
            index++;
        }

        // Get The CRC (4bytes)
        Receive_Char_Uart8(uart1_config.UARTx,&buf[index],Enable);
        if(buf[index] == 0)
        {
            Send_Text_Uart(&uart1_config,"4.Error Not Receive Any Data\r\n", Enable);
            break;
        }
        Receive_Char_Uart8(uart1_config.UARTx,&buf[index++],Enable);
        if(buf[index] == 0)
        {
            Send_Text_Uart(&uart1_config,"5.Error Not Receive Any Data\r\n", Enable);
            break;
        }
        Receive_Char_Uart8(uart1_config.UARTx,&buf[index++],Enable);
        if(buf[index] == 0)
        {
            Send_Text_Uart(&uart1_config,"6.Error Not Receive Any Data\r\n", Enable);
            break;
        }
        Receive_Char_Uart8(uart1_config.UARTx,&buf[index++],Enable);
        if(buf[index] == 0)
        {
            Send_Text_Uart(&uart1_config,"7.Error Not Receive Any Data\r\n", Enable);
            break;
        }

        // Receive EOF (1byte)
        Receive_Char_Uart8(uart1_config.UARTx,&buf[index],Enable);
        if(buf[index] == 0)
        {
            Send_Text_Uart(&uart1_config,"8.Error Not Receive Any Data\r\n", Enable);
            break;
        }

    } while (0);

    if(max_len < index)
    {
        Send_Text_Uart(&uart1_config,"9.Error Received more than expected\r\n", Enable);
        index = 0;
    }    

    return index;

}
//==============================================================================