#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <linked_list.h>

void enqueue(node **head, node **tail, void *value)
{
    node *new_node = create_node(value);
    new_node->value = value;

    if (*tail == NULL)
    {
        *head = new_node;
    }
    else
    {
        (*tail)->next = new_node;
    }

    *tail = new_node;
}

void *dequeue(node **head, node **tail)
{
    if (*head == NULL)
        return NULL;

    void *value = (*head)->value;

    node *old_head = *head;
    *head = (*head)->next;

    if (*head == NULL)
        *tail = NULL;

    free(old_head);

    return value;
}