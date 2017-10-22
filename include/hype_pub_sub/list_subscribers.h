
#ifndef HYPE_PUB_SUB_LIST_SUBSCRIBERS_H_INCLUDED_
#define HYPE_PUB_SUB_LIST_SUBSCRIBERS_H_INCLUDED_

#include "linked_list.h"
#include "constants.h"


typedef LinkedListElement ListSubscribers;


ListSubscribers* hype_pub_sub_list_subscribers_create();

int hype_pub_sub_list_subscribers_add(ListSubscribers* list_subs, byte subscriber_id[]);

int hype_pub_sub_list_subscribers_remove(ListSubscribers **list_subs, byte subscriber_id[]);

void hype_pub_sub_list_subscribers_destroy(ListSubscribers* list_subs);

void copy_subscriber(void **dst_subs, void* src_subs);

bool compare_subscribers(void* subs1, void* subs2);

void free_subscriber(void* subs);

#endif /* HYPE_PUB_SUB_LIST_SUBSCRIBERS_H_INCLUDED_ */
