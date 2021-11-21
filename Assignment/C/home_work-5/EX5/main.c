/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include "string.h"
#define cal_area_circle(x) 3.14*x*x


int main()
{
	float r;
	printf("Enter the radius: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&r);
	printf("Area= %0.2f",cal_area_circle(r));
	return 0;
}

