#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <linked_list.h>

node *create_node(void *value)
{
    node *new_node = malloc(sizeof(node));
    if (!new_node)
        return NULL;

    new_node->value = value;
    new_node->next = NULL;

    return new_node;
}

void add_node(node **head, void *value)
{
    node *new_node = create_node(value);
    if (!new_node)
        return;

    new_node->next = *head;
    *head = new_node;
}

void print_all(node *head)
{
    node *current = head;

    while (current != NULL)
    {
        printf("%s\n", (char *)current->value);
        current = current->next;
    }
}
