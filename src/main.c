#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "./services/server.h"
#include "./utils/server_utils.h"
#include "./services/errors.h"
#include "./constants/error_codes.h"

void *handler(void *new_socket)
{
    puts("Connection");
    int client_socket = *(int *)new_socket;

    // Actual handler

    close_socket(client_socket);
    free(new_socket);
}

int main()
{
    puts("Server on");

    int result = server(handler);

    if (result < 0)
    {
        handle_error(result);
        return -1;
    }

    return 0;
}
