/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include "string.h"

void fun(char _str1[],int _str1_len);

int main()
{
	char str1[30]; // declertion and definition of a character array
	int str1_len;
	printf("Enter a string :");
	fflush(stdin); fflush(stdout);
	gets(str1);
	str1_len=strlen(str1); // string length
	fun(str1,str1_len);

	return 0;

}

void fun(char _str1[],int _str1_len)
{
	unsigned char str2_index=0;
	char str2[30]={0};
	for(int i=0;_str1[i]!='\0';i++)
	{
		if(_str1[i]==32)
		{
			str2_index++;
			str2[str2_index]=i+1;
			_str1[i]='\0';
		}
	}
	for(int i=str2_index;i>=0;i--)
		printf("%s ",&_str1[str2[i]]);

}
