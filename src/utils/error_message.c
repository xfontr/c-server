#include <ctype.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <error_codes.h>
#include <error_messages.h>

char *error_message(int error_code)
{
    char *message;

    switch (error_code)
    {

//-automated-code-begins - timestamp: 15/2/2025 - 21:8
    
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

    case ERROR_UNKNOWN:
        message = ERROR_MSG_UNKNOWN;
        break;

//-automated-code-ends

    default:
        message = ERROR_MSG_UNKNOWN;
        break;
    }

    assert(strncmp(&message[0], "", 1) != 0 && &message[0] != NULL);

    return message;
}