/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include "string.h"

struct employee
{
	int ID;
	char Name[10];
};

int main()
{
	struct employee first;
	struct employee *second=&first;
	printf("Enter the employee id :");
	fflush(stdin); fflush(stdout);
	scanf("%d",&(first.ID));
	fflush(stdin); fflush(stdout);
	printf("Enter the emplyee name :");
	fflush(stdin); fflush(stdout);
	gets(first.Name);
	printf("Emloyee Name :%s\n",second->Name);
	printf("Emplyee ID : %d",second->ID);

	return 0;
}
