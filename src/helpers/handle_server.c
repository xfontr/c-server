#include <ctype.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include "../constants/error_codes.h"
#include "../helpers/handle_error.h"

struct sockaddr_in get_bind_address()
{
    return (struct sockaddr_in){
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(8080)};
}

int open_connection()
{
    int connection = socket(AF_INET, SOCK_STREAM, 0);

    if (connection < 0)
    {
        handle_error(ERROR_SOCKET_CREATION);
        return -1;
    }

    return connection;
}

int init_server(int connection)
{
    struct sockaddr_in server = get_bind_address();

    int binding = bind(connection, (struct sockaddr *)&server, sizeof(server));

    if (binding < 0)
    {
        handle_error(ERROR_BINDING);
        return -1;
    }

    return binding;
}

int close_connection(int connection)
{
    if (close(connection) < 0)
    {
        handle_error(ERROR_CLOSING);
        return -1;
    };

    return 0;
}