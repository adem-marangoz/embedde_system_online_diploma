#ifndef EXTI_H_
#define EXTI_H_

#include "Common.h"

#define EXTI_Mask                   (0x80)
#define EXTI_2_Mask                 (0x82)


#define Enable_EXTI_0()             SET_BIT(GICR,0x40)
#define Enable_EXTI_1()             SET_BIT(GICR,0x80)
#define Enable_EXTI_2()             SET_BIT(GICR,0x20)

#define Disable_EXTI_0()            CLEAR_BIT(GICR,0x40)
#define Disable_EXTI_1()            CLEAR_BIT(GICR,0x80)
#define Disable_EXTI_2()            CLEAR_BIT(GICR,0x20)

#define Enable_Global_EXTI()        SET_BIT(SREG,0x80)
#define Disable_Global_EXTI()       CLEAR_BIT(SREG,0x80)



#endif