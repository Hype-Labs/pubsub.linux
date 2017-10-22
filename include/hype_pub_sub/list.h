
#ifndef LIST_H_INCLUDED_
#define LIST_H_INCLUDED_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct LinkedListElement_
{
  void* data;
  struct LinkedListElement_* next;
} LinkedListElement;

LinkedListElement* list_create();

int list_add(LinkedListElement* head, void *elem_data, void (*copy_data) (void** dst, void* src), bool(*compare_elements_data)(void* data1, void* data2));

int list_remove(LinkedListElement **head, void* elem_data, bool (*compare_elements_data)(void* data_elem1, void* data_elem2), void (*free_element_data)(void* data));

bool list_is_empty(LinkedListElement* head);

void list_destroy(LinkedListElement *head, void (*free_element_data)(void* data));

#endif /* LIST_H_INCLUDED_ */
