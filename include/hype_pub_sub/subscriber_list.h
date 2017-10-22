
#ifndef HYPE_PUB_SUB_SUBSCRIBER_LIST_H_INCLUDED_
#define HYPE_PUB_SUB_SUBSCRIBER_LIST_H_INCLUDED_

#include "list.h"
#include "constants.h"

LinkedListElement* hype_pub_sub_subscriber_list_create();

int hype_pub_sub_subscriber_list_add(LinkedListElement *head, byte subscriber_id[]);

int hype_pub_sub_subscriber_list_remove(LinkedListElement **head, byte subscriber_id[]);

void hype_pub_sub_subscriber_list_destroy(LinkedListElement* head);

void copy_subscriber_id(void **dst, void* src);

bool is_id_equal(void* dst, void* src);

void free_subscriber(void* id);

#endif /* HYPE_PUB_SUB_SUBSCRIBER_LIST_H_INCLUDED_ */
