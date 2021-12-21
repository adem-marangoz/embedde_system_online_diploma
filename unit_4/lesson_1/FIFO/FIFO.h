/*
 * FIFO.h
 *
 *  Created on: Dec 18, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <stdio.h>

#define Cprint(...)	{fflush(stdin);\
					fflush(stdout);\
					printf(__VA_ARGS__);\
					fflush(stdin);\
					fflush(stdout);\
					}

typedef struct
{
	unsigned char* base;
	unsigned char* till;
	unsigned char* head;
	unsigned char counter;
	unsigned char length;
}FIFO_Buf_t;

typedef enum
{
	FIFO_full,
	FIFO_not_full,
	FIFO_emypt,
	FIFO_not_empty,
	FIFO_no_Error,
	FIFO_Null
}FIFO_Status;

FIFO_Status FIFO_init(FIFO_Buf_t *_p_fifo_buf,unsigned char *_array,unsigned char length);
FIFO_Status FIFO_push(FIFO_Buf_t *_p_fifo_buf,unsigned char value);
FIFO_Status FIFO_pop(FIFO_Buf_t *_p_fifo_buf,unsigned char *value);
FIFO_Status FIFO_is_full(FIFO_Buf_t *_p_fifo_buf);
FIFO_Status FIFO_is_empty(FIFO_Buf_t *_p_fifo_buf);
void FIFO_print(FIFO_Buf_t *_p_fifo_buf);

#endif /* FIFO_H_ */
