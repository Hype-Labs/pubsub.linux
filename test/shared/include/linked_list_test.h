
#ifndef SHARED_LINKED_LIST_TEST_H_INCLUDED_
#define SHARED_LINKED_LIST_TEST_H_INCLUDED_

#include <CUnit/Basic.h>

#include "linked_list.h"

void linked_list_test();

void linked_list_test_create_destroy();
void linked_list_test_int();


// Callbacks for integer linked list
bool compare_int_elem(void *val1, void *val2);
void free_int_elem();

#endif /* SHARED_LINKED_LIST_TEST_H_INCLUDED_ */
