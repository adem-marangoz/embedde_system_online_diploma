/*
 * main.c
 *
 *  Created on: Oct 31, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>

int main()
{
	int user_number,user_number2;
	printf("Enter two integer : ");
	fflush(stdin); fflush(stdout);
	scanf("%d%d",&user_number,&user_number2);
	//scanf ("%d",)
	printf("Sum : %d",user_number+user_number2);
	return 0;

}
