/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include "string.h"

int main()
{
	 int num,temp=0;
	printf("enter a number: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&num);
	for(;num;num--)
	{
		temp+=num;
	}
	printf("Sum %d",temp);
}
