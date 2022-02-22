/*
 * queue.c
 *
 *  Created on: Jan 23, 2022
 *      Author: MAHMMAD_ALNAJJAR
 */


#include <stdio.h>
#include "queue.h"
#include "stdlib.h"
#include <string.h>

//---------------------------------Declare a pointer to structs------------------------------
student_queue *head_student_m=NULL;
student_queue *head_student_test=NULL;
//-------------------------------------------------------------------------------------------

//---------------------------------Decleration a functions-----------------------------------
static void header();
static void print_roll(student_queue *print_r);
static queue_state_t print(student_queue *head);
static queue_state_t change_gpa(student_queue *head);
static queue_state_t change_roll(student_queue *head);
static student_queue* search_roll2(student_queue **head);
static student_queue* entry_student(student_queue** head);
static queue_state_t change_last_name(student_queue *head);
static queue_state_t change_first_name(student_queue *head);
static queue_state_t change_course_id(student_queue *head,int n);
static queue_state_t delet_a_student_f(student_queue **head,int _roll);
static queue_state_t sreach_by_last_name(student_queue *head,char *nm);
static queue_state_t sreach_by_first_name(student_queue *head,char *nm);
static queue_state_t search_in_roll(student_queue *_roll,student_queue *start);
static queue_state_t rewrite_file_students_information(student_queue *head,char n_f[]);
//-------------------------------------------------------------------------------------------

//---------------------------------Decleration global variables------------------------------
int f_s_counter;
int m_s_counter;
//-------------------------------------------------------------------------------------------


/**
 * @brief A function to read the txt file in the municipality to transfer data to queue
 * @return queue_state_t
 */
queue_state_t Read_File_First()
{
	FILE *file_pointer;
	student_queue student_info;
	file_pointer=fopen("my_students.txt","r");
	while(fread(&student_info,sizeof(student_queue),1,file_pointer))
	{
		{
			f_s_counter++;
			student_queue *s=(student_queue*)malloc(sizeof(student_queue));
			if(head_student_test==NULL)
			{
				head_student_test=s;
			}else
			{
				student_queue *temp_node=(student_queue*)head_student_test;
				while(temp_node->p_student)
				{
					temp_node=(student_queue*)temp_node->p_student;
				}
				temp_node->p_student=s;
			}
			s->roll_n=student_info.roll_n;
			strcpy(s->first_name,student_info.first_name);
			strcpy(s->last_name,student_info.last_name);
			s->GPA=student_info.GPA;
			for(int counter=0;counter<4;counter++)
			{
				s->course[counter].mark=student_info.course[counter].mark;
			}
			s->p_student=NULL;
		}

	}
	fclose(file_pointer);
	return sucsess;
}

/**
 * @brief A function to enter student information
 * @param [head] root of head list
 * @return student_queue
 */
static student_queue* entry_student(student_queue** head)
{
	queue_state_t test1 = error;
	queue_state_t test2 = error;
	student_queue *new_node=(student_queue*)malloc(sizeof(student_queue));
	new_node->p_student=NULL;

	student_queue *temp_node=*head;
	if(*head == NULL)
	{
		*head=new_node;
	}
	else
	{
		while(temp_node->p_student != NULL)
		{
			temp_node=temp_node->p_student;
		}
		temp_node->p_student=new_node;
	}
	Cprint("Enter the student number roll: ");
	scanf("%d",&new_node->roll_n);
	do
	{
		test1 = search_in_roll(new_node,head_student_test);
		test2 = search_in_roll(new_node,head_student_m);
	}while(test1 == error && test2 == error);
	Cprint("Enter the student first name: ");
	gets(new_node->first_name);
	Cprint("Enter the student last name: ");
	gets(new_node->last_name);
	Cprint("Enter the student GPA degree: ");
	scanf("%f",&new_node->GPA);

	for(int counter=0;counter<4;counter++)
	{
		Cprint("%d.Courses registered by the student: ",counter);
		scanf("%d",&new_node->course[counter].mark);
		if((counter != 0) && (new_node->course[counter].mark != 0))
		{
			for(int i=0;i<counter;i++)
			{
				if(new_node->course[counter].mark == new_node->course[i].mark)
				{
					Cprint("This course exist in you list, Please entry another course: ");
					scanf("%d",&new_node->course[counter].mark);
					i=-1;
				}
			}
		}
	}

	return new_node;
}

