#include "Stm32f10xx_RCC.h"


/*=============================================================================================
ooooo         ooooooo     oooooooo8     o      ooooo       
 888        o888   888o o888     88    888      888        
 888        888     888 888           8  88     888        
 888      o 888o   o888 888o     oo  8oooo88    888      o 
o888ooooo88   88ooo88    888oooo88 o88o  o888o o888ooooo88
ooooo  oooo  o      oooooooooo  ooooo oooooooooo      o      ooooo       ooooooooooo 
 888    88  888      888    888  888   888    888    888      888         888    88  
  888  88  8  88     888oooo88   888   888oooo88    8  88     888         888ooo8    
   88888  8oooo88    888  88o    888   888    888  8oooo88    888      o  888    oo  
    888 o88o  o888o o888o  88o8 o888o o888ooo888 o88o  o888o o888ooooo88 o888ooo8888 
*/
const static uint8_t APB_Prescaler[8] = {0, 0, 0, 0, 2, 4, 8, 16};
const static uint16_t AHB_Prescaler[9] = {0, 2, 4, 8, 16, 64, 128, 256, 512};
const static uint8_t PREDIV[16] = {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
const static uint8_t PLLMUL[8] = {0, 0, 4, 5, 6, 7, 8, 9};
const static uint8_t PLLMUL2[15] = {0, 0, 0, 0, 0, 8, 9, 10, 11, 12, 13, 14, 0, 16, 20};
static uint32_t HSE_Freq = 0;
//==============================================================================================


/**
 * @brief   used to get the SYSCLK frequency
 * @return  uint32_t: SYSCLK  
 */
uint32_t Get_Systick_Freq()
{
    uint8_t _SW = (RCC->RCC_CFGR >> 2) & 0x3;
    uint32_t CLK_Freq = 0;
    switch (_SW)
    {
        case 0: //HSI oscillator used as system clock
            CLK_Freq = HSI_Freq;
            break;
        case 1: //HSE oscillator used as system clock
            CLK_Freq = HSE_Freq;
            break;
        case 2: //PLL used as system clock
            //Bit 16 PLLSRC: PLL entry clock source
            if(RCC->RCC_CFGR >> 16 & 0x1)
            {
                //Bit 16 PREDIV1SRC: PREDIV1 entry clock source
                if(RCC->RCC_CFGR2 >> 16 & 0x1)
                {
                    //Bits 7:4 PREDIV2[3:0]: PREDIV2 division factor
                    CLK_Freq = HSE_Freq >> PREDIV[(RCC->RCC_CFGR2 >> 4) & 0xF];
                    //Bits 11:8 PLL2MUL[3:0]: PLL2 Multiplication Factor
                    CLK_Freq = CLK_Freq >> PLLMUL2[(RCC->RCC_CFGR2 >> 8) & 0xF];
                }else
                {
                    CLK_Freq = HSE_Freq;
                }
                //Bits 3:0 PREDIV1[3:0]: PREDIV1 division factor
                CLK_Freq = (CLK_Freq >> PREDIV[RCC->RCC_CFGR2 & 0xF]);
            }
            else
            {
                CLK_Freq = HSI_Freq/2;
            }

            //Bits 21:18 PLLMUL[3:0]: PLL multiplication factor
            CLK_Freq = CLK_Freq >> PLLMUL[RCC->RCC_CFGR >> 18 & 0xF];
            break;
        default: //11: Not applicable
            CLK_Freq = 0;
            break;
    } 
    return CLK_Freq;
}

/**
 * @brief   used to get the AHB frequency
 * @return  uint32_t : AHB frequency
 */
uint32_t Get_HCLK_Freq()
{
    //Bits 7:4 HPRE[3:0]: AHB prescaler
    return (Get_Systick_Freq() >> AHB_Prescaler[(RCC->RCC_CFGR >> 4) & 0xF]);
}

/**
 * @brief   used to get the APB1 frequency
 * @return  uint32_t : APB1 frequency 
 */
uint32_t Get_APB1_Freq()
{
    //Bits 13:11 PPRE2[2:0]: APB high-speed prescaler (APB2)
    return (Get_HCLK_Freq() >> (APB_Prescaler[(RCC->RCC_CFGR >> 11) & 0x7]));
}

/**
 * @brief   used to get the APB2 frequency
 * @return  uint32_t : APB2 frequency 
 */
uint32_t Get_APB2_Freq()
{
    //Bits 10:8 PPRE1[2:0]: APB Low-speed prescaler (APB1)
    return (Get_HCLK_Freq() >> (APB_Prescaler[(RCC->RCC_CFGR >> 8) & 0x7]));
}

/**
 * @brief       used to set the external clock frequency
 * @param[in]   _HSE_Freq : external clock frequency 
 * @param[out]  uint8_t : 1 = Succeeded
 *                        0 = Failed 
 */
uint8_t Set_HSE_CLK_Freq(uint32_t _HSE_Freq)
{
    if(_HSE_Freq > HSE_MIN && _HSE_Freq < HSE_MIN){HSE_Freq = _HSE_Freq; return 1;}
    return 0;
    
}