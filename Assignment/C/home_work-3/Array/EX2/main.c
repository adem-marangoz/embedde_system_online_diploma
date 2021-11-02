/*
 * main.c
 *
 *  Created on: Oct 31, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>

int main()
{
	int number_of_data;
	float numbers[10],sum=0.0;
	printf("Enter the numbers of data: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&number_of_data);
	for(int i=0;i<number_of_data;i++)
	{
		printf("%d Enter number : ",i+1);
		fflush(stdin); fflush(stdout);
		scanf("%f",&numbers[i]);
		sum+=numbers[i];
	}
	printf("Average = %f",sum/number_of_data);
	return 0;
}
