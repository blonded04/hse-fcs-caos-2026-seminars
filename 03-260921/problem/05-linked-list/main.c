#include <assert.h>

#include "linked_list.h"

// You may comment this line to test teacher's solution:
#define TEST_ME

int main(void) {
    list_t list;
    list_init(&list);

    list_push_back(&list, 1);
    assert(list.length == 1);
    assert(list_get(&list, 0) == 1);
    list_push_back(&list, 2);
    assert(list.length == 2);
    assert(list_get(&list, 0) == 1);
    assert(list_get(&list, 1) == 2);
    list_push_back(&list, 10);
    assert(list.length == 3);
    assert(list_get(&list, 0) == 1);
    assert(list_get(&list, 1) == 2);
    assert(list_get(&list, 2) == 10);

#ifdef TEST_ME

    node_t *pivot = list_find(&list, 5);
    assert(pivot == NULL);
    
    assert(list.length == 3);
    assert(list_get(&list, 0) == 1);
    assert(list_get(&list, 1) == 2);
    assert(list_get(&list, 2) == 10);

    pivot = list_find(&list, 2);
    assert(pivot != NULL);
    assert(pivot->value == 2);
    assert(list.length == 3);
    assert(list_get(&list, 0) == 1);
    assert(list_get(&list, 1) == 2);
    assert(list_get(&list, 2) == 10);

    list_insert(&list, pivot, 5);
    assert(pivot->next != NULL);
    assert(pivot->next->value == 5);
    assert(list.length == 4);
    assert(list_get(&list, 0) == 1);
    assert(list_get(&list, 1) == 2);
    assert(list_get(&list, 2) == 5);
    assert(list_get(&list, 3) == 10);

#endif  // TEST_ME

    list_destroy(&list);

    return 0;
}
