//
// Created by franchioping on 6/25/24.
//

#include "test_linked_list.h"
#include <check.h>
#include <malloc.h>
#include "src/util/linkedlist/linkedlist.h"
#include <mcheck.h>

#define TEST_LIST_LENGTH 2

int* generate_data(const int length){
    int* ints = (int*) malloc(sizeof(int) * length);
    for(int i = 0; i < length; i++){
        ints[i] = i;
    }
    return ints;
}

START_TEST (test_lnkdList_GetNth)
{
    int* ints= generate_data(TEST_LIST_LENGTH);

    listnode* list = lnkdList_FromIntArray(TEST_LIST_LENGTH, ints);

    for(ssize_t i = 0; i < TEST_LIST_LENGTH; i++){
        ck_assert_uint_eq(*((int*)lnkdList_GetNth(list, i)->data),i);
    }

    free(ints);
    lnkdList_Free(list);
}
END_TEST


START_TEST (test_lnkdList_GetLength){
    int* ints= generate_data(TEST_LIST_LENGTH);

    listnode* list = lnkdList_FromIntArray(TEST_LIST_LENGTH, ints);

    ck_assert_uint_eq(lnkdList_GetLength(list), TEST_LIST_LENGTH);
    free(ints);
    lnkdList_Free(list);
}
END_TEST

START_TEST (test_lnkdList_Free) {


    int *ints = generate_data(TEST_LIST_LENGTH);

    listnode *list = lnkdList_FromIntArray(TEST_LIST_LENGTH, ints);

    free(ints);
    lnkdList_Free(list);
}
END_TEST


Suite *linked_list_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Test Linked List Suite");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_lnkdList_GetLength);
    tcase_add_test(tc_core, test_lnkdList_Free);
    tcase_add_test(tc_core, test_lnkdList_GetNth);

    suite_add_tcase(s, tc_core);

    return s;
}