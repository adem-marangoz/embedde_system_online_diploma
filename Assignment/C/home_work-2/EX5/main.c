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
	char num;
	printf("enter a character: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&num);
	if((num>=65 && num<=90)||(num>=97 && num<=122))
		printf("%c is an alphabet",num);
	else
		printf("%c is not an alphabet",num);
}
