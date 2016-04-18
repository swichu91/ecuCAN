/*
 * history_list.c
 *
 *  Created on: 16 kwi 2016
 *      Author: Mateusz
 */


#include "history_list.h"
#include <stdint.h>
#include <stdlib.h>

struct history_list_entry
{
	struct history_list_entry* prev;
	struct history_list_entry* next;

	char* data;
};

struct history_list
{
	struct history_list_entry* last;
	struct history_list_entry* current;
	struct history_list_entry* top;
	uint16_t current_len;
	uint16_t max_len;

};

void history_list_init(struct history_list** stack)
{
    *stack = malloc(sizeof (struct history_list_entry));
    (*stack)->last = NULL;
    (*stack)->current = NULL;
    (*stack)->top = NULL;
   // (*stack)->data = 666;
}

void history_list_push(struct history_list** stack,char* data)
{
    if(stack != NULL)
    {
        struct history_list_entry* temp = malloc(sizeof(struct history_list_entry));

        temp->data = data;
        temp->next = *stack;

        (*stack)->last = *stack;
        (*stack)->current = temp;
        (*stack)->top = temp;
        (*stack)->current_len++;


        if((*stack)->current_len == (*stack)->max_len) // we've reached maximum capacity of list, remove last element
        {
        	struct history_list_entry* temp = (*stack)->last->prev;

        	(*stack)->last->prev->next = NULL;
        	free((*stack)->last);
        	(*stack)->last = temp;
        }
    }

}

int history_list_pop(struct history_list** stack)
{
	struct history_list_entry* ret = NULL;

	ret = (*stack)->current;

	if((*stack)->current->next != NULL) //check if we've reached last element, if yes then return last component
	{
		(*stack)->current = (*stack)->current->next;
	}

    return ret;
}

int history_list_pop_rev(struct history_list** stack)
{
	struct history_list_entry* ret = NULL;

	ret = (*stack)->current;

	if((*stack)->current->prev != NULL) //check if we've reached last element, if yes then return last component
	{
		(*stack)->current = (*stack)->current->prev;
	}

    return ret;
}




