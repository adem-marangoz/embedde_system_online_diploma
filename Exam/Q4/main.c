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
	int num;
	printf("enter a number: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&num);
	fun(num);
	return 0;
}

void fun(int _num1)
{
	int temp,rev=0;
	do
	{
		temp=_num1%10;
		_num1/=10;
		rev=10*rev+temp;
	}while(_num1);
	printf("the revers digit :%d",rev);
}
