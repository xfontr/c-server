#include <ctype.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdbool.h>

#include <server.h>
#include <errors.h>
#include <server_utils.h>
#include <thread_utils.h>
#include <error_codes.h>

static void clean_up(Thread *threads);
static int check_thread(int thread_creation, int *new_socket);

void clean_up(Thread *threads)
{
    int thread_closing = remove_threads(&threads);

    if (thread_closing < 0)
    {
        handle_error(ERROR_THREAD_CLOSING, NULL); // TODO: Forward the amount of threads unable to close
    }
}

int check_thread(int thread_creation, int *new_socket)
{
    if (thread_creation < 0)
    {
        handle_error(ERROR_THREAD_CREATION, NULL);
        free(new_socket);
        close_socket(*new_socket);
    }
}

int server(client_handler handler)
{
    int socketfd = set_up_server();

    if (socketfd < 0)
        return socketfd;

    Thread threads = thread_pool();

    while (true)
    {
        int *new_socket = accept_client(socketfd);

        if (!new_socket)
            continue;

        int thread_limit = check_thread_size(&threads);

        if (thread_limit < 0)
        {
            handle_error(ERROR_THREAD_LIMIT, NULL);
        }
        else
        {
            int thread_creation = create_thread(&threads, handler, new_socket);
            check_thread(thread_creation, new_socket);
        }
    }

    clean_up(&threads);

    return close_socket(socketfd) < 0 ? -1 : 0;
}