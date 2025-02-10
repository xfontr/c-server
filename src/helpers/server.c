#include <ctype.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>     // close
#include <netinet/in.h> // sockaddr_in
#include <limits.h>     // INT_MAX
#include "../constants/error_codes.h"
#include "../constants/configs.h"
#include "../helpers/handle_error.h"
#include "./threads.h"

int create_socket();
int bind_socket(int socketfd);
int init_server(int socketfd);
int accept_connection(int socketfd);
int enable_port_reuse(int socketfd);
int close_socket(int socketfd);
struct sockaddr_in get_bind_address();
int set_up_server();
int set_up_error(int socketfd, int error_code);

struct sockaddr_in get_bind_address()
{
    return (struct sockaddr_in){
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(PORT)};
}

int close_socket(int socketfd)
{
    if (close(socketfd) < 0)
    {
        handle_error(ERROR_SOCKET_CLOSING);
        return -1;
    }

    return 1;
}

int enable_port_reuse(int socketfd)
{
    int enable = 1;
    return setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
}

int create_socket()
{
    return socket(AF_INET, SOCK_STREAM, 0);
}

int bind_socket(int socketfd)
{
    struct sockaddr_in server_address = get_bind_address();

    return bind(socketfd, (struct sockaddr *)&server_address, sizeof(server_address));
}

int init_server(int socketfd)
{
    return listen(socketfd, MAX_CONNECTIONS);
}

int accept_connection(int socketfd)
{
    struct sockaddr_in client_address;
    socklen_t client_size = sizeof(client_address);

    return accept(socketfd, (struct sockaddr *)&client_address, &client_size);
}

int set_up_error(int socketfd, int error_code)
{
    close_socket(socketfd);
    return error_code;
}

int set_up_server()
{
    int socketfd = create_socket();

    if (socketfd < 0)
        return ERROR_SOCKET_CREATION;

    if (enable_port_reuse(socketfd) < 0)
        return set_up_error(socketfd, ERROR_SOCKET_REUSABLE);

    if (bind_socket(socketfd) < 0)
        return set_up_error(socketfd, ERROR_SOCKET_BINDING);

    if (init_server(socketfd) < 0)
        return set_up_error(socketfd, ERROR_SOCKET_LISTENING);

    return socketfd;
}

void *handle_thread(void *vargp)
{
    puts("Connection");
}

int server()
{
    int socketfd = set_up_server();

    if (socketfd < 0)
        return socketfd;

    puts("Server started");

    Thread threads = thread_pool();

    while (1)
    {
        int new_socket = accept_connection(socketfd);

        if (new_socket < 0)
        {
            handle_error(ERROR_SOCKET_CLIENT_CONNECTION);
        }
        else
        {
            int thread_creation = create_thread(&threads, handle_thread);

            if (thread_creation < 0)
            {
                handle_error(ERROR_THREAD_CREATION);
                close_socket(new_socket);
            }
        }

        close_socket(new_socket);
    }

    int thread_closing = remove_threads(&threads);

    if (thread_closing < 0)
    {
        handle_error(ERROR_THREAD_CLOSING); // TODO: Forward the amount of threads unable to close
    }

    return close_socket(socketfd) < 0 ? -1 : 0;
}