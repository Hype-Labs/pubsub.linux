
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
        return -2;

    if(head->subscriber_id == NULL) // List is empty. Add subscriber in the first position.
    {
        head->subscriber_id = (byte*) malloc(HYPE_ID_BYTE_SIZE * sizeof(byte));
        memcpy(head->subscriber_id, subs_id, HYPE_ID_BYTE_SIZE * sizeof(byte));
    }
    else
    {
        Subscriber *current_subsc = head;
        while(current_subsc->next_subscriber != NULL) // Advance to the tail of the list.
            current_subsc = current_subsc->next_subscriber;

        // Allocate space for the new subscriber
        current_subsc->next_subscriber = (Subscriber*) malloc(sizeof(Subscriber));

        // Allocate space for the ID of the new subscriber and set the elements of the struct.
        current_subsc->next_subscriber->subscriber_id = (byte*) malloc(HYPE_ID_BYTE_SIZE * sizeof(byte));
        memcpy(current_subsc->next_subscriber->subscriber_id, subs_id, HYPE_ID_BYTE_SIZE * sizeof(byte));
        current_subsc->next_subscriber->next_subscriber = NULL;
    }

    return 0;
}

int hype_pub_sub_subscriber_list_remove(Subscriber **head, byte subs_id[HYPE_ID_BYTE_SIZE])
{
    if(hype_pub_sub_subscriber_list_is_empty(*head))
        return -1;

    if(memcmp((*head)->subscriber_id, subs_id, HYPE_ID_BYTE_SIZE * sizeof(byte)) == 0)
    {
        free((*head)->subscriber_id);
        (*head)->subscriber_id = NULL;

        if( (*head)->next_subscriber != NULL ) // redefine head if there is another element
            (*head) = (*head)->next_subscriber;

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
        if(memcmp(current_subs->subscriber_id, subs_id, HYPE_ID_BYTE_SIZE) == 0)
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
