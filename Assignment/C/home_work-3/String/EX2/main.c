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
	char str[30],chr;
	int n=0;
	printf("Enter a string :");
	fflush(stdin); fflush(stdout);
	gets(str);
	fflush(stdin); fflush(stdout);

	for (int i=0;str[i]!=0;i++)
	{
		n++;
	}
	printf("Length of string : %d",n);
	return 0;
}
