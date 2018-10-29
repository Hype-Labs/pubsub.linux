
#ifndef HYPE_PUB_SUB_LIST_SUBSCRIPTIONS_H_INCLUDED_
#define HYPE_PUB_SUB_LIST_SUBSCRIPTIONS_H_INCLUDED_

#include <string.h>

#include "linked_list.h"
#include "hpb_subscription.h"
#include "hpb_constants.h"


typedef LinkedListNode HpbSubscriptionsListNode;
typedef LinkedList HpbSubscriptionsList;

/**
 * @brief Allocates space for a linked list of HpbSubscription elements.
 * @return Returns a pointer to the created linked list or NULL if the space could not be allocated.
 */
HpbSubscriptionsList *hpb_list_subscriptions_create();

/**
 * @brief Adds an HpbSubscription to a HpbSubscriptionsList.
 * @param list_subscrpt List in which the HpbSubscription should be added.
 * @param serv_name Name of the service of the HpbSubscription to be added.
 * @param serv_name_len Length of the name of the service of the HpbSubscription to be added.
 * @param man_id ID of the manager HpbClient of the HpbSubscription to be added.
 * @return Returns a pointer to the added HpbSubscription.
 */
HpbSubscription *hpb_list_subscriptions_add(HpbSubscriptionsList *list_subscrpt, char *serv_name, size_t serv_name_len, HypeInstance * instance);

/**
 * @brief Removes an HpbSubscription from a HpbSubscriptionsList.
 * @param list_subscrpt List from which the HpbSubscription should be removed.
 * @param service_key Service key of the HpbSubscription to be removed.
 * @return Returns >=0 if the HpbSubscription was removed and <0 otherwise.
 */
int hpb_list_subscriptions_remove(HpbSubscriptionsList *list_subscrpt, HLByte service_key[]);

/**
 * @brief Deallocates the space previously allocated for a linked list of HpbSubscription elements
 * @param list_subscrpt Pointer to the pointer of the HpbSubscription linked list to be deallocated.
 */
void hpb_list_subscriptions_destroy(HpbSubscriptionsList **list_subscrpt);

/**
 * @brief Finds a given HpbSubscription in a linked list.
 * @param list_subscrpt List in which the HpbSubscription should be searched.
 * @param service_key Service key of the HpbSubscription to be searched.
 * @return Returns a pointer to the HpbSubscription if the search is successful or NULL otherwise.
 */
HpbSubscription *hpb_list_subscriptions_find(HpbSubscriptionsList *list_subscrpt, HLByte service_key[]);


#endif /* HYPE_PUB_SUB_LIST_SUBSCRIPTIONS_H_INCLUDED_ */
