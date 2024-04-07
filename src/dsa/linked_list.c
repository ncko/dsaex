#include <stdint.h>
#include <stdlib.h>
#include <dbg.h>
#include "dsa/linked_list.h"

List *List_create() { 
    List *list = calloc(1, sizeof(List));
    check_mem(list);
    list->count = 0;
    return list;

error:
    return NULL;
}

void List_push(List *list, void *value) {
    check(list, "list cannot be null");

    ListNode *node = calloc(1, sizeof(ListNode));
    node->value = value;

    if (list->count == 0) {
        list->first = node;
        list->last = node;
    } else {
        node->prev = list->last;
        list->last->next = node;
        list->last = node;
    }

    list->count += 1;

error:
    return;
}

void *List_pop(List *list) {
    check(list, "list cannot be null");

    if (list->count == 0) {
        return NULL;
    }

    ListNode *target = list->last;
    void *value = target->value;

    if (list->count == 1) {
        list->first = NULL;
        list->last = NULL;
    } else {
        list->last = target->prev;
        list->last->next = NULL;
    }

    free(target);
    list->count -= 1;
    return value;

error:
    return NULL;
}

void List_unshift(List *list, void *value) {
    check(list, "list cannot be null");

    ListNode *node = calloc(1, sizeof(ListNode));
    node->value = value;

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
    check(list, "list cannot be null");

    if (list->count == 0) {
        return NULL;
    }

    ListNode *target = list->first;
    void *value = target->value;

    if (list->count == 1) {
        list->first = NULL;
        list->last = NULL;
    } else {
        list->first = target->next;
        list->first->prev = NULL;
    }

    free(target);
    list->count -= 1;
    return value;

error:
    return NULL;
}

List *List_copy(List *list) {
    check(list, "list cannot be NULL");

    List *copy = List_create();
    check_mem(copy);

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
    check(list1, "list1 cannot be null");
    check(list2, "list2 cannot be null");

    if (list2->count == 0) {
        free(list2);
        return;
    }

    if (list1->count == 0) {
        List *tmp = list1;
        list1 = list2;
        free(tmp);
        return;
    }

    list1->last->next = list2->first;
    list2->first->prev = list1->last;
    list1->last = list2->last;
    list1->count += list2->count;
    free(list2);

error:
    return;
}

List **List_split(List *list, int index) {
    check(list, "list cannot be null");
    check(index >= 0, "index must be greater than or equal to zero");

    List **lists = calloc(2, sizeof(List *));

    if (index >= list->count || index == 0) {
        lists[0] = list;
        return lists;
    }

    List *list2 = List_create();
    check_mem(list2);

    ListNode *splitNode = list->first;
    for (int i = 0; i < index; i++) splitNode = splitNode->next;

    list2->first = splitNode;
    list2->last = list->last;
    list->last = splitNode->prev;
    splitNode->prev = NULL;
    list->last->next = NULL;
    list2->count = list->count - index;
    list->count -= list2->count;

    lists[0] = list;
    lists[1] = list2;
    return lists;

error:
    List_free(list2);
    return NULL;
}

void List_reverse(List *list) {
    check(list, "list cannot be NULL");
    if (list->count < 2) return;

    ListNode *curr = list->first;
    while(curr) {
        curr->next = (ListNode *)((uintptr_t)curr->next ^ (uintptr_t)curr->prev);
        curr->prev =  (ListNode *)((uintptr_t)curr->next ^ (uintptr_t)curr->prev);
        curr->next =  (ListNode *)((uintptr_t)curr->next ^ (uintptr_t)curr->prev);
        curr = curr->prev;
    }

    list->first = (ListNode *)((uintptr_t)list->first ^ (uintptr_t)list->last);
    list->last = (ListNode *)((uintptr_t)list->first ^ (uintptr_t)list->last);
    list->first = (ListNode *)((uintptr_t)list->first ^ (uintptr_t)list->last);
error:
    return;
}

void List_insert_sorted(List *list, void *value) {}

void List_free(List *list) {
    if (list) {
        ListNode *curr = List_pop(list);
        while(curr) curr = List_pop(list);
        free(list);
    }
}
