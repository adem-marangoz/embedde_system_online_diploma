/*
 * FIFO.c
 *
 *  Created on: Dec 18, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */


#include "Queue_RTOS.h"


FIFO_Status FIFO_init(FIFO_Buf_t *_P_QUEUE_RTOS,Task_Pointer *_array,unsigned char length)
{
	if(!_P_QUEUE_RTOS || !_array)
	{
		return FIFO_Null;
	}
	_P_QUEUE_RTOS->base=_array;
	_P_QUEUE_RTOS->tail=_array;
	_P_QUEUE_RTOS->head=_array;
	_P_QUEUE_RTOS->length=length;
	_P_QUEUE_RTOS->counter=0;


	return FIFO_no_Error;
}

FIFO_Status FIFO_push(FIFO_Buf_t *_P_QUEUE_RTOS,Task_Pointer value)
{

	/* _P_QUEUE_RTOS null*/

	if (!_P_QUEUE_RTOS->base || !_P_QUEUE_RTOS->length)
		return FIFO_Null;
	/*_P_QUEUE_RTOS is full*/

	/* _P_QUEUE_RTOS full */
	if ((_P_QUEUE_RTOS->head == _P_QUEUE_RTOS->tail) && (_P_QUEUE_RTOS->counter == _P_QUEUE_RTOS->length))
		return FIFO_full;

	*(_P_QUEUE_RTOS->tail) = value;
	_P_QUEUE_RTOS->counter++;

	/*for circular _P_QUEUE_RTOS again */

	/* circular enqueue */
	if (_P_QUEUE_RTOS->tail == (((unsigned int)_P_QUEUE_RTOS->base + (4*_P_QUEUE_RTOS->length )) - 4 ))
		_P_QUEUE_RTOS->tail = _P_QUEUE_RTOS->base;
	else
		_P_QUEUE_RTOS->tail++;

}

FIFO_Status FIFO_pop(FIFO_Buf_t *_P_QUEUE_RTOS, Task_Pointer *value)
{
		/* check _P_QUEUE_RTOS valid */
	if (!_P_QUEUE_RTOS->base || !_P_QUEUE_RTOS->length)
		return FIFO_Null;

	/* _P_QUEUE_RTOS empty */
	if (_P_QUEUE_RTOS->head == _P_QUEUE_RTOS->tail)
		return FIFO_emypt;


	*value = *(_P_QUEUE_RTOS->head);
	_P_QUEUE_RTOS->counter--;

	/* circular dequeue */
	if (_P_QUEUE_RTOS->head == (((unsigned int)_P_QUEUE_RTOS->base + (4*_P_QUEUE_RTOS->length )) - 4 ))
		_P_QUEUE_RTOS->head = _P_QUEUE_RTOS->base;
	else
		_P_QUEUE_RTOS->head++;

	return FIFO_no_Error;

}

FIFO_Status FIFO_is_full(FIFO_Buf_t *_P_QUEUE_RTOS)
{
	if(!_P_QUEUE_RTOS->head || !_P_QUEUE_RTOS->base || !_P_QUEUE_RTOS->tail)
		return FIFO_Null;
	if(_P_QUEUE_RTOS->counter == _P_QUEUE_RTOS->length)
		return FIFO_full;

	return FIFO_no_Error;
}

FIFO_Status FIFO_is_empty(FIFO_Buf_t *_P_QUEUE_RTOS)
{
	if(_P_QUEUE_RTOS->counter==0)
	{
		return FIFO_emypt;
	}
	return FIFO_not_empty;
}

void FIFO_print(FIFO_Buf_t *_P_QUEUE_RTOS)
{
	for(int i=0;i<_P_QUEUE_RTOS->length;i++)
	{
	}
}
