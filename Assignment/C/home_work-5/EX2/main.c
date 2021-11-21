/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include "string.h"

struct Distance
{
	int feet;
	float inch;
}d1,d2,sum;


int main()
{
	printf("Enter information for 1st distance\n");
	printf("Enter feet: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&d1.feet);
	fflush(stdin); fflush(stdout);
	printf("Enter inch: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&d1.inch);
	fflush(stdin); fflush(stdout);
	printf("\nEnter information for 2nd distance\n");
	printf("Enter feet: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&d2.feet);
	fflush(stdin); fflush(stdout);
	printf("Enter inch: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&d2.inch);
	fflush(stdin); fflush(stdout);
	sum.feet=d1.feet +d2.feet;
	sum.inch=d1.inch +d2.inch;
	if(sum.inch>12.0)
	{
		sum.inch=sum.inch-12.0;
		++sum.feet;
	}
	printf("\nSum of distance=%d\' - %.1f\"",sum.feet,sum.inch);
	return 0;
}
