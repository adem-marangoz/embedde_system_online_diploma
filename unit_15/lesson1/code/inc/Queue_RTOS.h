/*
 * FIFO.h
 *
 *  Created on: Dec 18, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#ifndef QUEUE_RTOS_H_
#define QUEUE_RTOS_H_

#include <stdio.h>

//------------------------------- Include Files --------------------------------
#include "Scheduler.h"
//==============================================================================

#define Task_Pointer Scheduler_Typedef*
typedef struct
{
	Task_Pointer* base;
	Task_Pointer* till;
	Task_Pointer* head;
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


FIFO_Status FIFO_init(FIFO_Buf_t *_P_QUEUE_RTOS, Task_Pointer *_array, unsigned char length);
FIFO_Status FIFO_push(FIFO_Buf_t *_P_QUEUE_RTOS, Task_Pointer value);
FIFO_Status FIFO_pop(FIFO_Buf_t *_P_QUEUE_RTOS, Task_Pointer *value);
FIFO_Status FIFO_is_full(FIFO_Buf_t *_P_QUEUE_RTOS);
FIFO_Status FIFO_is_empty(FIFO_Buf_t *_P_QUEUE_RTOS);
void FIFO_print(FIFO_Buf_t *_P_QUEUE_RTOS);

#endif /* FIFO_H_ */
