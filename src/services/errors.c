#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <error_message.h>

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
    char *message = error_message(error_code);

    if (additional_info)
    {
        message = strcat(message, additional_info);
    }

    free(additional_info);

    print_error(error_code, message);
}
