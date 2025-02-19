#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <sys/socket.h>

#include <server.h>
#include <server_utils.h>
#include <errors.h>
#include <constants/error_codes.h>

static void *handler(void *socketfd)
{
    int client_socket = *(int *)socketfd;

    const char *message = "Server response\n";
    send(client_socket, message, strlen(message), 0);

    close_socket(client_socket);
    free(socketfd);

    return NULL;
}

int main()
{
    int result = server(handler);

    if (result < 0)
    {
        handle_error(result, NULL);
        return -1;
    }

    return 0;
}
