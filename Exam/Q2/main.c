/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include "string.h"
#include <math.h>
#include "stdlib.h"

void fun(int num);
int main()
{
	int num;

	printf("input :");
	fflush(stdin); fflush(stdout);
	scanf("%d",&num);
	fun(num);
	return 0;
}
void fun(int num)
{
	double temp,sqrt;
	sqrt=num/2;
	temp=0;
	while(sqrt!=temp)
	{
		temp=sqrt;
		sqrt=(num/temp+temp)/2;
	}
	printf("output: %lf",sqrt);
}
