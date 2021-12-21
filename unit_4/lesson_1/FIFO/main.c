/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LIFO.h"
#include "FIFO.h"


int main()
{
	unsigned char _s_array[5],_temp;
	unsigned char *_d_array_ptr=(unsigned char*)malloc(5*sizeof(unsigned char));
	FIFO_Buf_t _s_fifo,_d_fifo;
	FIFO_init(&_s_fifo,_s_array,sizeof(_s_array));
	FIFO_init(&_d_fifo,_d_array_ptr,sizeof(_d_array_ptr));
	Cprint("\nPush item to FIFO buffer : ");
	for(int i=0;i<sizeof(_s_array)-1;i++)
	{
		FIFO_push(&_s_fifo,i+2);
	}
	Cprint("\n");
	FIFO_is_full(&_s_fifo);
	Cprint("\nPop item from FIFO buffer: ");
	for(int i=0;i<sizeof(_s_array);i++)
	{
		FIFO_pop(&_s_fifo,&_temp);
	}
	FIFO_is_empty(&_s_fifo);
	Cprint("\n");

	return 0;
}
































//char _array[4];
//	char *ptr=(char*)malloc(sizeof(4));
//	char temp=0;
//	LIFO_Buf_t _static_array, _dynamic_array;
//	LIFO_Init(&_dynamic_array,ptr,4);
//	LIFO_Init(&_static_array,_array,4);
//	Cprint("\nPush item in static array: ");
//	for(unsigned char i=0;i<sizeof(_array);i++)
//	{
//		LIFO_Push(&_static_array,i*2);
//	}
//	Cprint("\nPop item in static array: ");
//	for (unsigned char i=0;i<sizeof(_array);i++)
//	{
//		LIFO_Pop(&_static_array,&temp);
//
//	}
//	Cprint("\nPush item in dynamic array: ");
//	for(unsigned char i=0;i<sizeof(_array);i++)
//	{
//		LIFO_Push(&_dynamic_array,i);
//	}
//	Cprint("\nPop item in dynamic array: ");
//	for (unsigned char i=0;i<sizeof(_array);i++)
//	{
//		LIFO_Pop(&_dynamic_array,&temp);
//
//	}
