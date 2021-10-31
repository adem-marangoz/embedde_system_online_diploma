/*
 * main.c
 *
 *  Created on: Oct 31, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>

int main()
{
	float user_number,user_number2;
	printf("Enter two numbers : ");
	fflush(stdin); fflush(stdout);
	scanf("%f%f",&user_number,&user_number2);
	printf("Sum : %f",user_number+user_number2);
	return 0;

}
