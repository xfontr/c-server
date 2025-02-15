#include <ctype.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include <thread_utils.h>
#include <configs.h>

static void log_thread(pthread_t thread_id, Thread *thread);

void log_thread(pthread_t thread_id, Thread *thread)
{
    thread->threads[thread->size] = thread_id;
    thread->size++;
}

int check_thread_size(Thread *thread)
{
    if (thread->size >= MAX_THREADS)
    {
        return -1;
    }

    return 0;
}

int create_thread(Thread *thread, start_routine callback, callback_parameter arg)
{
    if (check_thread_size(thread) < 0)
        return -1;

    pthread_t thread_id;

    // TODO: Consider detached threads (2nd param) depending on the thread pattern used
    int thread_result = pthread_create(&thread_id, NULL, callback, arg);

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
