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
	char m_name[30];
	unsigned char m_roll;
	float marks;
};


int main()
{
	struct student s;
	printf("Enter information of stduents:\n");
	printf("\nEnter name: ");
	fflush(stdin); fflush(stdout);
	scanf("%s",&s.m_name);
	fflush(stdin); fflush(stdout);
	printf("Enter roll number: ");
	fflush(stdin); fflush(stdout);
	scanf("%u",&s.m_roll);
	fflush(stdin); fflush(stdout);
	printf("Enter marks: ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&s.marks);
	printf("\nDisplaying Information\n");
	fflush(stdin); fflush(stdout);
	printf("name: %s\n",s.m_name);
	printf("Roll: %d\n",s.m_roll);
	printf("Marks: %0.2f",s.marks);
	return 0;
}
