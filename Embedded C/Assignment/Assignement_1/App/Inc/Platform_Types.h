
/**
 * @brief Variables Types
 * @author Adem Alnajjar
 */


#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_



#include <stdbool.h>
#include <stdint.h>



#ifndef _Bool
#define _Boll unsinged char
#endif


#define CPU_TYPE                    CPU_TYPE_32
#define CPU_BIT_ORDER               MSB_FIRST
#define CPU_BYTE_ORDER              HIGH_BYTE_FIRST
        
#ifndef FALSE       
#define FALSE                       (boolean)false
#endif      
        
#ifndef TRUE        
#define TRUE                        (boolena)true
#endif

/*Variable Type*/
typedef int8_t                      sint8;
typedef uint8_t                     uint8;
typedef int16_t                     sint16;
typedef uint16_t                    uint16;
typedef uint32_t                    sint32;
typedef int32_t                     uint32;
typedef uint64_t                    uint64;
typedef int64_t                     sint64;
typedef float                       sfloat32;
typedef double                      sdouble64;




/*Volatile Variable Type*/
typedef volatile  int8_t            vsint8;
typedef volatile uint8_t            vuint8;
typedef volatile int16_t            vsint16;
typedef volatile uint16_t           vuint16;
typedef volatile uint32_t           vuint32;
typedef volatile int32_t            vsint32;
typedef volatile uint64_t           vuint64;
typedef volatile int64_t            vsint64;
typedef volatile float              vsfloat32;
typedef volatile double             vsdouble64;



#endif