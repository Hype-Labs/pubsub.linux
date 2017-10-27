
#ifndef SHARED_LINKED_LIST_H_INCLUDED_
#define SHARED_LINKED_LIST_H_INCLUDED_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//typedef bool (*LinkedListOnCompareDataCallback) (void*, void*);
//typedef void (*LinkedListOnRemoveDataCallback) (void*);

typedef struct LinkedListElement_
{
    void *data;
    struct LinkedListElement_ *next;
} LinkedListElement;

typedef struct LinkedList_
{
    LinkedListElement *head;
    size_t size;
} LinkedList;

typedef struct LinkedListIterator_
{
    LinkedList *list;
    LinkedListElement *it_elem;
} LinkedListIterator;

LinkedList* linked_list_create();

LinkedListElement* linked_list_create_element(void *elem_data);

LinkedListIterator* linked_list_create_iterator(LinkedList *list);

int linked_list_add(LinkedList* list, void *elem_data);

int linked_list_remove(LinkedList *list, void* elem_data, bool (*compare_elements_data) (void*, void*), void (*free_element_data) (void**));

bool linked_list_is_empty(LinkedList* list);

LinkedListElement* linked_list_find(LinkedList* list, void *elem_data, bool (*compare_elements_data) (void*, void*));

void linked_list_reset_iterator(LinkedListIterator *it);

void* linked_list_get_element_data_iterator(LinkedListIterator *it);

int linked_list_advance_iterator(LinkedListIterator *it);

void linked_list_destroy_iterator(LinkedListIterator **it);

void linked_list_destroy_element(LinkedListElement **element, void (*free_element_data) (void**));

void linked_list_destroy(LinkedList **list, void (*free_element_data) (void**));

#endif /* SHARED_LINKED_LIST_H_INCLUDED_ */
