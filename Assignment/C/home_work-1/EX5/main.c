/*
 * main.c
 *
 *  Created on: Oct 31, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>

int main()
{
	char user_char;
	printf("Enter a character: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&user_char);
	printf("ASCII value of %c = %d",user_char,user_char);
	return 0;

}
