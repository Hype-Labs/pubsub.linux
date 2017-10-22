
#include "hype_pub_sub/subscriber_list.h"

SubscriberList *hype_pub_sub_subscriber_list_create()
{
    return linked_list_create();
}

int hype_pub_sub_subscriber_list_add(SubscriberList *subsList, byte subscriber_id[])
{
    linked_list_add(subsList, subscriber_id, copy_subscriber_id, is_id_equal);
    return 0;
}

int hype_pub_sub_subscriber_list_remove(SubscriberList **subsList, byte subscriber_id[])
{
    linked_list_remove(subsList, subscriber_id, is_id_equal, free_subscriber);
    return 0;
}

void hype_pub_sub_subscriber_list_destroy(SubscriberList* subsList)
{
    linked_list_destroy(subsList, free_subscriber);
}

void copy_subscriber_id(void **dst, void *src)
{
    *dst = (byte*) malloc(HYPE_ID_BYTE_SIZE * sizeof(byte));
    memcpy(*dst, (byte *) src, HYPE_ID_BYTE_SIZE * sizeof(byte));

}

bool is_id_equal(void *dst, void *src)
{
    if (dst == NULL || src == NULL)
        return false;

    if (memcmp((byte*) dst, (byte*) src, HYPE_ID_BYTE_SIZE) == 0)
        return true;

    return false;
}

void free_subscriber(void* id)
{
    //free((byte*) id);
}
