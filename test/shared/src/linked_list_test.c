
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

    ////////////////////////////////////////////////////
    // Add 10 integer elements
    ////////////////////////////////////////////////////

    LinkedList *list = linked_list_create();
    CU_ASSERT_TRUE(linked_list_is_empty(list));

    int int_to_add1 = 23;
    int int_to_add2 = 54;
    int int_to_add3 = 39;
    int int_to_add4 = 77;
    int int_to_add5 = 65;
    int int_to_add6 = 66;
    int int_to_add7 = 76;
    int int_to_add8 = 12;
    int int_to_add9 = 1;
    int int_to_add10 = 93;

    return_val = linked_list_add(list, create_int(int_to_add1));
    CU_ASSERT_FALSE(linked_list_is_empty(list));
    CU_ASSERT(list->size == 1);
    CU_ASSERT(return_val == 0);
    return_val = linked_list_add(list, create_int(int_to_add2));
    return_val = linked_list_add(list, create_int(int_to_add3));
    CU_ASSERT(list->size == 3);
    return_val = linked_list_add(list, create_int(int_to_add4));
    return_val = linked_list_add(list, create_int(int_to_add5));
    return_val = linked_list_add(list, create_int(int_to_add6));
    return_val = linked_list_add(list, create_int(int_to_add7));
    return_val = linked_list_add(list, create_int(int_to_add8));
    return_val = linked_list_add(list, create_int(int_to_add9));
    return_val = linked_list_add(list, create_int(int_to_add10));
    CU_ASSERT(list->size == 10);

    ////////////////////////////////////////////////////
    // Iterate over the 10 integer elements
    ////////////////////////////////////////////////////

    LinkedListIterator *it = linked_list_create_iterator(NULL);
    CU_ASSERT_PTR_NULL(it);

    it = linked_list_create_iterator(list);
    CU_ASSERT_PTR_NOT_NULL(it);

    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT_PTR_NOT_NULL(elem_data);
    CU_ASSERT( *((int *) elem_data) == int_to_add1);

    linked_list_advance_iterator(it);
    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT( *((int *) elem_data) == int_to_add2);

    linked_list_advance_iterator(it);
    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT( *((int *) elem_data) == int_to_add3);

    linked_list_advance_iterator(it);
    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT( *((int *) elem_data) == int_to_add4);

    linked_list_advance_iterator(it);
    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT( *((int *) elem_data) == int_to_add5);

    linked_list_advance_iterator(it);
    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT( *((int *) elem_data) == int_to_add6);

    linked_list_advance_iterator(it);
    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT( *((int *) elem_data) == int_to_add7);

    linked_list_advance_iterator(it);
    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT( *((int *) elem_data) == int_to_add8);

    linked_list_advance_iterator(it);
    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT( *((int *) elem_data) == int_to_add9);

    linked_list_advance_iterator(it);
    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT( *((int *) elem_data) == int_to_add10);

    // Test iterator when we get to the end of the list
    linked_list_advance_iterator(it);
    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT_PTR_NOT_NULL(elem_data);
    CU_ASSERT( *((int *) elem_data) == int_to_add10);

    ////////////////////////////////////////////////////
    // Remove 3 elements
    ////////////////////////////////////////////////////

    int int_to_remove1 = int_to_add5;
    int int_to_remove2 = int_to_add1;
    int int_to_remove3 = int_to_add1;
    int int_to_remove4 = int_to_add10;

    return_val = linked_list_remove(list, &int_to_remove1, compare_int_elem, free_int_elem);
    CU_ASSERT(list->size == 9);
    CU_ASSERT(return_val == 0);

    return_val = linked_list_remove(list, &int_to_remove2, compare_int_elem, free_int_elem);
    CU_ASSERT(list->size == 8);
    CU_ASSERT(return_val == 1); // Removing head

    return_val = linked_list_remove(list, &int_to_remove3, compare_int_elem, free_int_elem);
    CU_ASSERT(list->size == 8);
    CU_ASSERT(return_val == -2);

    return_val = linked_list_remove(list, &int_to_remove4, compare_int_elem, free_int_elem);
    CU_ASSERT(list->size == 7);
    CU_ASSERT(return_val == 0);

    ////////////////////////////////////////////////////
    // Iterate over the remaining 7 integer elements
    ////////////////////////////////////////////////////

    linked_list_reset_iterator(it); // reset to get back to the head of the list
    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT( *((int *) elem_data) == int_to_add2);

    linked_list_advance_iterator(it);
    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT( *((int *) elem_data) == int_to_add3);

    linked_list_advance_iterator(it);
    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT( *((int *) elem_data) == int_to_add4);

    linked_list_advance_iterator(it);
    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT( *((int *) elem_data) == int_to_add6);

    linked_list_advance_iterator(it);
    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT( *((int *) elem_data) == int_to_add7);

    linked_list_advance_iterator(it);
    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT( *((int *) elem_data) == int_to_add8);

    linked_list_advance_iterator(it);
    elem_data = linked_list_get_element_data_iterator(it);
    CU_ASSERT( *((int *) elem_data) == int_to_add9);

    linked_list_destroy_iterator(&it);
    CU_ASSERT_PTR_NULL(it);

    ////////////////////////////////////////////////////
    // Test list find
    ////////////////////////////////////////////////////

    int int_to_find1 = int_to_add1;
    int int_to_find2 = int_to_add2;
    int int_to_find3 = int_to_add5;
    int int_to_find4 = int_to_add8;

    elem = linked_list_find(list, &int_to_find1, compare_int_elem);
    CU_ASSERT_PTR_NULL(elem);

    elem = linked_list_find(list, &int_to_find2, compare_int_elem);
    CU_ASSERT_PTR_NOT_NULL(elem);
    CU_ASSERT( *((int *) elem->data) == int_to_add2);

    elem = linked_list_find(list, &int_to_find3, compare_int_elem);
    CU_ASSERT_PTR_NULL(elem);

    elem = linked_list_find(list, &int_to_find4, compare_int_elem);
    CU_ASSERT_PTR_NOT_NULL(elem);
    CU_ASSERT( *((int *) elem->data) == int_to_add8);

    ////////////////////////////////////////////////////
    // Remove all elements
    ////////////////////////////////////////////////////

    linked_list_remove(list, &int_to_add2, compare_int_elem, free_int_elem);
    linked_list_remove(list, &int_to_add3, compare_int_elem, free_int_elem);
    linked_list_remove(list, &int_to_add4, compare_int_elem, free_int_elem);
    linked_list_remove(list, &int_to_add6, compare_int_elem, free_int_elem);
    linked_list_remove(list, &int_to_add7, compare_int_elem, free_int_elem);
    linked_list_remove(list, &int_to_add8, compare_int_elem, free_int_elem);
    linked_list_remove(list, &int_to_add9, compare_int_elem, free_int_elem);
    CU_ASSERT(list->size == 0);

    return_val = linked_list_remove(list, &int_to_remove1, compare_int_elem, free_int_elem);
    CU_ASSERT(list->size == 0);
    CU_ASSERT(return_val == -1);

    ////////////////////////////////////////////////////
    // Add 5 elements, and destroy the list
    ////////////////////////////////////////////////////

    linked_list_add(list, create_int(int_to_add1));
    LinkedListElement * elem1 = linked_list_find(list, &int_to_add1, compare_int_elem);
    linked_list_add(list, create_int(int_to_add2));
    linked_list_add(list, create_int(int_to_add3));
    linked_list_add(list, create_int(int_to_add4));
    linked_list_add(list, create_int(int_to_add5));
    CU_ASSERT(list->size == 5);

    CU_ASSERT_PTR_NOT_NULL(elem1);
    linked_list_destroy(&list, free_int_elem);
    CU_ASSERT_PTR_NULL(elem1->data);
    CU_ASSERT_PTR_NULL(list);

    // test operations when the list is null
    CU_ASSERT(linked_list_add(list, create_int(int_to_add1)) == -1);
    CU_ASSERT(linked_list_remove(list, &int_to_remove1, compare_int_elem, free_int_elem) == -1);
    CU_ASSERT_TRUE(linked_list_is_empty(list));
    CU_ASSERT_PTR_NULL(linked_list_create_iterator(list));
    CU_ASSERT_PTR_NULL(linked_list_find(list, &int_to_find1, compare_int_elem));
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

void free_int_elem(void **val)
{
    int **ptr = (int **) val;
    destroy_int(ptr);
}

int * create_int(int val)
{
    int *int_ptr = (int *) malloc(sizeof(int));
    *int_ptr = val;
    return int_ptr;
}

void destroy_int(int **ptr)
{
    free(*ptr);
    (*ptr) = NULL;
}
