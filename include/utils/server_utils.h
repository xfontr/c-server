#ifndef SERVER_UTILS
#define SERVER_UTILS

int set_up_server();
int *accept_client(int socketfd);
int close_socket(int socketfd);

#endif
