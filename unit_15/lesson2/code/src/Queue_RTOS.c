/**
 * @file Queue_RTOS.c
 * @author Adem Marangoz (adem.marangoz95@gmail.com)
 * @brief Circular FIFO Driver
 * @version 0.1
 * @date 2023-05-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

//------------------------------- Include Files --------------------------------
#include "Queue_RTOS.h"
//==============================================================================


//------------------------------ Global Functions ------------------------------

/**
 * @brief initialize The FIFO Buffer
 * @param _P_QUEUE_RTOS Buffer control structure
 * @param _array Buffer start pointer
 * @param length The number of buffer elements
 * @return FIFO_Status 	: FIFO_no_Error
 * 						: FIFO_Null
 */
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


/**
 * @brief  Push value into a buffer
 * @param _P_QUEUE_RTOS Buffer control structure
 * @param value This value to put into a buffer
 * @return FIFO_Status 	: FIFO_no_Error
 * 						: FIFO_Null 
 */
FIFO_Status FIFO_push(FIFO_Buf_t *_P_QUEUE_RTOS,Task_Pointer value)
{

	/* _P_QUEUE_RTOS null*/

	if (!_P_QUEUE_RTOS->base || !_P_QUEUE_RTOS->length)
		return FIFO_Null;
	/*_P_QUEUE_RTOS is full*/

	/* _P_QUEUE_RTOS full */
	if ((unsigned int)(_P_QUEUE_RTOS->head == _P_QUEUE_RTOS->tail) && (_P_QUEUE_RTOS->counter == _P_QUEUE_RTOS->length))
		return FIFO_full;

	*(_P_QUEUE_RTOS->tail) = value;
	_P_QUEUE_RTOS->counter++;

	/*for circular _P_QUEUE_RTOS again */

	/* circular enqueue */
	if ((unsigned int)(_P_QUEUE_RTOS->tail) == (((unsigned int)_P_QUEUE_RTOS->base + (4*_P_QUEUE_RTOS->length )) - 4 ))
		_P_QUEUE_RTOS->tail = _P_QUEUE_RTOS->base;
	else
		_P_QUEUE_RTOS->tail++;

}


/**
 * @brief Pop value form a buffer
 * @param _P_QUEUE_RTOS Buffer control structure
 * @param value This value to put into a buffer
 * @return FIFO_Status 	: FIFO_no_Error
 * 						: FIFO_Null 
 */
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
	if ((unsigned int)(_P_QUEUE_RTOS->head) == (((unsigned int)_P_QUEUE_RTOS->base + (4*_P_QUEUE_RTOS->length )) - 4 ))
		_P_QUEUE_RTOS->head = _P_QUEUE_RTOS->base;
	else
		_P_QUEUE_RTOS->head++;

	return FIFO_no_Error;

}


/**
 * @brief Check if Buffer is Full  
 * @param _P_QUEUE_RTOS Buffer control structure
 * @return FIFO_Status 	: FIFO_no_Error
 * 						: FIFO_Null 
 */
FIFO_Status FIFO_is_full(FIFO_Buf_t *_P_QUEUE_RTOS)
{
	if(!_P_QUEUE_RTOS->head || !_P_QUEUE_RTOS->base || !_P_QUEUE_RTOS->tail)
		return FIFO_Null;
	if(_P_QUEUE_RTOS->counter == _P_QUEUE_RTOS->length)
		return FIFO_full;

	return FIFO_no_Error;
}


/**
 * @brief Check if Buffer is Empty
 * @param _P_QUEUE_RTOS Buffer control structure
 * @return FIFO_Status 	: FIFO_no_Error
 * 						: FIFO_Null 
 */
FIFO_Status FIFO_is_empty(FIFO_Buf_t *_P_QUEUE_RTOS)
{
	if(_P_QUEUE_RTOS->counter==0)
	{
		return FIFO_emypt;
	}
	return FIFO_not_empty;
}


/**
 * @brief 
 * @param _P_QUEUE_RTOS 
 */
void FIFO_print(FIFO_Buf_t *_P_QUEUE_RTOS)
{
	for(int i=0;i<_P_QUEUE_RTOS->length;i++)
	{
	}
}

//==============================================================================