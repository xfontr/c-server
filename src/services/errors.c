#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <error_codes.h>

static void print_error(short error_code, char *message);

void print_error(short error_code, char *message)
{
    if (errno == 0)
    {
        printf("Error %d: %s\n", error_code, message);
    }
    else
    {
        printf("Error %d: %s - %s\n", error_code, message, strerror(errno));
        errno = 0;
    }
}

void handle_error(short error_code, char *additional_info)
{
    char *message;

    switch (error_code)
    {
    case ERROR_SOCKET_CREATION:
        message = "Unable to create socket";
        break;

    case ERROR_SOCKET_BINDING:
        message = "Unable to bind the socket to the server";
        break;

    case ERROR_SOCKET_REUSABLE:
        message = "Could not set the socket connection to be reusable";
        break;

    case ERROR_SOCKET_LISTENING:
        message = "Could not listen for connections";
        break;

    case ERROR_SOCKET_CLIENT_CONNECTION:
        message = "Socket connection rejected";
        break;

    case ERROR_SOCKET_CLOSING:
        message = "Unable to close the selected socket";
        break;

    case ERROR_THREAD_CREATION:
        message = "Unable to create thread";
        break;

    case ERROR_THREAD_LIMIT:
        message = "Reached the maximum number of threads";
        break;

    case ERROR_THREAD_CLOSING:
        assert(error_code == ERROR_THREAD_CLOSING);
        message = "Unable to close thread";
        break;

    case ERROR_MEMORY_ALLOCATION:
        message = "Could not allocate memory for the designated resource";
        break;

    default:
        error_code = ERROR_UNKNOWN;
        message = "Unknown error";
        break;
    }

    if (additional_info)
    {
        message = strcat(message, additional_info);
    }

    free(additional_info);

    print_error(error_code, message);
}
