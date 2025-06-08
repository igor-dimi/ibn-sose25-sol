#include <pthread.h>
#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>

#define NUM_THREADS 200000

void* TaskCode (void* argument)
{
    int tid = *((int*) argument);
    printf("number: %d\n", tid);
    printf("ending thread %d\n", tid);
    return NULL;
}

int main()
{
    pthread_t thread;
    int thread_arg;

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_arg = i;
        printf("creating thread %d\n", i);
        int rc = pthread_create(&thread, NULL, TaskCode, &thread_arg);
        assert(rc == 0);
        rc = pthread_join(thread, NULL);
        assert(rc == 0);
    }

    return 0;
}
