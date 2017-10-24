
#include "hype_pub_sub/list_subscriptions.h"

ListSubscriptions *hype_pub_sub_list_subscriptions_create()
{
    return linked_list_create();
}

int hype_pub_sub_list_subscriptions_add(ListSubscriptions *list_subscrpt, char* serv_name, size_t serv_name_len, byte man_id[HYPE_ID_BYTE_SIZE])
{
    Subscription *subscrpt = hype_pub_sub_subscription_create(serv_name, serv_name_len, man_id);

    if(hype_pub_sub_list_subscriptions_find(list_subscrpt, subscrpt->service_key) != NULL)
        return -1;

    return linked_list_add(list_subscrpt, subscrpt);
}

int hype_pub_sub_list_subscriptions_remove(ListSubscriptions *list_subscrpt, char* serv_name, size_t serv_name_len, byte man_id[HYPE_ID_BYTE_SIZE])
{
    Subscription *subscrpt = hype_pub_sub_subscription_create(serv_name, serv_name_len, man_id);
    return linked_list_remove(list_subscrpt, subscrpt, hype_pub_sub_list_subscriptions_compare, hype_pub_sub_list_subscriptions_free);
}

void hype_pub_sub_list_subscriptions_destroy(ListSubscriptions *list_subscrpt)
{
    linked_list_destroy(list_subscrpt, hype_pub_sub_list_subscriptions_free);
}

Subscription* hype_pub_sub_list_subscriptions_find(ListSubscriptions* list_subscrpt, byte service_key[])
{
    LinkedListElement *elem = linked_list_find(list_subscrpt, service_key, hype_pub_sub_list_subscriptions_compare);

    if(elem == NULL)
        return NULL;

    return (Subscription*) elem->data;
}

bool hype_pub_sub_list_subscriptions_compare(void *subscrpt1, void *subscrpt2)
{
    if (subscrpt1 == NULL || subscrpt2 == NULL)
        return false;

    if (memcmp(((Subscription*) subscrpt1)->service_key, ((Subscription*) subscrpt2)->service_key, HYPE_ID_BYTE_SIZE * sizeof(byte)) == 0)
        return true;

    return false;
}

void hype_pub_sub_list_subscriptions_free(void *subscrpt)
{
    hype_pub_sub_subscription_destroy(((Subscription*) subscrpt));
}
