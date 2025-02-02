#include <ctype.h>
#include "./helpers/handle_server.h"
#include "./utils/utils.h"

int main()
{
    int socketfd = exit_on_fail(create_socket());

    exit_on_fail(bind_socket(socketfd));
    exit_on_fail(init_server(socketfd));
    exit_on_fail(accept_connection(socketfd));

    close_socket(socketfd);

    return 0;
}
