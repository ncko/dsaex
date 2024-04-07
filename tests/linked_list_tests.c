#include <stdlib.h>
#include <dsa/linked_list.h>
#include "minunit.h"

char *test_list_stack_functions() {
    List *list = List_create();
    mu_assert(list->count == 0, "Count is incorrect");

    List_push(list, "one");
    List_push(list, "two");
    List_push(list, "three");
    mu_assert(list->count == 3, "Count is incorrect");

    char *value = List_pop(list);
    mu_assert(strcmp(value, "three") == 0, "List_pop returned incorrect value");
    value = List_pop(list);
    mu_assert(strcmp(value, "two") == 0, "List_pop returned incorrect value");
    value = List_pop(list);
    mu_assert(strcmp(value, "one") == 0, "List_pop returned incorrect value");

    List_free(list);

    return NULL;
}

char *test_list_queue_functions() {
    List *list = List_create();
    mu_assert(list->count == 0, "Count is incorrect. Expected count: 0");

    List_unshift(list, "one");
    List_unshift(list, "two");
    List_unshift(list, "three");
    mu_assert(list->count == 3, "Count is incorrect. Expected count: 3");

    char *value = List_shift(list);
    mu_assert(strcmp(value, "three") == 0, "List_pop returned incorrect value");
    value = List_shift(list);
    mu_assert(strcmp(value, "two") == 0, "List_pop returned incorrect value");
    value = List_shift(list);
    mu_assert(strcmp(value, "one") == 0, "List_pop returned incorrect value");

    // previous tests were effectively a stack from the front of the list
    // lets try treating it as an actually queue

    List_push(list, "one");
    List_push(list, "two");
    List_push(list, "three");

    value = List_shift(list);
    mu_assert(strcmp(value, "one") == 0, "List_pop returned incorrect value");
    value = List_shift(list);
    mu_assert(strcmp(value, "two") == 0, "List_pop returned incorrect value");
    value = List_shift(list);
    mu_assert(strcmp(value, "three") == 0, "List_pop returned incorrect value");

    List_free(list);
    return NULL;
}

char *test_list_copy() {
    char *strings[] = { "one", "two", "three" };
    List *list = List_create();

    for (int i = 0; i < 3; i++) List_push(list, strings[i]);

    List *copy = List_copy(list);

    mu_assert(copy->count == list->count, "copy count does not match list count");

    char *listCurr = List_pop(list);
    char *copyCurr = List_pop(copy);
    while(listCurr) {
        mu_assert(strcmp(listCurr, copyCurr) == 0, "copy value mismatch");
        listCurr = List_pop(list);
        copyCurr = List_pop(copy);
    }

    List_free(list);
    List_free(copy);
    return NULL;
}

char *test_list_join() {
    List *list1 = List_create();
    List *list2 = List_create();

    List_push(list1, "one");
    List_push(list1, "two");
    List_push(list1, "three");

    List_push(list2, "four");
    List_push(list2, "five");
    List_push(list2, "six");

    List_join(list1, list2);
    mu_assert(list1->count == 6, "list1 count incorrect. Expected 6");

    char *value = List_pop(list1);
    mu_assert(strcmp(value, "six") == 0, "List copy value mismatch");
    value = List_pop(list1);
    mu_assert(strcmp(value, "five") == 0, "List copy value mismatch");
    value = List_pop(list1);
    mu_assert(strcmp(value, "four") == 0, "List copy value mismatch");
    value = List_pop(list1);
    mu_assert(strcmp(value, "three") == 0, "List copy value mismatch");
    value = List_pop(list1);
    mu_assert(strcmp(value, "two") == 0, "List copy value mismatch");
    value = List_pop(list1);
    mu_assert(strcmp(value, "one") == 0, "List copy value mismatch");
    mu_assert(list1->count == 0, "list1 count incorrect. Expected 0");

    List_free(list1);
    return NULL;
}

char *test_list_split() {
    List *list = List_create();
    char *strings[] = {"one", "two", "three", "four", "five", "six"};
    for (int i = 0; i < 6; i++) List_push(list, strings[i]);

    List **lists = List_split(list, 3);
    List *list1 = lists[0];
    List *list2 = lists[1];

    mu_assert(list1, "list1 is null");
    mu_assert(list2, "list2 is null");
    mu_assert(list1->count == 3, "list1 count is incorrect. Expected 3");
    mu_assert(list2->count == 3, "list2 count is incorrect. Expected 3");
    mu_assert(strcmp(list1->first->value, "one") == 0, "list1 first value is incorrect. Expected 'one'");
    mu_assert(strcmp(list1->last->value, "three") == 0, "list1 last value is incorrect. Expected 'three'");
    mu_assert(strcmp(list2->first->value, "four") == 0, "list2 first value is incorrect. Expected 'four'");
    mu_assert(strcmp(list2->last->value, "six") == 0, "list2 last value is incorrect. Expected 'six'");

    List_free(list1);
    List_free(list2);
    free(lists);
    return NULL;
}

char *test_list_reverse() {
    List *list = List_create();

    List_push(list, "one");
    List_push(list, "two");
    List_push(list, "three");

    List_reverse(list);

    char *value = List_pop(list);
    mu_assert(strcmp(value, "one") == 0, "List_reverse: List_pop returned incorrect value");
    value = List_pop(list);
    mu_assert(strcmp(value, "two") == 0, "List_reverse: List_pop returned incorrect value");
    value = List_pop(list);
    mu_assert(strcmp(value, "three") == 0, "List_reverse: List_pop returned incorrect value");

    List_free(list);
    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_list_stack_functions);
    mu_run_test(test_list_queue_functions);
    mu_run_test(test_list_copy);
    mu_run_test(test_list_join);
    mu_run_test(test_list_split);
    mu_run_test(test_list_reverse);

    return NULL;
}

RUN_TESTS(all_tests)
