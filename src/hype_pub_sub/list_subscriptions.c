
#include "hype_pub_sub/list_subscriptions.h"

ListSubscriptions *hpb_list_subscriptions_create()
{
    return linked_list_create();
}

Subscription *hpb_list_subscriptions_add(ListSubscriptions *list_subscrpt, char *serv_name, size_t serv_name_len, byte man_id[HPB_ID_BYTE_SIZE])
{
    if(list_subscrpt == NULL)
        return NULL;

    Subscription *subscrpt;

    // Get service key from service name
    byte subscrpt_service_key[SHA1_BLOCK_SIZE];
    sha1_digest((const BYTE *) serv_name, serv_name_len, subscrpt_service_key);

    // Avoid to insert repeated Subscriptions
    subscrpt = hpb_list_subscriptions_find(list_subscrpt, subscrpt_service_key);
    if(subscrpt != NULL)
        return subscrpt;

    subscrpt = hpb_subscription_create(serv_name, serv_name_len, man_id);

    linked_list_add(list_subscrpt, subscrpt);
    return subscrpt;
}

int hpb_list_subscriptions_remove(ListSubscriptions *list_subscrpt, char *serv_name, size_t serv_name_len, byte man_id[HPB_ID_BYTE_SIZE])
{
    Subscription *subscrpt = hpb_subscription_create(serv_name, serv_name_len, man_id);
    return linked_list_remove(list_subscrpt, subscrpt, hpb_list_subscriptions_compare_data_callback, hpb_list_subscriptions_free_data_callback);
}

void hpb_list_subscriptions_destroy(ListSubscriptions *list_subscrpt)
{
    linked_list_destroy(&list_subscrpt, hpb_list_subscriptions_free_data_callback);
}

Subscription *hpb_list_subscriptions_find(ListSubscriptions *list_subscrpt, byte service_key[])
{
    LinkedListNode *elem = linked_list_find(list_subscrpt, service_key, hpb_list_subscriptions_compare_data_callback);

    if(elem == NULL)
        return NULL;

    return (Subscription*) elem->element;
}

bool hpb_list_subscriptions_compare_data_callback(void *subscrpt1, void *subscrpt2)
{
    if (subscrpt1 == NULL || subscrpt2 == NULL)
        return false;

    if (memcmp(((Subscription*) subscrpt1)->service_key, (byte*) subscrpt2, SHA1_BLOCK_SIZE * sizeof(byte)) == 0)
        return true;

    return false;
}

void hpb_list_subscriptions_free_data_callback(void **subscrpt)
{
    Subscription **ptr = (Subscription**) subscrpt;
    hpb_subscription_destroy(ptr);
}
