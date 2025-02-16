#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct node
{
    void *value;
    struct node *next;
} node;

node *create_node(void *value);
void add_node(node **head, void *value);
void print_all(node *head);

#endif
