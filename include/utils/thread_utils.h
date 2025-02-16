#ifndef THREADS
#define THREADS

#include <pthread.h>

#include <configs.h>

typedef void *(*thread_handler)(void *);

typedef pthread_t thread;

int create_threads(thread *threads, thread_handler callback, int size);
int remove_threads(thread *threads, int size);

#endif