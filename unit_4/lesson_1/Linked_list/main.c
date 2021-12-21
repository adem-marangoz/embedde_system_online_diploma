/*
 * main.c
 *
 *  Created on: Nov 1, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "LIFO.h"
//#include "FIFO.h"
#include "Linked_list.h"


int main()
{
	char _text[10];

	while(1)
		{
			Cprint("\n---------------------------\n");
			Cprint(" Choose on of the following Options \n ");
			Cprint(" 1: Add_Students \n");
			Cprint(" 2: Delete_Students \n");
			Cprint(" 3: Display_all_students \n");
			Cprint(" 4: Search_of_Student: \n");
			Cprint(" 5: Reverse_list \n");
			Cprint(" 6: Display_By_Index \n");
			Cprint(" 7: Display_By_Index_from_end \n");
			Cprint(" 8: Middle_node \n");
			gets(_text);
			Cprint("\n---------------------------\n");
			switch(atoi(_text))
			{
			case 1:
				Add_student();
				break;
			case 2:
				delet_student();
				break;
			case 3:
				display_all_students();
				break;
			case 4:
				search_of_student();
				break;
			case 5:
				reverse_list();
				break;
			case 6:
				Display_By_Index();
				break;
			case 7:
				Display_By_Index_From_end();
				break;
			case 8:
				Middle_node();
				break;
			default:
				Cprint("\n Wrong Option \n Please Try again\n");
				break;
			}

		}
	return 0;
}

































