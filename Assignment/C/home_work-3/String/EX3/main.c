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
	int strlength;
	printf("Enter a string :");
	fflush(stdin); fflush(stdout);
	gets(str);
	strlength=strlen(str);
	for(int i=0;i<(strlength/2);i++)
	{
		chr=str[i];
		str[i]=str[strlength-i-1];
		str[strlength-1-i]=chr;
	}
	printf("Reverse string is : %s",str);
	return 0;
}
