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
	unsigned short marks;
};


int main()
{
	struct student s[10];
	char yes_on_no;
	unsigned char index=0;
	printf("Enter information of students:\n");
	do
	{
		printf("\nFor roll number %u",index+1);
		printf("\nEnter name: ");
		s[index].m_roll=index+1;
		fflush(stdin); fflush(stdout);
		scanf("%s",&s[index].m_name);
		fflush(stdin); fflush(stdout);
		printf("Enter marks: ");
		fflush(stdin); fflush(stdout);
		scanf("%u",&s[index].marks);
		fflush(stdin); fflush(stdout);
		printf("do you want to continue entering data?");
		fflush(stdin); fflush(stdout);
		scanf("%c",&yes_on_no);
		fflush(stdin); fflush(stdout);
		index++;
	}while(yes_on_no=='y');
	printf("Displaying information of students:\n");
	for(int i=0;i<index;i++)
	{
		printf("Information for roll number %d\n",s[i].m_roll);
		printf("Name: %s\n",s[i].m_name);
		printf("Marks: %u\n",s[i].marks);
	}
	return 0;
}

