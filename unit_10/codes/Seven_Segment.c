#include "Seven_Segment.h"

uint32_t numbers[10] = {0};

/**
 * @brief This function is to be used to configure ports and pins seven segment
 * @param[in] seven_segment The seven_segment data structure containing the port and pins to be configured
 */
void init_seven_segment(St_7_segment const *seven_segment)
{
    GPIO_InitTypeDef gpio_seven_out = {0};
    gpio_seven_out.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_seven_out.Speed = GPIO_SPEED_FREQ_10MHZ;
    gpio_seven_out.Pin = seven_segment->Pins;
    Init_GPIO(seven_segment->Port,&gpio_seven_out);  
    //Test
    uint32_t io_current = 0;
    uint32_t io_position = 0;
    uint32_t start_pin_index = 0;
    for(uint16_t pos; pos <=  GPIO_PIN_NUMBER ; pos++)
    {
        io_position = 1 << pos;
        io_current = (uint32_t)seven_segment->Pins & io_position;
        if(io_position == io_current)
        {
            start_pin_index = io_position;
            break;
        }
    }
    numbers[0]= (io_position << 0)|(io_position << 1)|(io_position << 2)|(io_position << 3)|(io_position << 4)|(io_position << 5);
    numbers[1]= (io_position << 1)|(io_position << 2);
    numbers[2]= (io_position << 0)|(io_position << 1)|(io_position << 6)|(io_position << 4)|(io_position << 3);
    numbers[3]= (io_position << 0)|(io_position << 1)|(io_position << 6)|(io_position << 2)|(io_position << 3);
    numbers[4]= (io_position << 5)|(io_position << 6)|(io_position << 1)|(io_position << 2);
    numbers[5]= (io_position << 0)|(io_position << 5)|(io_position << 6)|(io_position << 2)|(io_position << 3);
    numbers[6]= (io_position << 0)|(io_position << 5)|(io_position << 6)|(io_position << 4)|(io_position << 3)|(io_position << 2);
    numbers[7]= (io_position << 0)|(io_position << 1)|(io_position << 2);
    numbers[8]= (io_position << 0)|(io_position << 1)|(io_position << 2)|(io_position << 3)|(io_position << 4)|(io_position << 5)|(io_position << 6);
    numbers[9]= (io_position << 0)|(io_position << 1)|(io_position << 2)|(io_position << 3)|(io_position << 5)|(io_position << 6);


}

/**
 * @brief To print numbers on seven segment
 * @param[in] seven_segment The seven_segment data structure containing the port and pins to be configured
 * @param index The number to be printed
 */
void Display_seven_segment(St_7_segment *seven_segment, uint8_t index)
{
    uint32_t temp = seven_segment->Port->GPIO_ODR;
    temp &= ~(seven_segment->Pins);
    temp |= numbers[index];
    Set_GPIO_Value(seven_segment->Port,temp);
}