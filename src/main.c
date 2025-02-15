#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <sys/socket.h>

#include "./services/server.h"
#include "./utils/server_utils.h"
#include "./services/errors.h"
#include "./constants/error_codes.h"

void *handler(void *new_socket)
{
    int client_socket = *(int *)new_socket;

    const char *message = "Server response\n";
    send(client_socket, message, strlen(message), 0);

    close_socket(client_socket);
    free(new_socket);
}

int main()
{
    puts("Server on");

    int result = server(handler);

    if (result < 0)
    {
        handle_error(result, NULL);
        return -1;
    }

    return 0;
}
