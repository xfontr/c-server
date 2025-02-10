#ifndef SERVER
#define SERVER

typedef void *(*client_handler)(void *);

int server(client_handler callback);

#endif
