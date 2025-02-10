#include <ctype.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>

#include "server.h"
#include "errors.h"
#include "../utils/server_utils.h"
#include "../utils/thread_utils.h"
#include "../constants/error_codes.h"

void clean_up(Thread *threads);
void clean_up(Thread *threads)
{
    int thread_closing = remove_threads(&threads);

    if (thread_closing < 0)
    {
        handle_error(ERROR_THREAD_CLOSING); // TODO: Forward the amount of threads unable to close
    }
}

int server(client_handler handler)
{
    int socketfd = set_up_server();

    if (socketfd < 0)
        return socketfd;

    Thread threads = thread_pool();

    while (1)
    {
        int *new_socket = accept_client(socketfd);

        if (!new_socket)
            continue;

        int thread_creation = create_thread(&threads, handler, new_socket);

        if (thread_creation < 0)
        {
            handle_error(ERROR_THREAD_CREATION);
            free(new_socket);
            close_socket(*new_socket);
        };
    }

    clean_up(&threads);

    return close_socket(socketfd) < 0 ? -1 : 0;
}