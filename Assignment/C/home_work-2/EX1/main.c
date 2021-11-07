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
	int num;
	printf("Enter an integer you want to check: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&num);
	if(num%2)
		printf("%d is odd",num);
	else
		printf("%d is even",num);

	return 0;
}
