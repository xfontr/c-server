#ifndef THREADS
#define THREADS

#include <pthread.h>
#include "../constants/configs.h"

typedef struct
{
    pthread_t threads[MAX_CONNECTIONS];
    int size;
} Thread;

void remove_threads(pthread_t thread_id, Thread *thread);
int create_thread(Thread *thread);
Thread thread_pool();

#endif