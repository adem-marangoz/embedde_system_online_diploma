/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include "string.h"

struct student
{
	float real;
	float imaginary;
};


int main()
{
	struct student num1,num2;
	printf("Fort 1st complex number");
	printf("\nEnter real and imaginary respectively: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f",&num1.real,&num1.imaginary);
	fflush(stdin); fflush(stdout);
	printf("\nFor 2st complex number\n");
	printf("Enter real and imaginary respectively: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f",&num2.real,&num2.imaginary);
	fflush(stdin); fflush(stdout);
	printf("Sum= %f+%fi",num1.real+num2.real,num1.imaginary+num2.imaginary);
	return 0;
}
