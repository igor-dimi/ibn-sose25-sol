//
//  mylist.c
//  
//
//  Created by Sascha Hunold on 11/3/11.
//  Copyright 2011. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include "mylist.h"

void init_list(list_t *list)
{
    list->cur_size = 0;
    list->head = NULL;
}

void append_elem(list_t *list, elem_t *node)
{
    node->next = NULL;
    
    if( list->head == NULL ) {
        list->head = node;
        list->cur_size = 1;
    } else {
        elem_t *cur_elem;
        cur_elem = list->head;
        while( cur_elem->next != NULL ) {
            cur_elem = cur_elem->next;
        } //cur_elem points to last node
        cur_elem->next = node;
        list->cur_size++;
    }
}

void remove_elem(list_t *list, elem_t **node)
{
    elem_t *ret_elem;
    assert( list->cur_size > 0 );
    
    ret_elem = list->head;
    
    if( list->head->next != NULL ) 
        list->head = list->head->next;
    else list->head = NULL;

    list->cur_size--;
    
    *node = ret_elem;
}


int get_size(list_t *list)
{
    return list->cur_size;    
}

void print_list(list_t* list)
{
    printf("size: %d\n", list->cur_size);
    printf("list: ");
    elem_t* el = list->head;
    // printed up until before el
    while(el != NULL) {
        if(el->next != NULL) 
            printf("%d -> ", el->data);
        else // el is last
            printf("%d", el->data);
        el = el->next;
    }
    printf("\n");
}