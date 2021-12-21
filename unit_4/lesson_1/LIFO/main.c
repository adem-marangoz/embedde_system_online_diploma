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

	char _array[4];
	char *ptr=(char*)malloc(sizeof(4));
	char temp=0;
	LIFO_Buf_t _static_array, _dynamic_array;
	LIFO_Init(&_dynamic_array,ptr,4);
	LIFO_Init(&_static_array,_array,4);
	Cprint("\nPush item in static array: ");
	for(unsigned char i=0;i<sizeof(_array);i++)
	{
		LIFO_Push(&_static_array,i*2);
	}
	Cprint("\nPop item in static array: ");
	for (unsigned char i=0;i<sizeof(_array);i++)
	{
		LIFO_Pop(&_static_array,&temp);

	}
	Cprint("\nPush item in dynamic array: ");
	for(unsigned char i=0;i<sizeof(_array);i++)
	{
		LIFO_Push(&_dynamic_array,i);
	}
	Cprint("\nPop item in dynamic array: ");
	for (unsigned char i=0;i<sizeof(_array);i++)
	{
		LIFO_Pop(&_dynamic_array,&temp);

	}
	return 0;
}

































