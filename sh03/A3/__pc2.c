#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mylist.h"

pthread_mutex_t queue_lock;
pthread_cond_t not_empty;
pthread_cond_t not_full;

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
    } else {
        return fib(n - 1) + fib(n - 2);
    }
}

static void create_data(elem_t **elem)
{
    *elem = (elem_t*) malloc(sizeof(elem_t));
    (*elem)->data = FIBONACCI_MAX;
}

static void *consumer_func(void *args) 
{
    elem_t *elem;

    while (1) {
        pthread_mutex_lock(&queue_lock);

        while (get_size(&buffer) == 0 && !production_done) {
            pthread_cond_wait(&not_empty, &queue_lock);
        }

        // If queue is still empty and production is done, exit
        if (get_size(&buffer) == 0 && production_done) {
            pthread_mutex_unlock(&queue_lock);
            break;
        }

        // Remove task
        remove_elem(&buffer, &elem);
        pthread_cond_signal(&not_full); // Notify producer there's space
        pthread_mutex_unlock(&queue_lock);

        // Process task
        fib(elem->data);
        free(elem);
        printf("item consumed\n");
    }

    return NULL;
}

static void *producer_func(void *args) 
{
    while (1) {
        pthread_mutex_lock(&queue_lock);

        while (get_size(&buffer) >= MAX_QUEUE_LENGTH) {
            pthread_cond_wait(&not_full, &queue_lock);
        }

        if (count_proc < MAX_COUNT) {
            elem_t *elem;
            create_data(&elem);
            append_elem(&buffer, elem);
            count_proc++;
            printf("item produced\n");

            pthread_cond_signal(&not_empty); // Notify consumers there's work
        }

        if (count_proc >= MAX_COUNT) {
            production_done = 1;
            pthread_cond_broadcast(&not_empty); // Wake all consumers to exit
            pthread_mutex_unlock(&queue_lock);
            break;
        }

        pthread_mutex_unlock(&queue_lock);
    }

    return NULL;
}

int main (int argc, char *argv[])
{
    pthread_t cons_thread[NUM_CONSUMER];
    pthread_t prod_thread;
    int i;

    pthread_mutex_init(&queue_lock, NULL);
    pthread_cond_init(&not_empty, NULL);
    pthread_cond_init(&not_full, NULL);
    
    init_list(&buffer);

    for (i = 0; i < NUM_CONSUMER; i++) {
        pthread_create(&cons_thread[i], NULL, &consumer_func, NULL);
    }

    pthread_create(&prod_thread, NULL, &producer_func, NULL);

    for (i = 0; i < NUM_CONSUMER; i++) {
        pthread_join(cons_thread[i], NULL);
    }
    pthread_join(prod_thread, NULL);

    pthread_mutex_destroy(&queue_lock);
    pthread_cond_destroy(&not_empty);
    pthread_cond_destroy(&not_full);

    return 0;
}
