
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
    return linked_list_remove(list_subscrpt, subscrpt, linked_list_callback_is_subscription_service_key, linked_list_callback_free_subscription);
}

void hpb_list_subscriptions_destroy(ListSubscriptions **list_subscrpt)
{
    linked_list_destroy(list_subscrpt, linked_list_callback_free_subscription);
}

Subscription *hpb_list_subscriptions_find(ListSubscriptions *list_subscrpt, byte service_key[])
{
    LinkedListNode *node = linked_list_find(list_subscrpt, service_key, linked_list_callback_is_subscription_service_key);

    if(node == NULL)
        return NULL;

    return (Subscription*) node->element;
}

static bool linked_list_callback_is_subscription_service_key(void *subscription, void *service_key)
{
    if (subscription == NULL || service_key == NULL)
        return false;

    return is_sha1_key_equal(((Subscription*) subscription)->service_key, (byte*) service_key);
}

static void linked_list_callback_free_subscription(void **subscription)
{
    hpb_subscription_destroy((Subscription**) subscription);
}
