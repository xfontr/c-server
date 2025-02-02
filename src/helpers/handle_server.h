#ifndef HANDLE_SERVER
#define HANDLE_SERVER

int create_socket();
int bind_socket(int socketfd);
int init_server(int socketfd);
int accept_connection(int socketfd);

struct sockaddr_in get_bind_address();
int check_connection(int result, int socketfd, short error_code);
int close_socket(int socketfd);

#endif