#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "../constants/error_codes.h"

char print_error(short error_code, char *message);

char print_error(short error_code, char *message)
{
    printf("Error %d: %s - %s\n", error_code, message, strerror(errno));
}

void handle_error(short error_code)
{
    char *message;

    switch (error_code)
    {
    case ERROR_SOCKET_CREATION:
        message = "Could not create socket";
        break;

    case ERROR_BINDING:
        message = "Could not connect to server";
        break;

    case ERROR_CLOSING:
        message = "Could not close the server";
        break;

    default:
        message = "Unknown error";
        break;
    }

    print_error(error_code | ERROR_UNKNOWN, message);
}
