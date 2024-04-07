#ifndef _DSA_LINKED_LIST_H_
#define _DSA_LINKED_LIST_H_

typedef struct ListNode {
    struct ListNode *prev;
    struct ListNode *next;
    void *value;
} ListNode;

typedef struct List {
    int count;
    ListNode *first;
    ListNode *last;
} List;

List *List_create();

void List_push(List *list, void *value);
void *List_pop(List *list);
void List_unshift(List *list, void *value);
void *List_shift(List *list);

List *List_copy(List *list);
void List_join(List *list1, List *list2);
List **List_split(List *list, int index);

void List_reverse(List *list);
void List_insert_sorted(List *list, void *value);

void List_free(List *list);

#endif
