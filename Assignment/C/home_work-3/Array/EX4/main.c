/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>

int main()
{
	int n,e,l,temp;
	int array[10];
	printf("Enter no of elements : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&array[i]);
	}
	printf("Enter the element to be inserted : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&e);
	printf("Enter the location : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&l);
	for (int i=0;i<n+1;i++)
	{
		if(i>=l+1)
		{
			temp=array[l];
			array[l]=array[i];
			array[i]=temp;

		}
	}
	array[l]=e;
	for(int i=0;i<n+1;i++)
	{
		printf("%d\t",array[i]);
	}
	return 0;
}
