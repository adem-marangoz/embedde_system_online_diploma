/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>

int main()
{
	int array[10],n,s;
	printf("Enter no of elements : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	fflush(stdin); fflush(stdout);
	for (int j=0;j<n;j++)
	{
		scanf("%d",&array[j]);
	}
	fflush(stdin); fflush(stdout);
	printf("Enter the elements to be searched : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&s);
	for(int i=0;i<n;i++)
	{
		if(s==array[i])
		{
			printf("number found at the location = %d",i+1);
			break;
		}
	}
	return 0;
}
