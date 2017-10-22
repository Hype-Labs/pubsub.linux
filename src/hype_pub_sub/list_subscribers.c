
#include "hype_pub_sub/list_subscribers.h"

ListSubscribers *hype_pub_sub_list_subscribers_create()
{
    return linked_list_create();
}

int hype_pub_sub_list_subscribers_add(ListSubscribers *list_subs, byte subscriber_id[])
{
    return linked_list_add(list_subs, subscriber_id, copy_subscriber, compare_subscribers);
}

int hype_pub_sub_list_subscribers_remove(ListSubscribers **list_subs, byte subscriber_id[])
{
    return linked_list_remove(list_subs, subscriber_id, compare_subscribers, free_subscriber);
}

void hype_pub_sub_list_subscribers_destroy(ListSubscribers* list_subs)
{
    linked_list_destroy(list_subs, free_subscriber);
}

void copy_subscriber(void **dst_subs, void *src_subs)
{
    *dst_subs = (byte*) malloc(HYPE_ID_BYTE_SIZE * sizeof(byte));
    memcpy(*dst_subs, (byte *) src_subs, HYPE_ID_BYTE_SIZE * sizeof(byte));
}

bool compare_subscribers(void *subs1, void *subs2)
{
    if (subs1 == NULL || subs2 == NULL)
        return false;

    if (memcmp((byte*) subs1, (byte*) subs2, HYPE_ID_BYTE_SIZE * sizeof(byte)) == 0)
        return true;

    return false;
}

void free_subscriber(void* subs)
{
    free((byte*) subs);
}
