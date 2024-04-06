#ifndef _DSA_LINKED_LIST_H_
#define _DSA_LINKED_LIST_H_

typedef struct List {
} List;

List *List_create();
void List_push(List *list, void *value);
void *List_pop(List *list);
void List_unshift(List *list, void *value);
void *List_shift(List *list);
void List_free(List *list);

#endif
