
#include "hype_pub_sub/subscriber_list.h"

LinkedListElement *hype_pub_sub_subscriber_list_create()
{
    return list_create();
}

int hype_pub_sub_subscriber_list_add(LinkedListElement *head, byte subscriber_id[])
{
    list_add(head, subscriber_id, copy_subscriber_id, is_id_equal);
    return 0;
}

int hype_pub_sub_subscriber_list_remove(LinkedListElement **head, byte subscriber_id[])
{
    list_remove(head, subscriber_id, is_id_equal, free_subscriber);
    return 0;
}

void hype_pub_sub_subscriber_list_destroy(LinkedListElement* head)
{
    list_destroy(head, free_subscriber);
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
