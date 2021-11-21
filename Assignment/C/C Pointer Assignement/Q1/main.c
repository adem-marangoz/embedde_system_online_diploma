/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include "string.h"

void change_variable_value(int *p_int2,int num2);
int main()
{
	int num1;
	printf("Enter an number:");
	fflush(stdin); fflush(stdout);
	scanf("%d",&num1);
	printf("entered numbers address: %X\n",&num1);
	printf("entered numbers value: %d\n",num1);
	int *p_int=&num1;
	printf("pointers address: %X\n",&p_int);
	printf("pointers value: %X\n",p_int);
	change_variable_value(p_int,33);
	printf("Entered numbers value after changign: %d",num1);
	return 0;
}

void change_variable_value(int *p_int2,int num2)
{
	*p_int2=num2;
	printf("address of p_int2:%X \n",&p_int2);
	printf("content address of p_int2:%X \n",p_int2);
	printf("content of p_int2:%d \n",*p_int2);

}
