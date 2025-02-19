#include <ctype.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>

#include <thread_utils.h>
#include <configs.h>

static int create_thread(thread *thread_id, thread_handler handler);

/**
 * TODO: Consider detached threads (2nd param) depending on the thread pattern used
 */
int create_thread(thread *thread_id, thread_handler handler)
{
    return pthread_create(thread_id, NULL, handler, NULL);
}

int create_threads(thread *threads, thread_handler handler, int size)
{
    int success_count = 0;

    for (int i = 0; i < size; i++)
    {
        int thread_result = create_thread(&threads[i], handler);

        if (thread_result == 0)
            success_count++;
    }

    return success_count;
}

/**
 * @return Number of failed thread joins.
 */
int remove_threads(thread *threads, int size)
{
    int error_count = 0;

    for (int i = 0; i < size; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
            error_count++;
    }

    return error_count;
}
