/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>

int main()
{
	int row,column,temp;
	int array[5][5]={0},diff;
	printf("Enter rows and columns of matrix: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&row);
	fflush(stdin); fflush(stdout);
	scanf("%d",&column);
	fflush(stdin); fflush(stdout);
	printf("Enter elements of matrix: \n");
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<column;j++)
		{
			printf("Enter elements a%d%d :",i+1,j+1);
			fflush(stdin); fflush(stdout);
			scanf("%d",&array[i][j]);
		}
	}
	printf("Entered Matrix: \n");
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<column;j++)
		{
			printf("%d\t",array[i][j]);
		}
		printf("\n");
	}
	diff=row>column?	row:column;
	int j=0;
	for(int i=0;i<diff;i++)
	{
		j=i;
		for(;j<diff;j++)
		{
			if(i!=j)
			{

				temp=array[i][j];
				array[i][j]=array[j][i];
				array[j][i]=temp;
			}
		}

	}
	printf("Transpose of Matrix \n");
	for(int a=0;a<column;a++)
	{
		for(int b=0;b<row;b++)
		{
			printf("%d \t",array[a][b]);
		}
		printf("\n");
	}
	return 0;
}
