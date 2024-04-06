#include <stdlib.h>
#include "minunit.h"

char *some_test() {
    mu_assert(1 == 1, "Math is broken!");
    mu_assert(2 == 2, "Math is broken!");

    return NULL;
}

char *some_other_test() {
    mu_assert(3 == 3, "Math is broken!");
    mu_assert(4 == 4, "Math is broken!");

    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(some_test);
    mu_run_test(some_other_test);

    return NULL;
}

RUN_TESTS(all_tests)
