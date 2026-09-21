#include "linked_list.h"

#include <stdlib.h>

void list_push_back(list_t *list, int value) {
    node_t **last_node_ptr = &list->head;
    while (*last_node_ptr) {
        last_node_ptr = &(*last_node_ptr)->next;
    }

    *last_node_ptr = malloc(sizeof(**last_node_ptr));
    // if (last_node_ptr == NULL) { ... }
    (*last_node_ptr)->value = value;
    (*last_node_ptr)->next = NULL;
    list->length++;
}

int list_get(list_t *list, size_t index) {
    // if (index >= list->length) { ... }

    node_t *node_ptr = list->head;
    while (index) {
        node_ptr = node_ptr->next;
        index--;
    }
    
    return node_ptr->value;
}
