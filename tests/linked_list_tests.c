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

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_list_create);

    return NULL;
}

RUN_TESTS(all_tests)
