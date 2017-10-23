
#include "hype_pub_sub/list_subscriptions.h"

ListSubscriptions *hype_pub_sub_list_subscriptions_create()
{
    return linked_list_create();
}

int hype_pub_sub_list_subscriptions_add(ListSubscriptions *list_subscrpt, Subscription *subscrpt)
{
    return linked_list_add(list_subscrpt, subscrpt, copy_subscription, compare_subscriptions);
}

int hype_pub_sub_list_subscriptions_remove(ListSubscriptions **list_subscrpt, Subscription *subscrpt)
{
    return linked_list_remove(list_subscrpt, subscrpt, compare_subscriptions, free_subscription);
}

void hype_pub_sub_list_subscriptions_destroy(ListSubscriptions *list_subscrpt)
{
    linked_list_destroy(list_subscrpt, free_subscription);
}

void copy_subscription(void **dst, void *src)
{
    Subscription ** dst_subscrpt = (Subscription**) (dst);
    Subscription * src_subscrpt = (Subscription*) src;
    *dst_subscrpt = hype_pub_sub_subscription_create(src_subscrpt->service_name, strlen(src_subscrpt->service_name), src_subscrpt->manager_id);
}

bool compare_subscriptions(void *subscrpt1, void *subscrpt2)
{
    if (subscrpt1 == NULL || subscrpt2 == NULL)
        return false;

    if (memcmp(((Subscription*) subscrpt1)->service_key, ((Subscription*) subscrpt2)->service_key, HYPE_ID_BYTE_SIZE * sizeof(byte)) == 0)
        return true;

    return false;
}

void free_subscription(void *subscrpt)
{
    hype_pub_sub_subscription_destroy(((Subscription*) subscrpt));
}
