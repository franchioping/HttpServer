//
// Created by franchioping on 6/25/24.
//

#include "linked_list.h"
#include <check.h>
#include <malloc.h>
#include "src/util/linkedlist/linkedlist.h"
#include <mcheck.h>

#define TEST_LIST_LENGTH 9

int* generate_data(const int length){
    int* ints = (int*) malloc(sizeof(int) * length);
    for(int i = 0; i < length; i++){
        ints[i] = i;
    }
    return ints;
}

listnode* create_linked_list(const int list_length, const int* data){

    listnode *start = (listnode*) malloc(sizeof(listnode));
    listnode* node = start;
    for(int i = 0; i < list_length; i++){
        node->data = (void*) &data[i];
        node->next_node = (listnode*) malloc(sizeof(listnode));
        node = node->next_node;
    }
    return start;
}

START_TEST (test_linked_list_get_index)
{
    int* ints= generate_data(TEST_LIST_LENGTH);

    listnode* list = create_linked_list(TEST_LIST_LENGTH, ints);

    for(int i = 0; i < TEST_LIST_LENGTH -1; i++){
        listnode* node = list_get_at_index(list, i);
        ck_assert_int_eq(*((int*)(node->data)), i);
    }

    free(ints);
    list_free(list);
}
END_TEST

START_TEST (test_linked_list_length)
{
    int* ints= generate_data(TEST_LIST_LENGTH);

    listnode* list = create_linked_list(TEST_LIST_LENGTH, ints);

    ck_assert_uint_eq(list_get_length(list), TEST_LIST_LENGTH);
    free(ints);
    list_free(list);
}
END_TEST


Suite *linked_list_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Test Linked List Suite");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_linked_list_length);
    tcase_add_test(tc_core, test_linked_list_get_index);

    suite_add_tcase(s, tc_core);

    return s;
}