#include <ctype.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>     // close
#include <netinet/in.h> // sockaddr_in
#include <limits.h>     // INT_MAX
#include <stdlib.h>     // malloc, free

#include <server_utils.h>
#include <services/errors.h>
#include <constants/error_codes.h>
#include <constants/configs.h>

static int create_socket();
static int bind_socket(int socketfd);
static int init_server(int socketfd);
static int accept_connection(int socketfd);
static int enable_port_reuse(int socketfd);
static struct sockaddr_in get_bind_address();
static int set_up_error(int socketfd, int error_code);

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
        handle_error(ERROR_SOCKET_CLOSING, NULL);
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

int *accept_client(int socketfd)
{
    int new_socket = accept_connection(socketfd);

    if (new_socket < 0)
    {
        handle_error(ERROR_SOCKET_CLIENT_CONNECTION, NULL);
        return NULL;
    }

    int *new_socket_ptr = malloc(sizeof(new_socket));

    if (!new_socket_ptr)
    {
        handle_error(ERROR_MEMORY_ALLOCATION, NULL);
        close_socket(new_socket);
        return NULL;
    }

    *new_socket_ptr = new_socket;

    return new_socket_ptr;
};
