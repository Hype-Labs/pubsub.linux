
#include "linked_list.h"

LinkedList* linked_list_create()
{
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}

LinkedListElement* linked_list_create_element(void *elem_data)
{
    LinkedListElement *element = (LinkedListElement *) malloc(sizeof(LinkedListElement));
    element->data = elem_data;
    element->next = NULL;
    return element;
}

LinkedListIterator* linked_list_create_iterator(LinkedList *list)
{
    LinkedListIterator *it = (LinkedListIterator *) malloc(sizeof(LinkedListIterator));
    it->list = list;
    it->it_elem = list->head;
    return it;
}

int linked_list_add(LinkedList* list, void *elem_data)
{
    if(list == NULL)
        return -1;

    if(linked_list_is_empty(list)) // List is empty. Add subscriber in the first position.
    {
        list->head = linked_list_create_element(elem_data);
    }
    else
    {
        LinkedListElement *current_elem = list->head;
        while(current_elem->next != NULL) // Get to the tail of the list.
            current_elem = current_elem->next;

        current_elem->next = linked_list_create_element(elem_data);
    }

    (list->size)++;
    return 0;
}

int linked_list_remove(LinkedList *list, void* elem_data, bool (*compare_elements_data) (void*, void*), void (*free_element_data) (void*))
{
    if(linked_list_is_empty(list))
        return -1;

    // Check if the element is in the head position and redefine head if necessary
    if(compare_elements_data(list->head->data, elem_data) == true)
    {
        LinkedListElement *next_head = list->head->next;
        free_element_data(list->head->data);
        free(list->head);
        list->head = next_head;
        (list->size)--;
        return 1;
    }

    LinkedListElement *previous_elem = list->head;
    LinkedListElement *current_elem = list->head->next;
    while(current_elem != NULL)
    {
        if(compare_elements_data(current_elem->data, elem_data) == true)
        {
            previous_elem->next = current_elem->next;
            linked_list_destroy_element(current_elem, free_element_data);
            (list->size)--;
            return 0;
        }
        previous_elem = current_elem;
        current_elem = current_elem->next;
    }

    return -2; // ID not found
}

bool linked_list_is_empty(LinkedList *list)
{
    if(list == NULL || list->size == 0)
        return true;

    return false;
}

void linked_list_iterator(LinkedListElement **it)
{
    (*it) = (*it)->next;
}

LinkedListElement* linked_list_find(LinkedList* list, void *elem_data, bool (*compare_elements_data) (void*, void*)) // its responsibility of the list to prevent duplicates if needed
{
    if(list == NULL)
        return NULL;

    LinkedListElement *current_elem = list->head;
    while(current_elem != NULL)
    {
        LinkedListElement* next_elem = current_elem->next;
        if(compare_elements_data(current_elem->data, elem_data) == true)
            return current_elem;
        current_elem = next_elem;
    }

    return NULL;
}

void linked_list_reset_iterator(LinkedListIterator *it)
{
    it->it_elem = it->list->head;
}

void* linked_list_get_element_data_iterator(LinkedListIterator *it)
{
    if(it == NULL || it->it_elem == NULL)
        return NULL;

    return it->it_elem->data;
}

void linked_list_advance_iterator(LinkedListIterator *it)
{
    it->it_elem = it->it_elem->next;
}

void linked_list_destroy_iterator(LinkedListIterator *it)
{
    free(it);
}

void linked_list_destroy_element(LinkedListElement *element, void (*free_element_data) (void*))
{
    free_element_data(element->data);
    free(element);
}

void linked_list_destroy(LinkedList *list, void (*free_element_data) (void*))
{
    if(list == NULL)
        return;

    LinkedListElement *current_elem = list->head;
    while(current_elem != NULL)
    {
        LinkedListElement *next_elem = current_elem->next;
        linked_list_destroy_element(current_elem, free_element_data);
        current_elem = next_elem;
    }

    free(list);
}
