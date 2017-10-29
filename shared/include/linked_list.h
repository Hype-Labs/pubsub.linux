
#ifndef SHARED_LINKED_LIST_H_INCLUDED_
#define SHARED_LINKED_LIST_H_INCLUDED_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef bool (*LinkedListCompareElementsCallback) (void *, void *);
typedef void (*LinkedListFreeElementCallback) (void **);

typedef struct LinkedListNode_
{
    void *element;
    struct LinkedListNode_ *next;
} LinkedListNode;

typedef struct LinkedList_
{
    LinkedListNode *head;
    size_t size;
} LinkedList;

typedef struct LinkedListIterator_
{
    LinkedList *list;
    LinkedListNode *it_node;
} LinkedListIterator;

LinkedList *linked_list_create();

LinkedListNode *linked_list_create_node(void *element);

LinkedListIterator *linked_list_create_iterator(LinkedList *list);

int linked_list_add(LinkedList *list, void *element);

int linked_list_remove(LinkedList *list, void *element, LinkedListCompareElementsCallback cmp_elements, LinkedListFreeElementCallback free_element);

bool linked_list_is_empty(LinkedList *list);

LinkedListNode *linked_list_find(LinkedList *list, void *element, LinkedListCompareElementsCallback cmp_elements);

void linked_list_iterator_reset(LinkedListIterator *it);

void *linked_list_iterator_get_element(LinkedListIterator *it);

int linked_list_iterator_advance(LinkedListIterator *it);

void linked_list_iterator_destroy(LinkedListIterator **it);

void linked_list_destroy_node(LinkedListNode **node, LinkedListFreeElementCallback free_element);

void linked_list_destroy(LinkedList **list, LinkedListFreeElementCallback free_element);

#endif /* SHARED_LINKED_LIST_H_INCLUDED_ */
