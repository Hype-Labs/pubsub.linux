
#include "hype_pub_sub/hpb_subscriptions_list.h"

HpbSubscriptionsList *hpb_list_subscriptions_create()
{
    return linked_list_create();
}

HpbSubscription *hpb_list_subscriptions_add(HpbSubscriptionsList *list_subscrpt, char *serv_name, size_t serv_name_len, HypeInstance * instance)
{
    if(list_subscrpt == NULL)
        return NULL;

    HpbSubscription *subscrpt;

    // Get service key from service name
    HLByte subscrpt_service_key[SHA1_BLOCK_SIZE];
    sha1_digest((const BYTE *) serv_name, serv_name_len, subscrpt_service_key);

    // Avoid to insert repeated Subscriptions
    subscrpt = hpb_list_subscriptions_find(list_subscrpt, subscrpt_service_key);
    if(subscrpt != NULL)
        return subscrpt;

    subscrpt = hpb_subscription_create(serv_name, serv_name_len, instance);

    linked_list_add(list_subscrpt, subscrpt);
    return subscrpt;
}

int hpb_list_subscriptions_remove(HpbSubscriptionsList *list_subscrpt,HLByte service_key[])
{
    return linked_list_remove(list_subscrpt, service_key, linked_list_callback_is_subscription_service_key, linked_list_callback_free_subscription);
}

void hpb_list_subscriptions_destroy(HpbSubscriptionsList **list_subscrpt)
{
    linked_list_destroy(list_subscrpt, linked_list_callback_free_subscription);
}

HpbSubscription *hpb_list_subscriptions_find(HpbSubscriptionsList *list_subscrpt, HLByte service_key[])
{
    LinkedListNode *node = linked_list_find(list_subscrpt, service_key, linked_list_callback_is_subscription_service_key);

    if(node == NULL)
        return NULL;

    return (HpbSubscription*) node->element;
}

static bool linked_list_callback_is_subscription_service_key(void *subscription, void *service_key)
{
    if (subscription == NULL || service_key == NULL)
        return false;

    return is_sha1_key_equal(((HpbSubscription*) subscription)->service_key, (HLByte*) service_key);
}

static void linked_list_callback_free_subscription(void **subscription)
{
    hpb_subscription_destroy((HpbSubscription**) subscription);
}
