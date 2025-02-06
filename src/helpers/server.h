#ifndef SERVER
#define SERVER

#include <pthread.h>
#include "../constants/configs.h"

typedef struct
{
    pthread_t threads[MAX_CONNECTIONS];
    int size;
} Thread;

int server();

#endif