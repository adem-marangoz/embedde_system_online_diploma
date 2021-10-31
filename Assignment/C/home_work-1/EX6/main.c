/*
 * main.c
 *
 *  Created on: Oct 31, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>

int main()
{
	float user_float,user_float2,temp;
	printf("Enter value of a : ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&user_float);
	printf("Enter value of b : ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&user_float2);
	temp=user_float;
	user_float=user_float2;
	user_float2=temp;
	printf("After swapping, value of a = %f\n",user_float);
	printf("After swapping, value of b = %f",user_float2);
	return 0;

}
