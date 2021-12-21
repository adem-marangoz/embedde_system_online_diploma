/*
 * LIFO.c
 *
 *  Created on: Dec 17, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */


#include "LIFO.h"



LIFO_Status LIFO_Init(LIFO_Buf_t *_P_LIFO_buffer,unsigned char* _P_Array_buf,unsigned char _length)
{
	if(!_P_LIFO_buffer || !_P_Array_buf)
	{
		Cprint("LIFO or Array is Null\n");
		return LIFO_Null;
	}

	_P_LIFO_buffer->base=(unsigned char*)_P_Array_buf;
	_P_LIFO_buffer->head=(unsigned char*)_P_Array_buf;
	_P_LIFO_buffer->length=_length;
	_P_LIFO_buffer->count=0;
	Cprint("LIFO is initalized \n");
	return LIFO_No_Error;
}

LIFO_Status LIFO_Push(LIFO_Buf_t *_P_LIFO_buffer, char _value)
{
	/*Check if LIFO is Initialization*/
	if(!_P_LIFO_buffer)
	{
		Cprint("LIFO or Array is Null\n");
		return LIFO_Null;
	}


	/*Check if Array or Buffer full*/
	if(_P_LIFO_buffer->head==(_P_LIFO_buffer->base +_P_LIFO_buffer->length))
		return LIFO_Full;

	/*Push the item to Araay*/
	*(_P_LIFO_buffer->head)=_value;
	Cprint("%d ",*(_P_LIFO_buffer->head));
	(_P_LIFO_buffer->head)++;
	_P_LIFO_buffer->count++;

	return LIFO_No_Error;
}


LIFO_Status LIFO_Pop(LIFO_Buf_t *_P_LIFO_buffer, char *_value)
{
	/*Check if LIFO is Initialization*/
	if(!_P_LIFO_buffer)
	{
		Cprint("LIFO or Array is Null ");
		return LIFO_Null;
	}


	/*Check if before Add item to Array*/
	if(_P_LIFO_buffer->base==_P_LIFO_buffer->head)
	{
		return LIFO_empty;
	}

	(_P_LIFO_buffer->head)--;
	_P_LIFO_buffer->count--;
	*_value=*(_P_LIFO_buffer->head);
	Cprint("%d ",*(_P_LIFO_buffer->head));

	return LIFO_No_Error;

}


LIFO_Status LIFO_Is_full(LIFO_Buf_t *_P_LIFO_buffer)
{
	if(_P_LIFO_buffer->head==_P_LIFO_buffer->base + _P_LIFO_buffer->length)
	{
		Cprint("LIFO is full ");
		return LIFO_Full;
	}
	Cprint("LIFO is not full ");
	return LIFO_not_Full;
}


LIFO_Status LIFO_Is_empty(LIFO_Buf_t *_P_LIFO_buffer)
{
	if(_P_LIFO_buffer->base==_P_LIFO_buffer->head)
	{
		Cprint("LIFO is empty ");
		return LIFO_empty;
	}
	Cprint("LIFO is not empty ");
	return LIFO_not_empty;
}

