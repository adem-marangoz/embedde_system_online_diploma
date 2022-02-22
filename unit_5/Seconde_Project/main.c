/*
 * main.c
 *
 *  Created on: Jan 23, 2022
 *      Author: MAHMMAD_ALNAJJAR
 */


#include "stdio.h"
#include "queue.h"


int main()
{
	int x=8;
	Read_File_First();
	while(1)
	{

		Cprint("\n%-4s%-5s","1-","add student details from file\n");
		Cprint("%-4s%-5s","2-","add student details manually\n");
		Cprint("%-4s%-5s","3-","find the student by the given roll number\n");
		Cprint("%-4s%-5s","4-","find the student by the given first name\n");
		Cprint("%-4s%-5s","5-","find the student by the given last name\n");
		Cprint("%-4s%-5s","6-","find the students registered in a course\n");
		Cprint("%-4s%-5s","7-","count of students\n");
		Cprint("%-4s%-5s","8-","Delete a student\n");
		Cprint("%-4s%-5s","9-","update student\n");
		Cprint("%-4s%-5s","10-","show all information students in file\n");
		Cprint("%-4s%-5s","11-","show all information students menaully\n");
		Cprint("%-4s%-5s","12-","show all information students file and menaully\n");
		Cprint("%-4s%-5s","13-","Add a list of students manually added to the file\n");
		Cprint("%-4s%-5s","14-","exits\n");
		Cprint("Enter the number options: ");
		scanf("%d",&x);

		switch(x)
		{
			case 1:
				add_student_from_file();
				break;
			case 2:
				add_student_menaully();
				break;
			case 3:
				find_student_by_roll();
				break;
			case 4:
				find_studenty_by_first_name();
				break;
			case 5:
				find_student_by_last_name();
				break;
			case 6:
				find_regsitered_student_courses();
				break;
			case 7:
				count_a_students();
				break;
			case 8:
				delet_a_student();
				break;
			case 9:
				update_a_student();
				break;
			case 10:
				show_all_students_information_form_file();
				break;
			case 11:
				show_all_students_information_from_queue();
				break;
			case 12:
				Read_file();
				break;
			case 13:
				transfer_list_to_file();
				break;
			case 14:
				exit(1);
				break;
		}
	}
}
