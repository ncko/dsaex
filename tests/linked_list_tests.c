#include <stdlib.h>
#include <dsa/linked_list.h>
#include "minunit.h"

List *list;

char *test_list_create() {
    list = List_create();
    mu_assert(list, "List_create() returned a falsy value");
    mu_assert(list->count == 0, "Returned list does not have a proper count");

    return NULL;
}

char *test_list_push_pop() {
    List_push(list, "one");
    List_push(list, "two");
    List_push(list, "three");
    mu_assert(list->count == 3, "list count is not incremented");

    char *value = List_pop(list);
    mu_assert(strcmp(value, "three") == 0, "First pop value is incorrect");
    value = List_pop(list);
    mu_assert(strcmp(value, "two") == 0, "Second pop value is incorrect");
    value = List_pop(list);
    mu_assert(strcmp(value, "one") == 0, "Third pop value is incorrect");
    mu_assert(list->count == 0, "list count is not decremented");

    return NULL;
}

char *test_list_unshift_shift() {
    List_unshift(list, "one");
    List_unshift(list, "two");
    List_unshift(list, "three");
    mu_assert(list->count == 3, "list count is not incremented");

    char *value = List_shift(list);
    mu_assert(strcmp(value, "three") == 0, "First shift value is incorrect");
    value = List_shift(list);
    mu_assert(strcmp(value, "two") == 0, "Second shift value is incorrect");
    value = List_shift(list);
    mu_assert(strcmp(value, "one") == 0, "Third shift value is incorrect");
    mu_assert(list->count == 0, "list count is not decremented");

    return NULL;
}

char *test_list_queue() {
    List_push(list, "one");
    List_push(list, "two");
    List_push(list, "three");
    mu_assert(list->count == 3, "list count is not incremented");

    char *value = List_shift(list);
    mu_assert(strcmp(value, "one") == 0, "Out of order queue");
    value = List_shift(list);
    mu_assert(strcmp(value, "two") == 0, "Out of order queue");
    value = List_shift(list);
    mu_assert(strcmp(value, "three") == 0, "Out of order queue");

    return NULL;
}

char *test_list_copy() {
    char *strings[] = { "one", "two", "three" };

    for (int i = 0; i < 3; i++) List_push(list, strings[i]);

    List *copy = List_copy(list);

    ListNode *listCurr = list->first;
    ListNode *copyCurr = copy->first;
    while(listCurr) {
        mu_assert(listCurr->value == copyCurr->value, "List copy value ref mismatch");
        listCurr = listCurr->next;
        copyCurr = copyCurr->next;
    }

    List_clear(list);
    List_free(copy);

    return NULL;
}

char *test_list_join() {
    char *strings[] = { "one", "two", "three", "four", "five", "six" };

    for (int i = 0; i < 3; i++) List_push(list, strings[i]);

    List *list2 = List_create();
    for (int i = 3; i < 6; i++) List_push(list2, strings[i]);

    List_join(list, list2);

    for (int i = 0; i < 6; i++) {
        char *val = strings[i];
        char *curr = List_shift(list);
        mu_assert(val == curr, "List join ref mismatch");
    }

    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_list_create);
    mu_run_test(test_list_push_pop);
    mu_run_test(test_list_unshift_shift);
    mu_run_test(test_list_queue);
    mu_run_test(test_list_copy);
    mu_run_test(test_list_join);

    List_free(list);

    return NULL;
}

RUN_TESTS(all_tests)
