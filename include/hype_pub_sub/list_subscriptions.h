
#ifndef HYPE_PUB_SUB_LIST_SUBSCRIPTIONS_H_INCLUDED_
#define HYPE_PUB_SUB_LIST_SUBSCRIPTIONS_H_INCLUDED_

#include <string.h>

#include "linked_list.h"
#include "subscription.h"
#include "constants.h"


typedef LinkedListNode ListSubscriptionElement;
typedef LinkedList ListSubscriptions;


ListSubscriptions *hpb_list_subscriptions_create();

Subscription *hpb_list_subscriptions_add(ListSubscriptions *list_subscrpt, char *serv_name, size_t serv_name_len, byte man_id[HPB_ID_BYTE_SIZE]);

int hpb_list_subscriptions_remove(ListSubscriptions *list_subscrpt, char *serv_name, size_t serv_name_len, byte man_id[HPB_ID_BYTE_SIZE]);

void hpb_list_subscriptions_destroy(ListSubscriptions *list_subscrpt);

Subscription *hpb_list_subscriptions_find(ListSubscriptions *list_subscrpt, byte service_key[]);

bool hpb_list_subscriptions_compare_data_callback(void *subscrpt1, void *subscrpt2);

void hpb_list_subscriptions_free_data_callback(void **subscrpt);

#endif /* HYPE_PUB_SUB_LIST_SUBSCRIPTIONS_H_INCLUDED_ */
