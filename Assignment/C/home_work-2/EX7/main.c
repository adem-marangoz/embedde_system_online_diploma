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
	 int num,temp=1;
	printf("enter a number: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&num);
	if(num==0)
		goto print_screen;
	else if(num<0)
	{
		printf("Error !!! Factorial of negative number doesn't exist");
		return 0;
	}
	for(;num;num--)
	{
		temp*=num;
	}
print_screen:
	printf("Factorial = %d",temp);
	return 0;
}
