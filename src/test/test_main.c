//
// Created by franchioping on 6/25/24.
//

#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <mcheck.h>
#include "test_linked_list.h"


int run_suite(Suite* suite){
    SRunner *runner = srunner_create(suite);

    srunner_run_all(runner, CK_NORMAL);
    int no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return no_failed;
}

void no_op(enum mcheck_status status) {}

int main(void) {
    mcheck(&no_op);
    int no_failed = 0;

    no_failed += run_suite(linked_list_suite());

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}