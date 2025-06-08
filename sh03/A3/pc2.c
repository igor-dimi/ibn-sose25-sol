#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mylist.h"

// Mutex to protect access to the shared queue
pthread_mutex_t queue_lock;

// Single condition variable used for both producers and consumers
pthread_cond_t cond_var;

// Shared buffer (a custom linked list acting as a queue)
list_t buffer;

// Counters for task management
int count_proc = 0;
int production_done = 0;

/********************************************************/
/* Function Declarations */

static unsigned long fib(unsigned int n);
static void create_data(elem_t **elem);
static void *consumer_func(void *);
static void *producer_func(void *);

/********************************************************/
/* Compute the nth Fibonacci number (CPU-intensive task) */
static unsigned long fib(unsigned int n)
{
    if (n == 0 || n == 1) {
        return n;
    } else {
        return fib(n - 1) + fib(n - 2);
    }
}

/* Allocate and initialize a new task node */
static void create_data(elem_t **elem)
{
    *elem = (elem_t*) malloc(sizeof(elem_t));
    (*elem)->data = FIBONACCI_MAX;
}

/* Consumer thread function */
static void *consumer_func(void *args) 
{
    elem_t *elem;

    while (1) {
        pthread_mutex_lock(&queue_lock);

        // Wait if the queue is empty and production is not yet complete
        while (get_size(&buffer) == 0 && !production_done) {
            pthread_cond_wait(&cond_var, &queue_lock);
        }

        // Exit condition: queue is empty and production has finished
        if (get_size(&buffer) == 0 && production_done) {
            pthread_mutex_unlock(&queue_lock);
            break;
        }

        // Remove an item from the queue
        remove_elem(&buffer, &elem);

        // Wake up a potentially waiting producer
        pthread_cond_signal(&cond_var);

        pthread_mutex_unlock(&queue_lock);

        // Process the task
        fib(elem->data);
        free(elem);
        printf("item consumed\n");
    }

    return NULL;
}

/* Producer thread function */
static void *producer_func(void *args) 
{
    while (1) {
        pthread_mutex_lock(&queue_lock);

        // Wait if the buffer is full
        while (get_size(&buffer) >= MAX_QUEUE_LENGTH) {
            pthread_cond_wait(&cond_var, &queue_lock);
        }

        if (count_proc < MAX_COUNT) {
            // Create and append a new task to the queue
            elem_t *elem;
            create_data(&elem);
            append_elem(&buffer, elem);
            count_proc++;
            printf("item produced\n");

            // Wake up one waiting consumer
            pthread_cond_signal(&cond_var);
        }

        // If production is done, notify all consumers and exit
        if (count_proc >= MAX_COUNT) {
            production_done = 1;

            // Wake up all consumers waiting on cond_var so they can check the exit condition
            pthread_cond_broadcast(&cond_var);

            pthread_mutex_unlock(&queue_lock);
            break;
        }

        pthread_mutex_unlock(&queue_lock);
    }

    return NULL;
}

/* Main function */
int main (int argc, char *argv[])
{
    pthread_t cons_thread[NUM_CONSUMER];
    pthread_t prod_thread;
    int i;

    // Initialize mutex and condition variable
    pthread_mutex_init(&queue_lock, NULL);
    pthread_cond_init(&cond_var, NULL);
    
    init_list(&buffer);

    // Start consumer threads
    for (i = 0; i < NUM_CONSUMER; i++) {
        pthread_create(&cons_thread[i], NULL, &consumer_func, NULL);
    }

    // Start producer thread
    pthread_create(&prod_thread, NULL, &producer_func, NULL);

    // Wait for all consumer threads to finish
    for (i = 0; i < NUM_CONSUMER; i++) {
        pthread_join(cons_thread[i], NULL);
    }

    // Wait for producer thread to finish
    pthread_join(prod_thread, NULL);

    // Cleanup
    pthread_mutex_destroy(&queue_lock);
    pthread_cond_destroy(&cond_var);

    return 0;
}
