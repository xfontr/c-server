#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <error_codes.h>
#include <error_messages.h>

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
        message = ERROR_MSG_SOCKET_CREATION;
        break;

    case ERROR_SOCKET_BINDING:
        message = ERROR_MSG_SOCKET_BINDING;
        break;

    case ERROR_SOCKET_REUSABLE:
        message = ERROR_MSG_SOCKET_REUSABLE;
        break;

    case ERROR_SOCKET_LISTENING:
        message = ERROR_MSG_SOCKET_LISTENING;
        break;

    case ERROR_SOCKET_CLIENT_CONNECTION:
        message = ERROR_MSG_SOCKET_CLIENT_CONNECTION;
        break;

    case ERROR_SOCKET_CLOSING:
        message = ERROR_MSG_SOCKET_CLOSING;
        break;

    case ERROR_THREAD_CREATION:
        message = ERROR_MSG_THREAD_CREATION;
        break;

    case ERROR_THREAD_LIMIT:
        message = ERROR_MSG_THREAD_LIMIT;
        break;

    case ERROR_THREAD_CLOSING:
        message = ERROR_MSG_THREAD_CLOSING;
        break;

    case ERROR_MEMORY_ALLOCATION:
        message = ERROR_MSG_MEMORY_ALLOCATION;
        break;

    default:
        error_code = ERROR_UNKNOWN;
        message = ERROR_MSG_UNKNOWN;
        break;
    }

    if (additional_info)
    {
        message = strcat(message, additional_info);
    }

    free(additional_info);

    print_error(error_code, message);
}
