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
	float num[4];
	num[3]=0.0;
	printf("Enter three numbers: ");
	fflush(stdin); fflush(stdout);
	for(int i=0;i<3;i++)
	{
		scanf("%f",&num[i]);
	}
	for(int i=0;i<sizeof(num);i++)
	{
		if(num[i]>num[3])
			num[3]=num[i];
	}
	printf("Largest number %f",num[3]);
	return 0;
}
