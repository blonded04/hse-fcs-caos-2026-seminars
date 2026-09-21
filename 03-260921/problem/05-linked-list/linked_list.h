#ifndef LINKED_LIST_H_INCLUDED_
#define LINKED_LIST_H_INCLUDED_

#include <stddef.h>

typedef struct node {
    int value;
    struct node *next;
} node_t;

typedef struct list {
   node_t *head;
   size_t length;
} list_t;

void list_init(list_t *list);  // TODO
void list_destroy(list_t *list);  // TODO
void list_push_back(list_t *list, int value);
int list_get(list_t *list, size_t index);
node_t* list_find(list_t *list, int value);  // TODO
void list_insert(list_t *list, node_t *previous, int value);  // TODO

#endif  // LINKED_LIST_H_INCLUDED
