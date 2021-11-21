/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include "string.h"

void prime_fun(int _num1, int _num2);

int main()
{
	int num1,num2;
	printf("Enter two numbers(intervals) :");
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&num1,&num2);
	if(num1>num2)
	{
		int temp;
		temp=num1;
		num1=num2;
		num2=temp;
	}
	printf("Prime numbers between 10 and 30 are : ");
	prime_fun(num1,num2);
	return 0;
}


void prime_fun(int _num1, int _num2)
{
	int p;
	for(int i=_num1;i<=_num2;i++)
	{
		for(int j=1;j<=i;j++)
		{
			if(i%j==0)
			{
				p++;
			}
		}
		if(p==2)
			printf("%d ",i);
		else
			p=0;
	}
}
