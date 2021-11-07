/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include "string.h"

int main()
{
	float num;
	printf("enter a number: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&num);
	if(num>0.0f)
		printf("%f is positive",num);
	else
		printf("you enteredd zero.");
}
