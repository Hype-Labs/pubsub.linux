
#ifndef SHARED_LINKED_LIST_H_INCLUDED_
#define SHARED_LINKED_LIST_H_INCLUDED_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef bool (*LinkedListCompareElementsCallback) (void *, void *);
typedef void (*LinkedListFreeElementCallback) (void **);

/**
 * @brief This struct represents a node of the linked list.
 */
typedef struct LinkedListNode_
{
    void *element; /**< Element kepted by the node. */
    struct LinkedListNode_ *next; /**< Pointer to the next node of the list. */
} LinkedListNode;

/**
 * @brief This struct represents a linked list.
 */
typedef struct LinkedList_
{
    LinkedListNode *head; /**< Pointer to the head node of the list. */
    size_t size; /**< Size of the list. */
} LinkedList;

/**
 * @brief This struct represents an iterator to the linked list.
 */
typedef struct LinkedListIterator_
{
    LinkedList *list; /**< Pointer to the list of the iterator. */
    LinkedListNode *it_node; /**< Pointer to the list node pointed by the iterator. */
} LinkedListIterator;

/**
 * @brief Allocates space for a linked list and set its size to 0 and the head to NULL.
 * @return Return a pointer to the created list.
 */
LinkedList *linked_list_create();

/**
 * @brief Creates a linked list node that can later be added to the linked list.
 * @param element Element to be kepted by the node.
 * @return Returns a pointer to the created node.
 */
LinkedListNode *linked_list_node_create(void *element);

/**
 * @brief Creates an iterator for a given linked list.
 * @param list Linked list to iterate.
 * @return Returns a pointer to the created iterator.
 */
LinkedListIterator *linked_list_iterator_create(LinkedList *list);

/**
 * @brief Adds a node to the linked list.
 * @param list Linked list to which the node will be added.
 * @param element Element to be kepted by the node that will be added.
 * @return Returns -1 if the specified list is NULL and 0 otherwise.
 */
int linked_list_add(LinkedList *list, void *element);

/**
 * @brief Removes a node from the linked list.
 * @param list Linked list from which the node will be removed.
 * @param element Element that will be used in the LinkedListCompareElementsCallback to identify the node to be removed.
 * @param cmp_elements Callback to identify the node to be removed.
 * @param free_element Callback to free the memory previously allocated for the node's element.
 * @return Returns -1 if the specified list is NULL or empty, -2 if the node was not found, 1 if the node is the head of the list and 0 otherwise.
 */
int linked_list_remove(LinkedList *list, void *element, LinkedListCompareElementsCallback cmp_elements, LinkedListFreeElementCallback free_element);

/**
 * @brief Checks if a given linked list is NULL or empty.
 * @param list Linked list to be analyzed.
 * @return Return true if the list is NULL or empty.
 */
bool linked_list_is_empty(LinkedList *list);

/**
 * @brief Method to find a linked list node which contains a given element.
 * @param list List to be searched.
 * @param element Element that the searched node must contain.
 * @param cmp_elements Callback to identify the node to be removed.
 * @return Return a pointer to the linked list node. If the node was not found it returns NULL.
 */
LinkedListNode *linked_list_find(LinkedList *list, void *element, LinkedListCompareElementsCallback cmp_elements);

/**
 * @brief Resets an iterator so that it points to the header of its linked list.
 * @param it Iterator to be reseted.
 */
void linked_list_iterator_reset(LinkedListIterator *it);

/**
 * @brief Gets the element from the node to which the iterator is pointing.
 * @param it Iterator from which to get the element.
 * @return Returns a pointer to the element.
 */
void *linked_list_iterator_get_element(LinkedListIterator *it);

/**
 * @brief Advances the iterator to the next node of the linked list.
 * @param it Iterator to be advanced.
 * @return Returns -1 if a next node do not exist, or if the list is NULL, and 0 otherwise.
 */
int linked_list_iterator_advance(LinkedListIterator *it);

/**
 * @brief Destroys an iterator by deallocating the space previously allocated for it.
 * @param it Iterator to be destroyed.
 */
void linked_list_iterator_destroy(LinkedListIterator **it);

/**
 * @brief Destroys a linked list node by deallocating the space previously allocated for it.
 * @param node Node to be destroyed.
 * @param free_element Callback to free the memory previously allocated for the node's element.
 */
void linked_list_node_destroy(LinkedListNode **node, LinkedListFreeElementCallback free_element);

/**
 * @brief Destroys a linked list by deallocating the space previously allocated for it.
 * @param list List to be destroyed.
 * @param free_element Callback to free the memory previously allocated for the elements of the list's nodes.
 */
void linked_list_destroy(LinkedList **list, LinkedListFreeElementCallback free_element);

#endif /* SHARED_LINKED_LIST_H_INCLUDED_ */
