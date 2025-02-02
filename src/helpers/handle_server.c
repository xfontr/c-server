#include <ctype.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include "../constants/error_codes.h"
#include "../constants/configs.h"
#include "../helpers/handle_error.h"

struct sockaddr_in get_bind_address();
int check_connection(int result, short error_code);
int close_socket(int socketfd);

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
        handle_error(ERROR_CLOSING);
        return -1;
    };

    return 0;
}

int check_connection(int result, short error_code)
{
    if (error_code < 0)
    {
        handle_error(error_code);
        close_socket(result);
        return -1;
    }

    return result;
}

int create_socket()
{
    return check_connection(socket(AF_INET, SOCK_STREAM, 0), ERROR_SOCKET_CREATION);
}

int bind_socket(int socketfd)
{
    struct sockaddr_in server_address = get_bind_address();

    int binding = bind(socketfd, (struct sockaddr *)&server_address, sizeof(server_address));

    return check_connection(binding, ERROR_BINDING);
}

int init_server(int socketfd)
{
    return check_connection(listen(socketfd, MAX_CONNECTIONS), ERROR_LISTENING);
}

int accept_connection(int socketfd)
{
    struct sockaddr_in client_address;
    socklen_t client_size = sizeof(client_address);

    int new_socket = accept(socketfd, (struct sockaddr *)&client_address, &client_size);

    return check_connection(new_socket, ERROR_ACCEPT_CONNECTION);
}
