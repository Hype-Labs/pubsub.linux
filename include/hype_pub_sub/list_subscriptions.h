
#ifndef HYPE_PUB_SUB_LIST_SUBSCRIPTIONS_H_INCLUDED_
#define HYPE_PUB_SUB_LIST_SUBSCRIPTIONS_H_INCLUDED_

#include <string.h>

#include "linked_list.h"
#include "subscription.h"
#include "constants.h"


typedef LinkedListNode HpbSubscriptionsListNode;
typedef LinkedList HpbSubscriptionsList;


HpbSubscriptionsList *hpb_list_subscriptions_create();

HpbSubscription *hpb_list_subscriptions_add(HpbSubscriptionsList *list_subscrpt, char *serv_name, size_t serv_name_len, HLByte man_id[HPB_ID_BYTE_SIZE]);

int hpb_list_subscriptions_remove(HpbSubscriptionsList *list_subscrpt, HLByte service_key[]);

void hpb_list_subscriptions_destroy(HpbSubscriptionsList **list_subscrpt);

HpbSubscription *hpb_list_subscriptions_find(HpbSubscriptionsList *list_subscrpt, HLByte service_key[]);

static bool linked_list_callback_is_subscription_service_key(void *subscription, void *service_key);

static void linked_list_callback_free_subscription(void **subscription);

#endif /* HYPE_PUB_SUB_LIST_SUBSCRIPTIONS_H_INCLUDED_ */
