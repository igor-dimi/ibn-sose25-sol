//  Sascha Hunold, Sebastian Lackner (c) 2011-2014
//  pc.c

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mylist.h"


pthread_mutex_t queue_lock;
int queue_length;
list_t buffer;

int count_proc = 0;
int production_done = 0;


static unsigned long fib(unsigned int n);
static void create_data(elem_t **elem);
static void *consumer_func(void *);
static void *producer_func(void *);

/********************************************************/

static unsigned long fib(unsigned int n)
{
    if (n == 0 || n == 1) {
        return n;
    }
    else {
        return fib(n - 1) + fib(n - 2);
    }
}

static void create_data(elem_t **elem)
{
    *elem = (elem_t*) malloc(sizeof(elem_t));
    (*elem)->data = FIBONACCI_MAX;
}

/*
 * Consumer-Funktion
 * tritt in den krit. Bereich
 * überprüft, ob etwas im Puffer liegt
 * wenn ja, wird es entnommen
 * und der krit. Bereich wird wieder verlassen
 */
static void *consumer_func(void *args) 
{
    int done = 0;
    elem_t *elem;
    
    while(1) {

        elem = NULL;
        
        pthread_mutex_lock(&queue_lock);
        
        if( get_size(&buffer) > 0 ) {
            /* Entnehme eine Aufgabe */
            remove_elem(&buffer, &elem);
            
        }        

        done = production_done;
        
        pthread_mutex_unlock(&queue_lock);
        
        if( elem != NULL ) {
            fib( elem->data );
            free(elem);
            printf("item consumed\n");
        } else if( done == 1 ) {
            break;
        }
        
    }
    
    return NULL;
}

/*
 * Producer-Funktion
 * tritt in den krit. Bereich
 * überprüft, ob Puffer voll ist
 * wenn nein, wird ein neues Element abgelegt
 * und der krit. Bereich wird wieder verlassen
 */
static void *producer_func(void *args) 
{
    int done = 0;    
    
    while( 1 ) {
        
        pthread_mutex_lock(&queue_lock);

        if( get_size(&buffer) < MAX_QUEUE_LENGTH ) {
            /* Erzeuge eine Aufgabe */
            elem_t *elem;
            create_data(&elem);
            append_elem(&buffer, elem);
            count_proc++;
            printf("item produced\n");
        }        

        if( count_proc >= MAX_COUNT ) {
            done = production_done = 1;
        }

        pthread_mutex_unlock(&queue_lock);
        
        if( done ) {
            break;
        }
    }
    return NULL;
}


int main (int argc, char *argv[])
{    
    pthread_t cons_thread[NUM_CONSUMER];
    pthread_t prod_thread;
    int i;
    
    pthread_mutex_init(&queue_lock, NULL);
    
    init_list(&buffer);
    
    for(i=0; i<NUM_CONSUMER; i++) {
        pthread_create(&cons_thread[i], NULL, &consumer_func, NULL);
    }
    
    pthread_create(&prod_thread, NULL, &producer_func, NULL);
    
    for(i=0; i<NUM_CONSUMER; i++) {
        pthread_join(cons_thread[i], NULL);
    }
    pthread_join(prod_thread, NULL);
    
    pthread_mutex_destroy(&queue_lock);
    
    return 0;
}