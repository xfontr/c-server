#include <ctype.h>
#include <stdio.h>
#include <pthread.h>
#include "threads.h"
#include "../constants/configs.h"

void log_thread(pthread_t thread_id, Thread *thread);

void log_thread(pthread_t thread_id, Thread *thread)
{
    thread->threads[thread->size] = thread_id;
    thread->size++;
}

int create_thread(Thread *thread)
{
    if (thread->size >= MAX_CONNECTIONS)
    {
        return -1;
    }

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, NULL, NULL);

    log_thread(thread_id, thread);
}

void remove_threads(pthread_t thread_id, Thread *thread)
{
    for (int i = 0; i < thread->size; i++)
    {
        pthread_join(thread->threads[i], NULL);
    }
}

Thread thread_pool()
{
    Thread thread = {
        .size = 0,
    };

    return thread;
}