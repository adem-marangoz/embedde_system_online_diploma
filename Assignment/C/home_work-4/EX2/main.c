/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include "string.h"

void factorial_fun(int _num1);

int main()
{
	int num1;
	printf("Enter an positive integer :");
	fflush(stdin); fflush(stdout);
	scanf("%d",&num1);
	factorial_fun(num1);
	return 0;
}

void factorial_fun(int _num1)
{
	int base=1,nn=_num1;
	for(;_num1;_num1--)
	{
		base*=_num1;
	}
	printf("Factorial of %d = %d",nn,base);
}
