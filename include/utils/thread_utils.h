#ifndef THREADS
#define THREADS

#include <pthread.h>

#include <configs.h>

typedef void *(*thread_handler)(void *);

typedef pthread_t thread;
typedef pthread_mutex_t mutex;

int create_threads(thread *threads, thread_handler handler, int size);
int remove_threads(thread *threads, int size);

#endif