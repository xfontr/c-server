#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "../constants/error_codes.h"

void print_error(short error_code, char *message);

void print_error(short error_code, char *message)
{
    printf("Error %d: %s - %s\n", error_code, message, strerror(errno));
}

void handle_error(short error_code)
{
    char *message;

    switch (error_code)
    {
    case ERROR_SOCKET_CREATION:
        message = "Unable to create socket";
        break;

    case ERROR_BINDING:
        message = "Unable to bind the socket to the server";
        break;

    case ERROR_LISTENING:
        message = "Could not listen for connections";
        break;

    case ERROR_ACCEPT_CONNECTION:
        message = "Socket connection rejected";
        break;

    case ERROR_CLOSING:
        message = "Unable to close the server";
        break;

    case ERROR_REUSABLE_SOCKET:
        message = "Could not set the socket connection to be reusable";
        break;

    default:
        error_code = ERROR_UNKNOWN;
        message = "Unknown error";
        break;
    }

    print_error(error_code, message);
}
