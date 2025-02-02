#include <ctype.h>
#include "./helpers/handle_server.h"

int main()
{
    int connection = exit_on_fail(open_connection());

    exit_on_fail(init_server(connection));

    close_connection(&connection);

    return 0;
}
