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
	int num1; // declertion and definition of a character array
	printf("Enter a number :");
	fflush(stdin); fflush(stdout);
	scanf("%d",&num1);
	fun(num1);
	return 0;

}

void fun(int _num1)
{
	int max=0,prev_max=0;
	for(int i=0;i<8*sizeof(_num1);i++)
	{
		if(_num1&(1<<i))
		{
			max++;
		}else
		{
			if(max>prev_max)
				prev_max=max;
			max=0;
		}
	}
	printf("%d",prev_max);
}
