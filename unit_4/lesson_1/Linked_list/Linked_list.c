/*
 * Linked_list.c
 *
 *  Created on: Dec 19, 2021
 *      Author: MAHMMAD_ALNAJJAR
 */


#include "Linked_list.h"
#include <stdlib.h>

Linked_list_Buf *first_node=NULL;


Linked_list_Status Add_student(void)
{
    Linked_list_Buf *new_node=NULL;
    if(first_node==NULL)
    {
        new_node=(Linked_list_Buf*)malloc(sizeof(Linked_list_Buf));
        first_node=new_node;
    }else
    {
        new_node=(Linked_list_Buf*)malloc(sizeof(Linked_list_Buf));
        Linked_list_Buf* _node=first_node;
        while(_node->N_node)
        {
            _node=(Linked_list_Buf*)_node->N_node;
        }
        _node->N_node=new_node;
    }
    new_node->N_node=NULL;
    if(!fill_node(new_node))
    {
    	return Linked_Error;
    }
    return Linked_no_Error;
}

Linked_list_Status delet_student(void)
{
    char id_c[10],id_dec;
    Cprint("Enter ID to be delete: ");
    
    id_dec=(unsigned char)atoi(gets(id_c));
    Linked_list_Buf *new_node=NULL;
    Linked_list_Buf *prev_node=NULL;    
    if(first_node->SStudent.id==id_dec)
    {
        if(first_node->N_node)
        {
            new_node=first_node;
            first_node=(Linked_list_Buf*)first_node->N_node;
            free(new_node);
            return Linked_no_Error;
        }
        else
        {
            first_node=NULL;
            return Linked_no_Error;
        }
    }else
    {
        new_node=(Linked_list_Buf*)first_node;
        prev_node=(Linked_list_Buf*)first_node;
        do
        {
            prev_node=new_node;
            new_node=(Linked_list_Buf*)new_node->N_node;
            if(new_node->SStudent.id==id_dec)
            {
                prev_node->N_node=new_node->N_node;
                free(new_node);
                return Linked_no_Error;
            }
            
        } while (new_node->N_node);
    }
    Cprint("cannot find this id: %d",id_dec);
    return Linked_Error;
}

Linked_list_Status display_all_students(void)
{
    Linked_list_Buf *temp=first_node;
    Cprint("\n----------------Display all students-------------------\n");
    while (temp->N_node)
    {
        Cprint("\n student name: %s \n student id: %d \n student age: %d \n",temp->SStudent.name,temp->SStudent.id,temp->SStudent.age);
        Cprint("-----------------------------------\n");
        temp=(Linked_list_Buf*)temp->N_node;
    }
    Cprint("\n student name: %s \n student id: %d \n student age: %d \n",temp->SStudent.name,temp->SStudent.id,temp->SStudent.age);
	Cprint("-----------------------------------\n");
    Cprint("-----------------------end-----------------------------\n");
    return Linked_no_Error;
}

Linked_list_Status search_of_student()
{
    char id_c[10],id_dec;
    Cprint("Write the ID you want to search for: ");
    id_dec=(char)atoi(gets(id_c));
    Linked_list_Buf *temp=first_node;
    while(temp)
    {
        if(temp->SStudent.id==id_dec)
        {
            Cprint("Information about the ID : %d\n",id_dec);
            Cprint(" Name: %s\n ID: %d\n age: %d\n",temp->SStudent.name,temp->SStudent.id,temp->SStudent.age);
            return Linked_no_Error;
        }
        temp=(Linked_list_Buf*)temp->N_node;
    }
    Cprint("Cannot find this ID: %d\n",id_dec);
    return Linked_Error;
    
}

Linked_list_Status reverse_list(void)
{
	Linked_list_Buf *head_node=first_node;
	Linked_list_Buf *temp1_node=NULL;
	Linked_list_Buf *temp2_node=NULL;
	while(head_node!=NULL)
	{
		temp2_node=(Linked_list_Buf*)head_node->N_node;
		head_node->N_node=temp1_node;
		temp1_node=(Linked_list_Buf*)head_node;
		head_node=(Linked_list_Buf*)temp2_node;
	}
	first_node=temp1_node;
	display_all_students();
	return Linked_no_Error;
}

Linked_list_Status Display_By_Index()
{
	char text[10],index,local_index;
	Linked_list_Buf *Cur_node=first_node;
	Cprint("Please Enter the index: ");
	index=atoi(gets(text));
	index--;
	if(index<0)
	{
		Cprint("Index is Negative");
		return Linked_Error;
	}else
	{
		while(local_index!=index)
		{
			Cur_node=(Linked_list_Buf*)Cur_node->N_node;
			local_index++;
		}
		Cprint("Index Inforamtion: \n Name: %s\n ID: %d\n age: %d",Cur_node->SStudent.name,Cur_node->SStudent.id,Cur_node->SStudent.age);
		return Linked_no_Error;
	}
}

Linked_list_Status Display_By_Index_From_end()
{
	char text[10],index,index_local;
	Linked_list_Buf *head_node=first_node;
	Linked_list_Buf *till_node=first_node;
	Cprint("Please Enter the Index from_end: ");
	index=atoi(gets(text));
	while(head_node)
	{
		if(index_local<index)
		{
			index_local++;
		}else if(index_local==index)
		{
			till_node=(Linked_list_Buf*)till_node->N_node;
		}
		head_node=(Linked_list_Buf*)head_node->N_node;
	}
	Cprint(" Name: %s\n ID: %d\n age: %d\n",till_node->SStudent.name,till_node->SStudent.id,till_node->SStudent.age);
	return Linked_no_Error;
}


Linked_list_Status Middle_node()
{
	char index=0;
	Linked_list_Buf *Fast_node=first_node;
	Linked_list_Buf *slow_node=first_node;
	while(Fast_node)
	{
		Fast_node=(Linked_list_Buf*)Fast_node->N_node;
		if(Fast_node)
		{
			Fast_node=(Linked_list_Buf*)Fast_node->N_node;
			slow_node=(Linked_list_Buf*)slow_node->N_node;
			index++;
		}
	}
	Cprint("Middle is %d Nodes Information: \n",index);
	Cprint(" Name: %s\n ID: %d\n age: %d\n",slow_node->SStudent.name,slow_node->SStudent.id,slow_node->SStudent.age);
	return Linked_no_Error;
}

filling_status fill_node(Linked_list_Buf *_linked_listed)
{
    unsigned char text[15];
    Cprint("Please Enter the student name: ");
    gets(_linked_listed->SStudent.name);
    Cprint("Please Enter the student id: ");
    _linked_listed->SStudent.id=(unsigned char)atoi(gets(&text));
    Cprint("Please Enter the student age: ");
    _linked_listed->SStudent.age=(unsigned char)atoi(gets(&text));
    
    return fiiling_success;
}
