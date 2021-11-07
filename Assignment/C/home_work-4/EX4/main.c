/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include "string.h"
#include <math.h>
void power_of_number(int _num1,int _num2);

int main()
{
	int num1,num2;
	printf("Enter base number: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&num1);
	fflush(stdin); fflush(stdout);
	printf("Enter power number(positive integer): ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&num2);
	power_of_number(num1,num2);
	return 0;
}

void power_of_number(int _num1,int _num2)
{
	printf("%d^%d = %d",_num1,_num2,(int)pow(_num1,_num2));
}
