/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include "string.h"

void fun(int _num1);

int main()
{
	int x;
	printf("input:");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);
	fun(x);
	return 0;
}

void fun(int _num1)
{
	int size=8*sizeof(_num1);
	int binary=0;
	while(size)
	{
		if(_num1&(1<<size))
		{
			binary++;
		}
		size--;
	}
	printf("output :%d",binary);
}
