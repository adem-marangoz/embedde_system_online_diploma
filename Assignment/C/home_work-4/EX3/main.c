/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include "string.h"

void reverse_sentence(char sente[]);

int main()
{
	char array[100];
	printf("Enter a sentence :");
	fflush(stdin); fflush(stdout);
	gets(array);
	reverse_sentence(array);
	return 0;
}

void reverse_sentence(char sente[])
{
	for(int i=strlen(sente)-1;i>=0;i--)
	{
		printf("%c",sente[i]);
	}
}
