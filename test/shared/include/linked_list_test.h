
#ifndef SHARED_LINKED_LIST_TEST_H_INCLUDED_
#define SHARED_LINKED_LIST_TEST_H_INCLUDED_

#include <CUnit/Basic.h>

#include "string.h"

#include "linked_list.h"

typedef struct TestingStruct_
{
    int id;
    char *str;
} TestingStruct;

void linked_list_test();
void linked_list_test_create_destroy();
void linked_list_test_int();
void linked_list_test_testing_struct();

// Methods to test an integer linked list
bool compare_int_elem(void *val1, void *val2);
void free_int_elem(void **val);
int * create_int(int val);
void destroy_int(int **ptr);

// Methods to test a TestingStruct linked list
bool compare_testing_struct_elem(void *val1, void *val2);
void free_testing_struct_elem(void **val);
TestingStruct * create_testing_struct(char *msg, size_t length, int id);
void destroy_testing_struct(TestingStruct **t_str);
void linked_list_add_testing_struct(LinkedList* list, void *elem_data);

#endif /* SHARED_LINKED_LIST_TEST_H_INCLUDED_ */
