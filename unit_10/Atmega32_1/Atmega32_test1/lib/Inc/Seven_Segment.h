#ifndef SEVEN_SEGMENT
#define SEVEN_SEGMENT

#include "GPIO.h"
#include "Common.h"

#define Num_1   PIN_1|PIN_2
#define Num_2   PIN_0|PIN_1|PIN_6|PIN_4|PIN_3
#define Num_3   PIN_0|PIN_1|PIN_6|PIN_2|PIN_3
#define Num_4   PIN_5|PIN_6|PIN_1|PIN_2
#define Num_5   PIN_0|PIN_5|PIN_6|PIN_2|PIN_3
#define Num_6   PIN_0|PIN_5|PIN_6|PIN_4|PIN_3|PIN_2
#define Num_7   PIN_0|PIN_1|PIN_2
#define Num_8   PIN_0|PIN_1|PIN_2|PIN_3|PIN_4|PIN_5|PIN_6
#define Num_9   PIN_0|PIN_1|PIN_2|PIN_3|PIN_5|PIN_6
#define Num_0   PIN_0|PIN_1|PIN_2|PIN_3|PIN_4|PIN_5

uint8_t numbers[10] = {Num_0,Num_1,Num_2,Num_3,Num_4,Num_5,Num_6,Num_7,Num_8,Num_9};



#endif