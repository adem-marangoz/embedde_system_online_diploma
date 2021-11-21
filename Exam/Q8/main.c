/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include "string.h"

int fun(int _array1[],int length);

int main()
{
	int array[5];
	int str=sizeof(array)/sizeof(array[0]);
	printf("Enter 5 a number:");
	fflush(stdin); fflush(stdout);
	for(int i=0;i<str;i++)
		scanf("%d",&array[i]);
	fun(array,str);
	return 0;
}

int fun(int _array1[],int length)
{
	int temp;
	int len=length/2;
	for(int i=0;i<len;i++)
	{
		temp=_array1[i];
		_array1[i]=_array1[length-i-1];
		_array1[length-i-1]=temp;
	}
	for(int i=0;i<length;i++)
		printf("%d ",_array1[i]);
	return 0;
}
