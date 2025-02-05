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
int check_errors(int result, int socketfd, short error_code);

struct sockaddr_in get_bind_address()
{
    return (struct sockaddr_in){
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(PORT)};
}

int close_socket(int socketfd)
{
    if (socketfd != INT_MIN & close(socketfd) < 0)
    {
        handle_error(ERROR_CLOSING);
        return -1;
    };

    return 0;
}

int check_errors(int result, int socketfd, short error_code)
{
    if (result < 0)
    {
        handle_error(error_code);
        close_socket(socketfd);
        return -1;
    }

    return result;
}

int enable_port_reuse(int socketfd)
{
    int enable = 1;
    int set_options_result = setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
    return check_errors(set_options_result, socketfd, ERROR_REUSABLE_SOCKET);
}

int create_socket()
{
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    return check_errors(socketfd, socketfd, ERROR_SOCKET_CREATION);
}

int bind_socket(int socketfd)
{
    struct sockaddr_in server_address = get_bind_address();

    int binding = bind(socketfd, (struct sockaddr *)&server_address, sizeof(server_address));

    return check_errors(binding, socketfd, ERROR_BINDING);
}

int init_server(int socketfd)
{
    return check_errors(listen(socketfd, MAX_CONNECTIONS), socketfd, ERROR_LISTENING);
}

int accept_connection(int socketfd)
{
    struct sockaddr_in client_address;
    socklen_t client_size = sizeof(client_address);

    int new_socket = accept(socketfd, (struct sockaddr *)&client_address, &client_size);

    int result = check_errors(new_socket, INT_MIN, ERROR_ACCEPT_CONNECTION);

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