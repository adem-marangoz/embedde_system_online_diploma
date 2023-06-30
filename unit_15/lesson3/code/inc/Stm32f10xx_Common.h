/**
 * @file Stm32f10xx_Common.h
 * @author Adem marangoz (adem.marangoz95@gmail.com)
 * @brief This Header file is common in multi files
 * @version 0.1
 * @date 2022-05-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#define __IO              volatile           

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define AHB_Bus     0x40018000

#define __weak   __attribute__((weak))

#define UNUSED(X) (void)X      /* To avoid gcc/g++ warnings */

#define Enable_Print_By_Uart      0x01
#define Disable_Print_By_Uart     0x02
#define Enable_Hal                0x01
#define Disable_Hal               0x02

#define Print_By_Uart             (Enable_Print_By_Uart)
#define Use_Hal                   (Disable_Hal)

// #define BL_DEBUG_UART                &huart2 
#define BL_DEBUG_UART                             // Write Uart structure
typedef enum
{
  Ok = 0x00U,
  Not_Ok = 0x01U,
  Busy = 0x02U,
  TimeOut = 0x03U
} State_Typedef;

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr If expr is false, it calls assert_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
  //#define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  //void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */


// void assert_failed(uint8_t *file, uint32_t line)
// {
//   /* USER CODE BEGIN 6 */
//   /* User can add his own implementation to report the file name and line number,
//      ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
//   /* USER CODE END 6 */
// }

//____________________________ Global Functions __________________________________

void clear_buffer(uint8_t *str, uint16_t start_add, uint16_t end_add, uint8_t ch);
uint32_t add_unsigned_int_to_str(char *str, uint32_t num);
uint8_t strcmp_(uint8_t *src, uint8_t *des, uint32_t len);
// void Print_With_Uart(char *format, ...);
//==============================================================================
#endif