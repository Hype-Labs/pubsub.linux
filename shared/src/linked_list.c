
#include "linked_list.h"

LinkedList *linked_list_create()
{
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));

    if(list == NULL)
        return NULL;

    list->head = NULL;
    list->size = 0;
    return list;
}

LinkedListNode *linked_list_create_node(void *element)
{
    LinkedListNode *node = (LinkedListNode *) malloc(sizeof(LinkedListNode));

    if(node == NULL)
        return NULL;

    node->element = element;
    node->next = NULL;
    return node;
}

LinkedListIterator *linked_list_create_iterator(LinkedList *list)
{
    if(list == NULL)
        return NULL;

    LinkedListIterator *it = (LinkedListIterator *) malloc(sizeof(LinkedListIterator));

    if(it == NULL)
        return NULL;

    it->list = list;
    it->it_node = list->head;
    return it;
}

int linked_list_add(LinkedList *list, void *element)
{
    if(list == NULL)
        return -1;

    if(linked_list_is_empty(list)) // List is empty. Add element in the first node.
    {
        list->head = linked_list_create_node(element);
    }
    else
    {
        LinkedListNode *current_node = list->head;
        while(current_node->next != NULL) // Get to the tail of the list.
            current_node = current_node->next;

        current_node->next = linked_list_create_node(element);
    }

    (list->size)++;
    return 0;
}

int linked_list_remove(LinkedList *list, void *element, LinkedListCompareElementsCallback cmp_elements, LinkedListFreeElementCallback free_element)
{
    if(linked_list_is_empty(list))
        return -1;

    // Check if the element is in the head position
    if(cmp_elements(list->head->element, element) == true)
    {
        LinkedListNode *next_head = list->head->next;
        linked_list_destroy_node(&(list->head), free_element);
        list->head = next_head; // redefine head if necessary
        (list->size)--;
        return 1;
    }

    LinkedListNode *previous_node = list->head;
    LinkedListNode *current_node = list->head->next;
    while(current_node != NULL)
    {
        if(cmp_elements(current_node->element, element) == true)
        {
            previous_node->next = current_node->next;
            linked_list_destroy_node(&current_node, free_element);
            (list->size)--;
            return 0;
        }
        previous_node = current_node;
        current_node = current_node->next;
    }

    return -2; // ID not found
}

bool linked_list_is_empty(LinkedList *list)
{
    if(list == NULL || list->size == 0)
        return true;

    return false;
}

LinkedListNode *linked_list_find(LinkedList *list, void *element, LinkedListCompareElementsCallback cmp_elements) // its responsibility of the list to prevent duplicates if needed
{
    if(list == NULL)
        return NULL;

    LinkedListNode *current_node = list->head;
    while(current_node != NULL)
    {
        LinkedListNode *next_node = current_node->next;
        if(cmp_elements(current_node->element, element) == true)
            return current_node;
        current_node = next_node;
    }

    return NULL;
}

void linked_list_iterator_reset(LinkedListIterator *it)
{
    it->it_node = it->list->head;
}

void *linked_list_iterator_get_element(LinkedListIterator *it)
{
    if(it == NULL || it->it_node == NULL)
        return NULL;

    return it->it_node->element;
}

int linked_list_iterator_advance(LinkedListIterator *it)
{
    if(it == NULL || it->it_node == NULL || it->it_node->next == NULL || it->list->size == 0)
        return -1;

    it->it_node = it->it_node->next;
    return 0;
}

void linked_list_iterator_destroy(LinkedListIterator **it)
{
    free(*it);
    (*it) = NULL;
}

void linked_list_destroy_node(LinkedListNode **node, LinkedListFreeElementCallback free_element)
{
    free_element(&((*node)->element));
    free(*node);
    (*node) = NULL;
}

void linked_list_destroy(LinkedList **list, LinkedListFreeElementCallback free_element)
{
    if((*list) == NULL)
        return;

    LinkedListNode *current_node = (*list)->head;
    while(current_node != NULL)
    {
        LinkedListNode *next_node = current_node->next;
        linked_list_destroy_node(&current_node, free_element);
        current_node = next_node;
    }

    free((*list));
    (*list) = NULL;
}
