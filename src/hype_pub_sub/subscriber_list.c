
#include "hype_pub_sub/subscriber_list.h"

Subscriber* hype_pub_sub_subscriber_list_create()
{
    Subscriber* subs = (Subscriber*) malloc(sizeof(Subscriber));
    subs->subscriber_id = NULL;
    subs->next_subscriber = NULL;
    return subs;
}

int hype_pub_sub_subscriber_list_add(Subscriber *head, byte subs_id[HYPE_ID_BYTE_SIZE])
{
    if(head == NULL)
        return -1;

    if(hype_pub_sub_subscriber_list_is_subscribed(head, subs_id))
        return 1;

    if(head->subscriber_id == NULL) // List is empty. Add subscriber in the first position.
    {
        hype_pub_sub_subscriber_list_set_subscriber_id(head, subs_id);
    }
    else
    {
        Subscriber *current_subsc = head;
        while(current_subsc->next_subscriber != NULL) // Get to the tail of the list.
            current_subsc = current_subsc->next_subscriber;

        // Allocate space for the new subscriber and initialize it
        current_subsc->next_subscriber = (Subscriber*) malloc(sizeof(Subscriber));
        hype_pub_sub_subscriber_list_set_subscriber_id(current_subsc->next_subscriber, subs_id);
        current_subsc->next_subscriber->next_subscriber = NULL;
    }

    return 0;
}

int hype_pub_sub_subscriber_list_remove(Subscriber **head, byte subs_id[HYPE_ID_BYTE_SIZE])
{
    if(hype_pub_sub_subscriber_list_is_empty(*head))
        return -1;

    // Check if the element is in the head position and redefine head if necessary
    if(memcmp((*head)->subscriber_id, subs_id, HYPE_ID_BYTE_SIZE * sizeof(byte)) == 0)
    {
        free((*head)->subscriber_id);
        (*head)->subscriber_id = NULL;

        if( (*head)->next_subscriber != NULL )
            (*head) = (*head)->next_subscriber;

        return 1;
    }

    Subscriber *previous_subsc = (*head);
    Subscriber *current_subsc = (*head)->next_subscriber;
    while(current_subsc != NULL)
    {
        if(memcmp(current_subsc->subscriber_id, subs_id, HYPE_ID_BYTE_SIZE * sizeof(byte)) == 0)
        {
            previous_subsc->next_subscriber = current_subsc->next_subscriber;
            free(current_subsc->subscriber_id);
            free(current_subsc);
            return 0;
        }
        previous_subsc = current_subsc;
        current_subsc = current_subsc->next_subscriber;
    }

    return -2; // ID not found
}

bool hype_pub_sub_subscriber_list_is_subscribed(Subscriber *head, byte subs_id[HYPE_ID_BYTE_SIZE])
{
    if(hype_pub_sub_subscriber_list_is_empty(head))
        return false;

    Subscriber* current_subs = head;
    do
    {
        if(memcmp(current_subs->subscriber_id, subs_id, HYPE_ID_BYTE_SIZE * sizeof(byte)) == 0)
            return true;
        current_subs = current_subs->next_subscriber;
    }
    while(current_subs != NULL);

    return false;
}

bool hype_pub_sub_subscriber_list_is_empty(Subscriber *head)
{
    if(head == NULL)
        return true;

    if(head->subscriber_id == NULL)
        return true;

    return false;
}

void hype_pub_sub_subscriber_list_destroy(Subscriber *head)
{
    if(head == NULL)
        return;

    Subscriber* current_subs = head;
    do
    {
        Subscriber* next_subs = current_subs->next_subscriber;

        free(current_subs->subscriber_id);
        free(current_subs);

        current_subs = next_subs;
    }
    while(current_subs != NULL);
}

static void hype_pub_sub_subscriber_list_set_subscriber_id(Subscriber *subs, byte subs_id[HYPE_ID_BYTE_SIZE])
{
    subs->subscriber_id = (byte*) malloc(HYPE_ID_BYTE_SIZE * sizeof(byte));
    memcpy(subs->subscriber_id, subs_id, HYPE_ID_BYTE_SIZE * sizeof(byte));
}
