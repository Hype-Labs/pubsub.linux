
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

LinkedListElement* linked_list_create_element(void *elem_data);

LinkedList* linked_list_create();

int linked_list_add(LinkedList* list, void *elem_data);

int linked_list_remove(LinkedList *list, void* elem_data, bool (*compare_elements_data) (void*, void*), void (*free_element_data) (void*));

bool linked_list_is_empty(LinkedList* list);

void linked_list_iterator(LinkedListElement **it);

LinkedListElement* linked_list_find(LinkedList* list, void *elem_data, bool (*compare_elements_data) (void*, void*));

void linked_list_destroy_element(LinkedListElement *element, void (*free_element_data) (void*));

void linked_list_destroy(LinkedList *list, void (*free_element_data) (void*));

#endif /* SHARED_LINKED_LIST_H_INCLUDED_ */
