/*
 * main.c
 *
 *  Created on: Oct 31, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>

int main()
{
	float matrix1[2][2],matrix2[2][2],sum[2][2];
	printf("Enter the elements of 1st matrix \n");
	for(int i=1;i<=2;i++)
	{
		for (int j=1;j<=2;j++)
		{
			printf("Enter a%d%d: ",i,j);
			fflush(stdin); fflush(stdout);
			scanf("%f",&matrix1[i-1][j-1]);
		}
	}
	printf("Enter the elements of 2st matrix \n");
	for(int i=1;i<=2;i++)
	{
		for (int j=1;j<=2;j++)
		{
			printf("Enter b%d%d: ",i,j);
			fflush(stdin); fflush(stdout);
			scanf("%f",&matrix2[i-1][j-1]);
		}
	}
	for(int i=1;i<=2;i++)
	{
		for (int j=1;j<=2;j++)
		{
			sum[i-1][j-1]=matrix1[i-1][j-1]+matrix2[i-1][j-1];
		}
	}
	for(int i=1;i<=2;i++)
	{
		for (int j=1;j<=2;j++)
		{
			printf("%f\t",sum[i-1][j-1]);
		}
		printf("\n");
	}

	return 0;
}
