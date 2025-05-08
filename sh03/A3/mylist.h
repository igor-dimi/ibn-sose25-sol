//
//  mylist.h
//  
//
//  Created by Sascha Hunold on 11/3/11.
//  Copyright 2011. All rights reserved.
//

#ifndef _mylist_h
#define _mylist_h

struct elem {
    struct elem *next;
    int data;
};
typedef struct elem elem_t;


struct list {
    elem_t *head;
    int cur_size;
};
typedef struct list list_t;

void init_list(list_t *list);
void append_elem(list_t *list, elem_t *node);
void remove_elem(list_t *list, elem_t **node);
int is_empty(list_t *list);
int is_full(list_t *list);
int get_size(list_t *list);
void print_list(list_t *list);

#define NUM_CONSUMER     10
#define MAX_COUNT        20
#define FIBONACCI_MAX    40
#define MAX_QUEUE_LENGTH  5

#endif
