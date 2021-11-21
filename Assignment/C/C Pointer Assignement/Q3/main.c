/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include "string.h"

void revers_string(char *p_char_array);
int main()
{
	char array[30];
	printf("Enter a string: ");
	fflush(stdin); fflush(stdout);
	gets(array);
	revers_string(array);
	return 0;
}

void revers_string(char *p_char_array)
{
	int array_leng=strlen(p_char_array);
	while(array_leng!=0)
	{
		printf("%c",*(p_char_array+array_leng-1));
		array_leng--;
	}

}
