
#include "linked_list.h"

LinkedListElement* linked_list_create()
{
    LinkedListElement* list = (LinkedListElement*) malloc(sizeof(LinkedListElement));
    list->data = NULL;
    list->next = NULL;
    return list;
}

int linked_list_add(LinkedListElement* head, void *elem_data)
{
    if(head == NULL)
        return -1;

    if(head->data == NULL) // List is empty. Add subscriber in the first position.
    {
        head->data = elem_data;
    }
    else
    {
        LinkedListElement *current_elem = head;

        while(current_elem->next != NULL) // Get to the tail of the list.
            current_elem = current_elem->next;

        // Allocate space for the new element and initialize it
        current_elem->next = (LinkedListElement*) malloc(sizeof(LinkedListElement));
        current_elem->next->next = NULL;
        current_elem->next->data = elem_data;
    }

    return 0;
}

int linked_list_remove(LinkedListElement **head, void* elem_data, bool (*compare_elements_data)(void* data1, void* data2), void (*free_element_data)(void* data))
{
    if(linked_list_is_empty(*head))
        return -1;

    // Check if the element is in the head position and redefine head if necessary
    if(compare_elements_data((*head)->data, elem_data) == true)
    {
        free_element_data((*head)->data);
        (*head)->data = NULL;

        if( (*head)->next != NULL )
            (*head) = (*head)->next;

        return 1;
    }

    LinkedListElement *previous_elem = (*head);
    LinkedListElement *current_elem = (*head)->next;
    while(current_elem != NULL)
    {
        if(compare_elements_data(current_elem->data, elem_data) == true)
        {
            previous_elem->next = current_elem->next;
            free_element_data(&current_elem->data);
            current_elem->data = NULL;
            return 0;
        }
        previous_elem = current_elem;
        current_elem = current_elem->next;
    }

    return -2; // ID not found
}

bool linked_list_is_empty(LinkedListElement *head)
{
    if(head == NULL)
        return true;

    if(head->data == NULL)
        return true;

    return false;
}

void linked_list_destroy(LinkedListElement *head, void (*free_element_data)(void* data))
{
    if(head == NULL)
        return;

    LinkedListElement* current_elem = head;
    do
    {
        LinkedListElement* next_elem = current_elem->next;

        free_element_data(current_elem->data);
        free(current_elem);

        current_elem = next_elem;
    }
    while(current_elem != NULL);
}

bool linked_list_is_element_inserted(LinkedListElement *head, void *elem_data, bool (*compare_elements_data)(void *, void *)) // its responsibility of the list to prevent duplicates if needed
{
    if(head == NULL)
        return false;

    LinkedListElement* current_elem = head;
    do
    {
        LinkedListElement* next_elem = current_elem->next;

        if(compare_elements_data(head->data, elem_data) == true)
            return true;

        current_elem = next_elem;
    }
    while(current_elem != NULL);

    return false;
}
