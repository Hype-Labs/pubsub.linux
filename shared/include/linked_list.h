
#ifndef SHARED_LINKED_LIST_H_INCLUDED_
#define SHARED_LINKED_LIST_H_INCLUDED_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//typedef bool (*LinkedListOnCompareDataCallback) (void*, void*);
//typedef void (*LinkedListOnRemoveDataCallback) (void*);

typedef struct LinkedListElement_
{
  void* data;
  struct LinkedListElement_* next;
} LinkedListElement;

LinkedListElement* linked_list_create();

int linked_list_add(LinkedListElement* head, void *elem_data);

int linked_list_remove(LinkedListElement **head, void* elem_data, bool (*compare_elements_data) (void*, void*), void (*free_element_data) (void*));

bool linked_list_is_empty(LinkedListElement* head);

void linked_list_iterator(LinkedListElement **it);

LinkedListElement* linked_list_find(LinkedListElement *head, void* elem_data, bool (*compare_elements_data) (void*, void*));

void linked_list_destroy(LinkedListElement *head, void (*free_element_data) (void*));

#endif /* SHARED_LINKED_LIST_H_INCLUDED_ */
