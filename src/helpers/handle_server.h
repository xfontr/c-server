#ifndef HANDLE_SERVER
#define HANDLE_SERVER

int create_socket();
int bind_socket(int socketfd);
int init_server(int socketfd);
int accept_connection(int socketfd);

#endif