/**
 * @brief To print the student information in the file and the manually entered student information
 * @return queue_state_t
 */
queue_state_t Read_file()
{
	show_all_students_information_form_file();
	show_all_students_information_from_queue();
	return sucsess;
}

/**
 * @brief Search function to verify the existence of a similar student number
 * @param [_roll] pointer indicates the address of the new student's information
 * @param [start] pointer indicates the information address of the previously added students
 * @return queue_state_t
 */
static queue_state_t search_in_roll(student_queue *_roll,student_queue *start)
{
	student_queue *_start=start;
	while(start)
	{
		rest:
		if((_roll->roll_n==start->roll_n) && (start != _roll))
		{
			Cprint("\nStudent roll number already exists\n");
			Cprint("Please enter a different student roll number: ");
			scanf("%d",&_roll->roll_n);
			start=_start;
			goto rest;
		}
		start=start->p_student;
	}
	return sucsess;
}

/**
 * @brief To print the student information in the file
 * @return queue_state_t
 */
queue_state_t show_all_students_information_form_file()
{
	header();
	print(head_student_test);
	Cprint("\n-----------------------------------------------------------------------");
	return sucsess;

}

/**
 * To print the student information manually entered
 * @return queue_state_t
 */
queue_state_t show_all_students_information_from_queue()
{
	header();
	print(head_student_m);
	Cprint("\n-----------------------------------------------------------------------");
	return sucsess;
}

/**
 * @brief To print the information of a specific student or node
 * @param [head] pointer indicates a specific address information about a student to print
 * @return queue_state_t
 */
static queue_state_t print(student_queue *head)
{
	if(head==NULL)
	{
		Cprint("\n--------------------------STUDENTS INFORMATION EMPTY----------------------------");
	}else
	{
		while(head)
		{
			Cprint("\n%-5d%-10s%-10s%-5.2f",head->roll_n,head->first_name,head->last_name,head->GPA);
			for(int j=0;j<4;j++)
			{
				Cprint("%7d",head->course[j].mark);
			}
			head=(student_queue*)head->p_student;
		}
	}
	return sucsess;
}

/**
 * @brief Add a new student to the file
 * @return queue_state_t
 */
queue_state_t add_student_from_file()
{
	student_queue *s= entry_student(&head_student_test);
	FILE *fp;
	fp=fopen("my_students.txt","a");
	fwrite(s,sizeof(student_queue),1,fp);
	fclose(fp);
	f_s_counter++;
	return sucsess;
}

/**
 * @brief Add a new student to the manual list
 * @return queue_state_t
 */
queue_state_t add_student_menaully()
{
	entry_student(&head_student_m);
	m_s_counter++;
	return sucsess;
}

/**
 * @brief An argument function that calls the function to add students from the manual list to the file
 * @return queue_state_t
 */
queue_state_t transfer_list_to_file()
{
	add_list_of_students_manually_to_the_file(&head_student_m,head_student_test);
	return sucsess;
}

/**
 * @brief Move the list of manually added students to the list of students in the file at the end
 * @param [dis] pointer on head for manual list
 * @param [src] pointer on head for file list
 * @return queue_state_t
 */
