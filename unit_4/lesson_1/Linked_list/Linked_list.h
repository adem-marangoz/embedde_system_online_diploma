/*
 * Linked_list.h
 *
 *  Created on: Dec 19, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdio.h>

#define Cprint(...)	{fflush(stdin);\
					fflush(stdout);\
					printf(__VA_ARGS__);\
					fflush(stdin);\
					fflush(stdout);\
					}

typedef struct 
{
    char name[15];
    char id; 
    unsigned char age;
}Student;

typedef struct 
{
    Student SStudent;
    struct Linked_list_Buf *N_node;
}Linked_list_Buf;

typedef enum
{
    filling_not_success,
    fiiling_success
}filling_status;

typedef enum
{
    Linked_Error,
    Linked_no_Error,
}Linked_list_Status;

Linked_list_Status Add_student(void);
Linked_list_Status delet_student(void);
Linked_list_Status display_all_students(void);
Linked_list_Status search_of_student();
Linked_list_Status reverse_list(void);
Linked_list_Status Display_By_Index();
Linked_list_Status Display_By_Index_From_end();
Linked_list_Status Middle_node();

filling_status fill_node(Linked_list_Buf *_linked_listed);



#endif /* LINKED_LIST_H_ */
