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
	_P_QUEUE_RTOS->till=_array;
	_P_QUEUE_RTOS->head=_array;
	_P_QUEUE_RTOS->length=length;
	_P_QUEUE_RTOS->counter=0;


	return FIFO_no_Error;
}

FIFO_Status FIFO_push(FIFO_Buf_t *_P_QUEUE_RTOS,Task_Pointer value)
{
	if(!_P_QUEUE_RTOS)
	{
		return FIFO_Null;
	}

	*(_P_QUEUE_RTOS->head)=value;

	if(_P_QUEUE_RTOS->counter>_P_QUEUE_RTOS->length)
	{
		_P_QUEUE_RTOS->head=_P_QUEUE_RTOS->base;
	}else
		(_P_QUEUE_RTOS->head)++;
	if(_P_QUEUE_RTOS->counter<_P_QUEUE_RTOS->length)
		_P_QUEUE_RTOS->counter++;
	return FIFO_no_Error;

}

FIFO_Status FIFO_pop(FIFO_Buf_t *_P_QUEUE_RTOS, Task_Pointer *value)
{
	if(!_P_QUEUE_RTOS)
	{
		return FIFO_Null;
	}
	if(_P_QUEUE_RTOS->counter)
	{
		*(value)=*(_P_QUEUE_RTOS->till);
		if(_P_QUEUE_RTOS->till==_P_QUEUE_RTOS->base + _P_QUEUE_RTOS->length)
			_P_QUEUE_RTOS->till=_P_QUEUE_RTOS->base;
		else
			_P_QUEUE_RTOS->till++;
		_P_QUEUE_RTOS->counter--;
		return FIFO_no_Error;
	}
	return FIFO_emypt;


}

FIFO_Status FIFO_is_full(FIFO_Buf_t *_P_QUEUE_RTOS)
{
	if(_P_QUEUE_RTOS->counter>_P_QUEUE_RTOS->length-1)
	{
		return FIFO_full;
	}
	return FIFO_not_full;
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
