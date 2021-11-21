/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include "string.h"

int fun();

int main()
{
	int sum=fun();
	printf("%d",sum);
	return 0;
}

int fun()
{
	static sum=0;
	static num1=100;
	sum=sum+num1;
	if(num1)
		fun(--num1);
	return sum;
}
