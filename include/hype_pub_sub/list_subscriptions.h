
#ifndef HYPE_PUB_SUB_LIST_SUBSCRIPTIONS_H_INCLUDED_
#define HYPE_PUB_SUB_LIST_SUBSCRIPTIONS_H_INCLUDED_

#include <string.h>

#include "linked_list.h"
#include "subscription.h"
#include "constants.h"


typedef LinkedListElement ListSubscriptions;


ListSubscriptions* hype_pub_sub_list_subscriptions_create();

int hype_pub_sub_list_subscriptions_add(ListSubscriptions* list_subscrpt, Subscription *subscrpt);

int hype_pub_sub_list_subscriptions_remove(ListSubscriptions **list_subscrpt, Subscription *subscrpt);

void hype_pub_sub_list_subscriptions_destroy(ListSubscriptions* list_subscrpt);

void copy_subscription(void **dst, void* src);

bool compare_subscriptions(void* subscrpt1, void* subscrpt2);

void free_subscription(void* subscrpt);

#endif /* HYPE_PUB_SUB_LIST_SUBSCRIPTIONS_H_INCLUDED_ */
