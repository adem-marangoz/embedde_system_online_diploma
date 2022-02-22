/*
 * queue.h
 *
 *  Created on: Jan 23, 2022
 *      Author: MAHMMAD_ALNAJJAR
 */

#ifndef QUEUE_H_
#define QUEUE_H_


#define Cprint(...)	{fflush(stdin);\
					fflush(stdout);\
					printf(__VA_ARGS__);\
					fflush(stdin);\
					fflush(stdout);\
					}

typedef struct student_queue
{

    int roll_n;
    char first_name[15];
    char last_name[15];
    float GPA;
    struct courses
	{
    	int mark;
	}course[4];
	struct student_queue *p_student;
}student_queue;

typedef enum
{
    error,
    sucsess
}queue_state_t;


queue_state_t Read_File_First();
queue_state_t Read_file();
queue_state_t add_student_from_file();
queue_state_t add_student_menaully();
queue_state_t find_student_by_roll();
queue_state_t find_studenty_by_first_name();
queue_state_t find_student_by_last_name();
queue_state_t find_regsitered_student_courses();
queue_state_t count_a_students();
queue_state_t delet_a_student();
queue_state_t update_a_student();
queue_state_t show_all_students_information_form_file();
queue_state_t show_all_students_information_from_queue();
queue_state_t transfer_list_to_file();
queue_state_t add_list_of_students_manually_to_the_file(student_queue **dis,student_queue *src);
queue_state_t test();



#endif /* QUEUE_H_ */