queue_state_t add_list_of_students_manually_to_the_file(student_queue **dis,student_queue *src)
{
	FILE *fp;
	fp=fopen("my_students.txt","a");
	student_queue *temp=*dis;
	while(src->p_student)
	{
		src=src->p_student;
	}
	src->p_student = *dis;
	while(temp)
	{
		fwrite(temp,sizeof(student_queue),1,fp);
		temp=temp->p_student;
	}
	fclose(fp);
	*dis=(void*)NULL;
	return sucsess;
}

/**
 * @brief A function to search for a specific student roll number
 * @param [head] pointer to head of the list
 * @return Returns the address of the structure where the student number was found
 */
static student_queue* search_roll2(student_queue **head)
{
	static int _roll;
	if(_roll == 0)
	{
		Cprint("Enter the student roll number : ");
		scanf("%d",&_roll);
	}
	student_queue *temp = *head;
	while(temp)
	{
		if(_roll == temp->roll_n)
		{
			_roll=0;
			return temp;
		}
		temp=temp->p_student;
	}


	return (student_queue*)NULL;
}

/**
 * @brief print conver
 */
static void header()
{
	Cprint("-----------------------------------------------------------------------\n");
	Cprint("%-5s%-10s%-10s%-10s%-7s%-7s%-7s%-7s\n","Roll","F_N","L_N","GPA","1.C","2.C","3.C","4.C");
	Cprint("-----------------------------------------------------------------------");
}

/**
 * @brief Printing a specific structure for a student
 * @param print_r argument of reference to a specific structure
 */
static void print_roll(student_queue *print_r)
{
	Cprint("\n%-5d%-10s%-10s%-5.2f",print_r->roll_n,print_r->first_name,print_r->last_name,print_r->GPA);
	for(int j=0;j<4;j++)
	{
		Cprint("%7d",print_r->course[j].mark);
	}
}

/**
 * @brief A function to search within the lists for a specific student roll number
 * @return queue_state_t
 */
queue_state_t find_student_by_roll()
{

	student_queue *temp_node = NULL;
	if((temp_node=search_roll2(&head_student_test))!=((student_queue*)NULL) || (temp_node=search_roll2(&head_student_m))!=((student_queue*)NULL))
	{
		header();
		print_roll(temp_node);
	}
	Cprint("\n-----------------------------------------------------------------------");
	return sucsess;
}

/**
 * @brief A argument function to search within the lists for a specific student first name and print it
 * @param [head] pointer to head of the list
 * @param [nm] pointer for the entered first name
 * @return queue_state_t
 */
static queue_state_t sreach_by_first_name(student_queue *head,char *nm)
{
	while(head)
	{
		if(!strcmp(head->first_name,nm))
		{
			print_roll(head);
		}
		head = head->p_student;
	}
	return sucsess;
}

/**
 * @brief A function to search by entering the first name of a specific student
 * @return queue_state_t
 */
queue_state_t find_studenty_by_first_name()
{
	char name[15];
	Cprint("Enter the Student first name for sreach : ");
	gets(name);
	header();
	sreach_by_first_name(head_student_test,name);
	sreach_by_first_name(head_student_m,name);
	Cprint("\n-----------------------------------------------------------------------");
	return sucsess;
}

/**
 * @brief A argument function to search within the lists for a specific student last name and print it
 * @param [head] pointer to head of the list
 * @param [nm] pointer for the entered last name
 * @return queue_state_t
 */
static queue_state_t sreach_by_last_name(student_queue *head,char *nm)
{
	while(head)
	{
		if(!strcmp(head->last_name,nm))
		{
			print_roll(head);
		}
		head = head->p_student;
	}
	return sucsess;
}

/**
 * @brief A function to search by entering the last name of a specific student
 * @return queue_state_t
 */
queue_state_t find_student_by_last_name()
{
	char name[15];
	Cprint("Enter the Student first name for sreach : ");
	gets(name);
	header();
	sreach_by_last_name(head_student_test,name);
	sreach_by_last_name(head_student_m,name);
	Cprint("\n-----------------------------------------------------------------------");
	return sucsess;
}

