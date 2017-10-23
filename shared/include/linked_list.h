
#ifndef SHARED_LINKED_LIST_H_INCLUDED_
#define SHARED_LINKED_LIST_H_INCLUDED_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct LinkedListElement_
{
  void* data;
  struct LinkedListElement_* next;
} LinkedListElement;

LinkedListElement* linked_list_create();

int linked_list_add(LinkedListElement* head, void *elem_data);

int linked_list_remove(LinkedListElement **head, void* elem_data, bool (*compare_elements_data)(void* data_elem1, void* data_elem2), void (*free_element_data)(void* data));

bool linked_list_is_empty(LinkedListElement* head);

LinkedListElement* linked_list_find(LinkedListElement *head, void* elem_data, bool (*compare_elements_data)(void* data_elem1, void* data_elem2));

void linked_list_destroy(LinkedListElement *head, void (*free_element_data)(void* data));

#endif /* SHARED_LINKED_LIST_H_INCLUDED_ */
