/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include "string.h"

void change_variable_value(char *p_int2,char num2_start,char num3_end);
int main()
{
	char num1=65;
	char *p_char=&num1;
	change_variable_value(p_char,num1,91);
	return 0;
}

void change_variable_value(char *p_int2,char num2_start,char num3_end)
{
	do
	{
		printf("%c ",(*p_int2)++);
	}while(*p_int2!=num3_end);
}
