#include <ctype.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <limits.h>
#include "../constants/error_codes.h"
#include "../constants/configs.h"
#include "../helpers/handle_error.h"

int create_socket();
int bind_socket(int socketfd);
int init_server(int socketfd);
int accept_connection(int socketfd);
int enable_port_reuse(int socketfd);
int close_socket(int socketfd);
struct sockaddr_in get_bind_address();
int check_errors(int result, short error_code);

struct sockaddr_in get_bind_address()
{
    return (struct sockaddr_in){
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(PORT)};
}

int check_errors(int result, short error_code)
{
    if (result < 0)
    {
        handle_error(error_code);
        return -1;
    }

    return result;
}

int close_socket(int socketfd)
{
    return check_errors(close(socketfd), ERROR_SOCKET_CLOSING);
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

    int new_socket = accept(socketfd, (struct sockaddr *)&client_address, &client_size);

    int result = check_errors(new_socket, ERROR_SOCKET_CLIENT_CONNECTION);

    if (result >= 0)
    {
        printf("Connection established\n");
    }

    return result;
}

int set_up_server()
{
    unsigned short status = 0;

    int socketfd = create_socket();

    if (socketfd >= 0)
    {
        status = enable_port_reuse(socketfd);
    }

    if (status >= 0)
    {
        status = bind_socket(socketfd);
    }

    if (status >= 0)
    {
        status = init_server(socketfd);
    }

    return status >= 0 ? socketfd : status;
}

int server()
{
    int socketfd = set_up_server();

    if (socketfd < 0)
        return -1;

    printf("%s\n", "Server started");

    while (1)
    {

        int new_socket = accept_connection(socketfd);

        // handle connection

        close_socket(new_socket);
    }

    close_socket(socketfd);

    return 1;
}