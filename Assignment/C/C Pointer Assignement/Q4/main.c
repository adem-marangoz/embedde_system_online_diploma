/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include "string.h"

void revers_string(int *p_char_array,int index);
int main()
{
	int array[15],num1;
	printf("input the number of elements to store in the array (max15): ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&num1);
	fflush(stdin); fflush(stdout);
	printf("input %d number of elements in the array:\n",num1);
	fflush(stdin); fflush(stdout);
	for(int i=0;i<num1;i++)
	{
		printf("element - %d : ",i+1);
		fflush(stdin); fflush(stdout);
		scanf("%d",&array[i]);
	}
	revers_string(array,num1);
	return 0;
}

void revers_string(int *p_char_array,int index)
{
	while(index!=0)
	{
		printf("element - %d : %d\n",index,*(p_char_array+index-1));
		index--;
	}

}
