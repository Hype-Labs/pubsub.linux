
#ifndef HYPE_PUB_SUB_SUBSCRIBER_LIST_H_INCLUDED_
#define HYPE_PUB_SUB_SUBSCRIBER_LIST_H_INCLUDED_

#include "linked_list.h"
#include "constants.h"


typedef LinkedListElement SubscriberList;


SubscriberList* hype_pub_sub_subscriber_list_create();

int hype_pub_sub_subscriber_list_add(SubscriberList* subsList, byte subscriber_id[]);

int hype_pub_sub_subscriber_list_remove(SubscriberList **subsList, byte subscriber_id[]);

void hype_pub_sub_subscriber_list_destroy(SubscriberList* subsList);

void copy_subscriber(void **dst, void* src);

bool compare_subscribers(void* dst, void* src);

void free_subscriber(void* id);

#endif /* HYPE_PUB_SUB_SUBSCRIBER_LIST_H_INCLUDED_ */