/**
 * @brief A function to search within the lists for students participating in a specific course
 * @return queue_state_t
 */
queue_state_t find_regsitered_student_courses()
{
	student_queue *s=head_student_test;
	int course_n;
	Cprint("Enter the course number: ");
	scanf("%d",&course_n);
	Cprint("-----------------------File Students-----------------------");
	while(s)
	{
		for(int i=0;i<4;i++)
		{
			if(s->course[i].mark == course_n)
			{
				Cprint("\n%-5d%-10s%-10s%-5.2f",s->roll_n,s->first_name,s->last_name,s->GPA);
				for(int j=0;j<4;j++)
				{
					Cprint("%7d",s->course[j].mark);
				}
			}
		}
		s=s->p_student;
	}
	Cprint("\n-----------------------MENUALLY Students-----------------------");
	s=head_student_m;
	while(s)
	{
		for(int i=0;i<4;i++)
		{
			if(s->course[i].mark == course_n)
			{
				Cprint("\n%-5d%-10s%-10s%-5.2f",s->roll_n,s->first_name,s->last_name,s->GPA);
				for(int j=0;j<4;j++)
				{
					Cprint("%7d",s->course[j].mark);
				}
			}
		}
		s=s->p_student;
	}
	Cprint("\n--------------------------------------------------------------");
	return sucsess;
}

/**
 * @brief Print the number of students entered in the file and the manual list
 * @return queue_state_t
 */
queue_state_t count_a_students()
{
	Cprint("Number of students in the file : %d\n",f_s_counter);
	Cprint("The number of students added manually : %d\n",m_s_counter);
	return sucsess;
}

/**
 * @brief Function to remove a specific student from the list
 * @param [head] pointer to head list
 * @param [_roll] Student number to be deleted
 * @return queue_state_t
 */
static queue_state_t delet_a_student_f(student_queue **head,int _roll)
{
	student_queue *temp = *head;
	student_queue *prev = NULL;
	if(temp->roll_n == _roll)
	{
		*head = temp->p_student;
		free(temp);
	}else
	{
		while(temp->p_student)
		{
			prev = temp;
			temp=temp->p_student;
			if(temp->roll_n == _roll)
			{
				prev->p_student = temp->p_student;
				free(temp);
				return sucsess;
			}
		}
	}

	return error;
}

/**
 * @brief Function to delete a specific student by entering a number
 * @return queue_state_t
 */
queue_state_t delet_a_student()
{
	int select,_roll;
	Cprint("Enter one of the numbers to delete from where list:\n");
	Cprint("1 : FILE\n2 : MENUALLY\n");
	scanf("%d",&select);
	Cprint("Enter the roll number of student: ");
	scanf("%d",&_roll);
	switch(select)
	{
		case 1:
		{
			if(delet_a_student_f(&head_student_test,_roll) == sucsess)
			{
				rewrite_file_students_information(head_student_test,"my_students.txt");
				f_s_counter--;
			}
			break;
		}
		case 2:
		{
			if(delet_a_student_f(&head_student_m,_roll) == sucsess)
				m_s_counter--;
			break;
		}
		default:
			break;
	}
	return error;
}

/**
 * @brief Function to change student roll number
 * @param [head] pointer for a specific student structure
 * @return queue_state_t
 */
static queue_state_t change_roll(student_queue *head)
{
	queue_state_t test1 = error;
	queue_state_t test2 = error;
	student_queue *new_node=(student_queue*)malloc(sizeof(student_queue));
	Cprint("Enter the new student roll number: ");
	scanf("%d",&new_node->roll_n);
	do
	{
		test1 = search_in_roll(new_node,head_student_test);
		test2 = search_in_roll(new_node,head_student_m);
	}while(test1 == error && test2 == error);
	head->roll_n=new_node->roll_n;
	free(new_node);
	return sucsess;
}

