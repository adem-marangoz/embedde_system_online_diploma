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
	printf("Enter an alphabet: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&num);
	if(num=='a'||num=='e'||num=='i'||num=='o'||num=='u')
		printf("%c is a vowel",num);
	else
		printf("%c is a consonant",num);

	return 0;
}
