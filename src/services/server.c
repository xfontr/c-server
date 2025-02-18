#include <ctype.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include <server.h>
#include <errors.h>
#include <server_utils.h>
#include <thread_utils.h>
#include <error_codes.h>
#include <queue.h>
#include <linked_list.h>

static void clean_up(thread *threads);
void set_up_threads(thread *threads);

client_handler main_handler;
node **head = NULL;
node **tail = NULL;

void clean_up(thread *threads)
{
    int thread_closing = remove_threads(threads, MAX_THREADS);

    if (thread_closing != MAX_THREADS)
    {
        handle_error(ERROR_THREAD_CLOSING, NULL); // TODO
    }
}

static void *thread_handle()
{
    assert(main_handler != NULL);

    while (true)
    {
        void *value = dequeue(&head, &tail);

        if (value != NULL)
        {
            main_handler(value);
        }
    }
}

void set_up_threads(thread *threads)
{
    int thread_creating = create_threads(threads, thread_handle, MAX_THREADS);

    if (thread_creating != MAX_THREADS)
    {
        handle_error(ERROR_THREAD_CREATION, NULL); // TODO
    }
}

int server(client_handler handler)
{
    main_handler = handler;

    int socketfd = set_up_server();

    if (socketfd < 0)
        return socketfd;

    puts("Server successfully set up");

    thread threads[MAX_THREADS];

    set_up_threads(threads);

    puts("Listening for clients:");

    while (true)
    {
        int *new_socket = accept_client(socketfd);

        if (!new_socket)
            continue;

        enqueue(&head, &tail, new_socket);
    }

    clean_up(threads);

    return close_socket(socketfd) < 0 ? -1 : 0;
}