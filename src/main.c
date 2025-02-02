#include <ctype.h>
#include "./helpers/handle_server.h"

int main()
{
    int connection = open_connection();

    if (connection == 1)
    {
        return 1;
    }

    close_connection(&connection);

    return 0;
}