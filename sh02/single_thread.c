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
    for (int i = 0; i < NUM_THREADS; i++) {
        TaskCode(&i);
    }

    return 0;
}
