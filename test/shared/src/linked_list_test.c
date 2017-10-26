
#include "linked_list_test.h"


void linked_list_test()
{
    linked_list_test_create_destroy();
    linked_list_test_int();
}

void linked_list_test_create_destroy()
{
    LinkedList *list = linked_list_create();

    CU_ASSERT_PTR_NOT_NULL(list);
    CU_ASSERT_PTR_NULL(list->head);
    CU_ASSERT(list->size == 0);

    linked_list_destroy(&list, NULL);
    CU_ASSERT_PTR_NULL(list);
}

void linked_list_test_int()
{
    LinkedListElement *elem;
    int *elem_data;
    int return_val;

    ////////////////////////////////
    // Test list add
    ////////////////////////////////

    LinkedList *list = linked_list_create();
    CU_ASSERT_TRUE(linked_list_is_empty(list));

    int int_to_add1 = 23;
    int int_to_add2 = 54;
    int int_to_add3 = 39;

    int *elem1 = (int *) malloc(sizeof(int));
    (*elem1) = int_to_add1;
    return_val = linked_list_add(list, elem1);
    CU_ASSERT_FALSE(linked_list_is_empty(list));
    CU_ASSERT(list->size == 1);
    CU_ASSERT(return_val == 0);

    int *elem2 = (int *) malloc(sizeof(int));
    (*elem2) = int_to_add2;
    return_val = linked_list_add(list, elem2);
    CU_ASSERT(list->size == 2);
    CU_ASSERT(return_val == 0);

    int *elem3 = (int *) malloc(sizeof(int));
    (*elem3) = int_to_add3;
    return_val = linked_list_add(list, elem3);
    CU_ASSERT(list->size == 3);
    CU_ASSERT(return_val == 0);

    return_val = linked_list_add(NULL, elem3);
    CU_ASSERT(return_val == -1);

    ////////////////////////////////
    // Test list find
    ////////////////////////////////

    int int_to_find1 = 40;
    int int_to_find2 = int_to_add3;
    int int_to_find3 = 100;
    int int_to_find4 = int_to_add1;

    elem = linked_list_find(list, &int_to_find1, compare_int_elem);
    CU_ASSERT_PTR_NULL(elem);

    elem = linked_list_find(list, &int_to_find2, compare_int_elem);
    CU_ASSERT_PTR_NOT_NULL(elem);
    CU_ASSERT( *((int *) elem->data) == int_to_add3);

    elem = linked_list_find(list, &int_to_find3, compare_int_elem);
    CU_ASSERT_PTR_NULL(elem);

    elem = linked_list_find(list, &int_to_find4, compare_int_elem);
    CU_ASSERT_PTR_NOT_NULL(elem);
    CU_ASSERT( *((int *) elem->data) == int_to_add1);

    ////////////////////////////////
    // Test list iterator
    ////////////////////////////////

    LinkedListIterator *it = linked_list_create_iterator(NULL);
    CU_ASSERT_PTR_NULL(it);

    it = linked_list_create_iterator(list);
    CU_ASSERT_PTR_NOT_NULL(it);

    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT_PTR_NOT_NULL(elem_data);
    CU_ASSERT( *((int *) elem_data) == int_to_add1);
    linked_list_advance_iterator(it);

    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT_PTR_NOT_NULL(elem_data);
    CU_ASSERT( *((int *) elem_data) == int_to_add2);
    linked_list_advance_iterator(it);

    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT_PTR_NOT_NULL(elem_data);
    CU_ASSERT( *((int *) elem_data) == int_to_add3);

    // Test iterator when we get to the end of the list
    linked_list_advance_iterator(it);
    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT_PTR_NOT_NULL(elem_data);
    CU_ASSERT( *((int *) elem_data) == int_to_add3);

    // Test iterator reset
    linked_list_reset_iterator(it);
    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT_PTR_NOT_NULL(elem_data);
    CU_ASSERT( *((int *) elem_data) == int_to_add1);

    linked_list_destroy_iterator(&it);
    CU_ASSERT_PTR_NULL(it);

    ////////////////////////////////
    // Test list remove
    ////////////////////////////////

    int int_to_remove1 = int_to_add2;
    int int_to_remove2 = int_to_add1;
    int int_to_remove3 = 100;
    int int_to_remove4 = int_to_add3;

    return_val = linked_list_remove(list, &int_to_remove1, compare_int_elem, free_int_elem);
    CU_ASSERT(list->size == 2);
    CU_ASSERT(return_val == 0);

    return_val = linked_list_remove(list, &int_to_remove2, compare_int_elem, free_int_elem);
    CU_ASSERT(list->size == 1);
    CU_ASSERT(return_val == 1); // Removing head

    return_val = linked_list_remove(list, &int_to_remove3, compare_int_elem, free_int_elem);
    CU_ASSERT(list->size == 1);
    CU_ASSERT(return_val == -2);

    return_val = linked_list_remove(list, &int_to_remove4, compare_int_elem, free_int_elem);
    CU_ASSERT(list->size == 0);
    CU_ASSERT(return_val == 1); // Removing head

    return_val = linked_list_remove(list, &int_to_remove1, compare_int_elem, free_int_elem);
    CU_ASSERT(list->size == 0);
    CU_ASSERT(return_val == -1);
}


// Callbacks for integer linked list
bool compare_int_elem(void *val1, void *val2)
{
    int *int_val1 = (int *) val1;
    int *int_val2 = (int *) val2;

    if(*int_val1 == *int_val2)
        return true;
    return false;
}

void free_int_elem(void *val)
{
    free((int *) val);
}
