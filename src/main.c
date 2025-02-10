#include <ctype.h>
#include <stdio.h>
#include "./helpers/server.h"
#include "./helpers/handle_error.h"

int main()
{
    int result = server();

    if (result < 0)
    {
        handle_error(result);
        return -1;
    }

    return 0;
}
