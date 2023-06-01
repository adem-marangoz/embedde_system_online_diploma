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

//------------------------------ Generic Objects -------------------------------

#define Task_Pointer Scheduler_Typedef*

/**
 * @brief  Buffer control structure
 */
typedef struct
{
	Task_Pointer* base;
	Task_Pointer* tail;
	Task_Pointer* head;
	unsigned int counter;
	unsigned int length;
	unsigned int Task_counter;
}FIFO_Buf_t;

/**
 * @brief State of Buffer
 */
typedef enum
{
	FIFO_no_Error,
	FIFO_full,
	FIFO_not_full,
	FIFO_emypt,
	FIFO_Null,
	FIFO_not_empty
}FIFO_Status;
//==============================================================================


//------------------------------ Global Functions ------------------------------
FIFO_Status FIFO_init(FIFO_Buf_t *_P_QUEUE_RTOS, Task_Pointer *_array, unsigned int length);
FIFO_Status FIFO_push(FIFO_Buf_t *_P_QUEUE_RTOS, Task_Pointer value);
FIFO_Status FIFO_pop(FIFO_Buf_t *_P_QUEUE_RTOS, Task_Pointer *value);
FIFO_Status FIFO_Clear(FIFO_Buf_t *_P_QUEUE_RTOS);
FIFO_Status FIFO_is_full(FIFO_Buf_t *_P_QUEUE_RTOS);
FIFO_Status FIFO_is_empty(FIFO_Buf_t *_P_QUEUE_RTOS);
void FIFO_print(FIFO_Buf_t *_P_QUEUE_RTOS);
//==============================================================================


#endif /* FIFO_H_ */
