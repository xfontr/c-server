#include <ctype.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "threads.h"
#include "../constants/configs.h"

void log_thread(pthread_t thread_id, Thread *thread);

void log_thread(pthread_t thread_id, Thread *thread)
{
    thread->threads[thread->size] = thread_id;
    thread->size++;
}

int create_thread(Thread *thread, start_routine callback)
{
    if (thread->size >= MAX_CONNECTIONS)
    {
        return -1; // TODO: Thread-per-connection + thread-pool hybrid (we want a queue here, not a -1)
    }

    pthread_t thread_id;

    int thread_result = pthread_create(&thread_id, NULL, callback, NULL);

    if (thread_result >= 0)
        log_thread(thread_id, thread);

    return thread_result;
}

/**
 * Closes all threads and returns the number of failures.
 *
 * @return 0 if all threads closed successfully.
 *         -N if N threads failed to close.
 */
int remove_threads(Thread *thread)
{
    int error_count = 0;

    for (int i = 0; i <= thread->size; i++)
    {
        int remove_result = pthread_join(thread->threads[i], NULL);

        if (remove_result < 0)
            error_count--;

        thread->size = thread->size - 1;
    }

    return error_count;
}

Thread thread_pool()
{
    Thread thread = {
        .size = 0,
    };

    return thread;
}
