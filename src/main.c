#include <stdlib.h>
#include <stdio.h>
#include <dbg.h>
#include <dsa/linked_list.h>

int main(int argc, char *argv[]) {

    printf("Hello, World!\n");

    List *list = List_create();
    check_debug(list, "What?");

    List_push(NULL, "");
    List_pop(NULL);
    List_unshift(NULL, "");
    List_shift(NULL);
    List_free(NULL);

    return EXIT_SUCCESS;

error:
    return EXIT_FAILURE;
}
