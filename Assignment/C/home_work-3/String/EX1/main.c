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
	printf("Enter a character to find frequency: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&chr);
	for (int i=0;i<strlen(str);i++)
	{
		if(str[i]==chr)
		{
			n++;
		}
	}
	printf("Frequency of %c =%d",chr,n);
	return 0;
}
