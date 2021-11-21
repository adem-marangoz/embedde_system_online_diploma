/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include "string.h"

fun(int _array1[]);
#define size_buffer 7
int main()
{
	int array1[size_buffer];
	printf("enter 7 element please: ");
	fflush(stdin); fflush(stdout);
	for(int i=0;i<size_buffer;i++)
		scanf("%d",&array1[i]);
	fun(array1);
	return 0;

}

fun(int _array1[])
{
	int array2[size_buffer]={0};
	for(int i=0;i<size_buffer;i++)
	{
		for(int j=0;j<size_buffer;j++)
		{
			if(_array1[i]==_array1[j])
			{
				if(i==j)
					continue;
				array2[i]=1;
			}

		}
	}
	printf("outpur: ");
	for(int i=0;i<size_buffer;i++)
	{
		if(array2[i]==0)
			printf("%d. ",_array1[i]);
	}
}
