#ifndef QUEUE
#define QUEUE

#include <linked_list.h>

void enqueue(node **head, node **tail, void *value);
void *dequeue(node **head, node **tail);

#endif
