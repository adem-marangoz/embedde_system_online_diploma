/*
 * FIFO.c
 *
 *  Created on: Dec 18, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */


#include "FIFO.h"


FIFO_Status FIFO_init(FIFO_Buf_t *_p_fifo_buf,unsigned char *_array,unsigned char length)
{
	if(!_p_fifo_buf || !_array)
	{
		Cprint("Array or Fifo is Null\n");
		return FIFO_Null;
	}
	_p_fifo_buf->base=_array;
	_p_fifo_buf->till=_array;
	_p_fifo_buf->head=_array;
	_p_fifo_buf->length=length;
	_p_fifo_buf->counter=0;

	Cprint("FIFO Buffer is initialized\n");

	return FIFO_no_Error;
}

FIFO_Status FIFO_push(FIFO_Buf_t *_p_fifo_buf,unsigned char value)
{
	if(!_p_fifo_buf)
	{
		Cprint("Array or Fifo is Null\n");
		return FIFO_Null;
	}

	*(_p_fifo_buf->head)=value;*(_p_fifo_buf->head)=value;
	Cprint("%d ",*(_p_fifo_buf->head));

	if(_p_fifo_buf->counter>_p_fifo_buf->length)
	{
		_p_fifo_buf->head=_p_fifo_buf->base;
	}else
		(_p_fifo_buf->head)++;
	if(_p_fifo_buf->counter<_p_fifo_buf->length)
		_p_fifo_buf->counter++;
	return FIFO_no_Error;

}

FIFO_Status FIFO_pop(FIFO_Buf_t *_p_fifo_buf,unsigned char *value)
{
	if(!_p_fifo_buf)
	{
		Cprint("Array or Fifo is Null\n");
		return FIFO_Null;
	}
	if(_p_fifo_buf->counter)
	{
		*(value)=*(_p_fifo_buf->till);
		Cprint("%d ",*(_p_fifo_buf->till));
		if(_p_fifo_buf->till==_p_fifo_buf->base + _p_fifo_buf->length)
			_p_fifo_buf->till=_p_fifo_buf->base;
		else
			_p_fifo_buf->till++;
		_p_fifo_buf->counter--;
		return FIFO_no_Error;
	}
	return FIFO_emypt;


}

FIFO_Status FIFO_is_full(FIFO_Buf_t *_p_fifo_buf)
{
	if(_p_fifo_buf->counter>_p_fifo_buf->length-1)
	{
		Cprint("\nFIFO is full");
		return FIFO_full;
	}
	Cprint("\nFIFO is not full");
	return FIFO_not_full;
}

FIFO_Status FIFO_is_empty(FIFO_Buf_t *_p_fifo_buf)
{
	if(_p_fifo_buf->counter==0)
	{
		Cprint("\nFIFO is empty ");
		return FIFO_emypt;
	}
	Cprint("\nFIFO is not empty ");
	return FIFO_not_empty;
}

void FIFO_print(FIFO_Buf_t *_p_fifo_buf)
{
	Cprint("Display FIFO buffer: ");
	for(int i=0;i<_p_fifo_buf->length;i++)
	{
		Cprint("%d ",*(_p_fifo_buf->base + i));
	}
	Cprint("\n");
}
