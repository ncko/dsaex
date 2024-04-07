#include <stdlib.h>
#include <dbg.h>
#include "dsa/linked_list.h"

ListNode *ListNode_create(void *value) {
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);
    node->value = value;
    return node;
error:
    return NULL;
}

void List_clear(List *list) {
    check(list, "List cannot be NULL");
    while(List_pop(list)) {}

error:
    return;
}

List *List_create() {
    List *list = calloc(1, sizeof(List));
    check_mem(list);
    list->count = 0;
    return list;

error:
    return NULL;
}

void List_free(List *list) {
    if (list) {
        while(List_pop(list)) {}
        free(list);
    }
}

void List_push(List *list, void *value) {
    check(list, "List cannot be NULL");
    ListNode *node = ListNode_create(value);
    check(node, "node is NULL");

    if (list->count == 0) {
        list->first = node;
        list->last = node;
    } else {
        node->prev = list->last;
        list->last->next = node;
        list->last = node;
    }

    list->count += 1;

    // fall through
error:
    return;
}

void *List_pop(List *list) { 
    check(list, "List cannot be NULL");
    
    if (list->count == 0) {
        return NULL;
    }

    ListNode *target = list->last;
    void *value = target->value;
    list->last = target->prev;
    free(target);
    list->count -= 1;

    return value;

error:
    return NULL;
}

void List_unshift(List *list, void *value) {
    check(list, "List cannot be NULL");
    ListNode *node = ListNode_create(value);
    check(node, "node is NULL");

    if (list->count == 0) {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count += 1;

error:
    return;
}

void *List_shift(List *list) { 
    check(list, "List cannot be NULL");

    if (list->count == 0) {
        return NULL;
    }

    ListNode *target = list->first;
    void *value = target->value;
    list->first = target->next;
    free(target);
    list->count -= 1;

    return value;

error:
    return NULL;

}

List *List_copy(List *list) { 
    check(list, "List cannot be NULL");

    List *copy = List_create();
    if (list->count == 0) {
        return copy;
    }

    ListNode *curr = list->first;
    while(curr) {
        List_push(copy, curr->value);
        curr = curr->next;
    }

    return copy;

error:
    return NULL;
}

void List_join(List *list1, List *list2) {
    check(list1, "list1 cannot be NULL");
    check(list2, "list2 cannot be NULL");

    if (list2->count == 0) {
        return;
    }

    if (list1->count == 0) {
        list1 = list2;
        return;
    }

    list1->last->next = list2->first;
    list2->first->prev = list1->last;

    list1->last = list2->last;
    list2->first = list1->first;

    list1->count += list2->count;
    free(list2);

error:
    return;
}

List **List_split(List *list, int index) {
    return NULL;
}

void List_reverse(List *list) {}
void List_insert_sorted(List *list, void *value) {}

