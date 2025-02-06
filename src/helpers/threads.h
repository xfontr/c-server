#ifndef THREADS
#define THREADS

#include <pthread.h>
#include "../constants/configs.h"

typedef struct
{
    pthread_t threads[MAX_CONNECTIONS];
    int size;
} Thread;

typedef void *(*start_routine)(void *);

void remove_threads(Thread *thread);
int create_thread(Thread *thread, start_routine callback);
Thread thread_pool();

void thread_test();

#endif