/**
 * @brief Function to change student first name
 * @param [head] pointer for a specific student structure
 * @return queue_state_t
 */
static queue_state_t change_first_name(student_queue *head)
{
	Cprint("Enter the new student first name: ");
	char f_n[15];
	gets(f_n);
	strcpy(head->first_name,f_n);
	return sucsess;
}

/**
 * @brief Function to change student last name
 * @param [head] pointer for a specific student structure
 * @return queue_state_t
 */
static queue_state_t change_last_name(student_queue *head)
{
	Cprint("Enter the new student last name: ");
	char f_n[15];
	gets(f_n);
	strcpy(head->last_name,f_n);
	return sucsess;
}

/**
 * @brief Function to change student GPA
 * @param [head] pointer for a specific student structure
 * @return queue_state_t
 */
static queue_state_t change_gpa(student_queue *head)
{
	Cprint("Enter the new student GPA: ");
	float x;
	scanf("%f",&x);
	head->GPA=x;
	return sucsess;
}

/**
 * @brief Function to change student course ID
 * @param [head] pointer for a specific student structure
 * @param [n] course number
 * @return queue_state_t
 */
static queue_state_t change_course_id(student_queue *head,int n)
{
	Cprint("Enter the new student course id: ");
	int x;
	student_queue *temp=head;
	scanf("%d",&x);
	for(int y=0;y<4;y++)
	{
		if(y == n)
		{
			continue;
		}
		if(	x == (temp->course[y].mark))
		{
			Cprint("This ID number is available to the student\n");
			Cprint("Enter the new student course id: ")
			scanf("%d",&x);
			y=-1;
		}
	}
	head->course[n].mark=x;
	return sucsess;
}

/**
 * @brief A function to change information inside the file
 * @param [head] pointer to head list
 * @param [n_f] pointer for the entered file name
 * @return queue_state_t
 */
static queue_state_t rewrite_file_students_information(student_queue *head,char n_f[])
{
	FILE *fp;
	student_queue *temp=head;
	fp=fopen(n_f,"w");
	while(temp)
	{
		fwrite(temp,sizeof(student_queue),1,fp);
		temp=temp->p_student;
	}
	fclose(fp);
	return sucsess;
}

/**
 * @brief A function to change the information of a particular student
 * @return queue_state_t
 */
queue_state_t update_a_student()
{
	student_queue *temp_node = NULL;
	if((temp_node=search_roll2(&head_student_test))!=((student_queue*)NULL))
	{
		header();
		print_roll(temp_node);
	}
	Cprint("\n-----------------------------------------------------------------------");
	Cprint("\n%-4s%-5s","1-","change the roll number");
	Cprint("\n%-4s%-5s","2-","change the first name");
	Cprint("\n%-4s%-5s","3-","change the last name");
	Cprint("\n%-4s%-5s","4-","change the GPA");
	Cprint("\n%-4s%-5s","5-","change course ID");
	Cprint("\nChoose the field number you want to change : ");
	int x;
	scanf("%d",&x);
	switch(x)
	{
		case 1:
		{
			change_roll(temp_node);
			rewrite_file_students_information(head_student_test,"my_students.txt");
			break;
		}
		case 2:
		{
			change_first_name(temp_node);
			rewrite_file_students_information(head_student_test,"my_students.txt");
			break;
		}
		case 3:
		{
			change_last_name(temp_node);
			rewrite_file_students_information(head_student_test,"my_students.txt");
			break;
		}
		case 4:
		{
			change_gpa(temp_node);
			rewrite_file_students_information(head_student_test,"my_students.txt");
			break;
		}
		case 5:
			Cprint("Enter course ID between 1 to 4 : ");
			int x;
			scanf("%d",&x);
			if(x<=4 && x>=1)
				change_course_id(temp_node,x-1);
			rewrite_file_students_information(head_student_test,"my_students.txt");
			break;
	}
	return sucsess;
}




