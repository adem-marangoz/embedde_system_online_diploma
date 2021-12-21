/*
 * LIFO.h
 *
 *  Created on: Dec 17, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#ifndef LIFO_H_
#define LIFO_H_


#include <stdio.h>

#define Cprint(...)	{fflush(stdin);\
					fflush(stdout);\
					printf(__VA_ARGS__);\
					fflush(stdin);\
					fflush(stdout);\
					}

typedef struct
{
	unsigned int length;
	unsigned int count;
	unsigned char* base;
	unsigned char* head;
}LIFO_Buf_t;


typedef enum
{
	LIFO_No_Error,
	LIFO_Full,
	LIFO_not_Full,
	LIFO_empty,
	LIFO_not_empty,
	LIFO_Null
}LIFO_Status;

LIFO_Status LIFO_Init(LIFO_Buf_t *_P_LIFO_buffer,unsigned char* _P_Array_buf,unsigned char _length);
LIFO_Status LIFO_Push(LIFO_Buf_t *_P_LIFO_buffer, char _value);
LIFO_Status LIFO_Pop(LIFO_Buf_t *_LIFO_buffer,char *_value);
LIFO_Status LIFO_Is_full(LIFO_Buf_t *_LIFO_buffer);
LIFO_Status LIFO_Is_empty(LIFO_Buf_t *_LIFO_buffer);




#endif /* LIFO_H_ */
