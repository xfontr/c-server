#include <ctype.h>
#include <stdio.h>
#include <sys/socket.h>

sockfd;

int main()
{
    int connection = socket(AF_INET, SOCK_STREAM, 0);

    if (connection < 0)
    {
        fprintf(stderr, "Error\n");
        return 1;
    }

    return 0;
}