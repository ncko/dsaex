#include <stdlib.h>
#include <dbg.h>
#include "dsa/linked_list.h"

List *List_create() { return NULL; }

void List_push(List *list, void *value) {}
void *List_pop(List *list) { return NULL; }
void List_unshift(List *list, void *value) {}
void *List_shift(List *list) { return NULL; }

List *List_copy(List *list) { return NULL; }
void List_join(List *list1, List *list2) {}
List **List_split(List *list, int index) { return NULL; }

void List_reverse(List *list) {}
void List_insert_sorted(List *list, void *value) {}

void List_free(List *list) {}
