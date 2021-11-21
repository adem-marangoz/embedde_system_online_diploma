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
	int num1;
	printf("input :");
	fflush(stdin); fflush(stdout);
	scanf("%d",&num1);
	fun(num1);
	return 0;
}
void fun(int num)
{
	int kal,sum=0;
	do
	{
		kal=num%10;
		num/=10;
		sum=sum+kal;
	}while(num>0);
	printf("output : %d",sum);
}
