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
	char operator;
	float num1,num2,temp;
	printf("enter opeartor either + or - or * or divide: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&operator);
	printf("Enter two operands: ");
	scanf("%f %f",&num2,&num1);
	if(operator=='-')
		temp=num2-num1;
	else if(operator=='+')
		temp=num2+num1;
	else if(operator=='*')
		temp=num2*num1;
	else if(operator=='/')
		temp=num2/num1;
	printf("%f %c %f = %f",num1,operator,num2,temp);

	return 0;
}
