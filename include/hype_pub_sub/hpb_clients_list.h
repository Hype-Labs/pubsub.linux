
#ifndef HPB_LIST_CLIENTS_H_INCLUDED_
#define HPB_LIST_CLIENTS_H_INCLUDED_

#include "linked_list.h"
#include "hpb_client.h"
#include "hpb_constants.h"

typedef LinkedListNode HpbClientsListNode;
typedef LinkedList HpbClientsList;

/**
 * @brief Allocates space for a linked list of HpbClient elements.
 * @return Returns a pointer to the created linked list or NULL if the space could not be allocated.
 */
HpbClientsList *hpb_list_clients_create();

/**
 * @brief Adds an HpbClient to a HpbClientsList.
 * @param list_cl List in which the HpbClient should be added.
 * @param instance Hype instance of the HpbClient to be added.
 * @return Returns a pointer to the added HpbClient.
 */
HpbClient *hpb_list_clients_add(HpbClientsList *list_cl, HypeInstance *instance);

/**
 * @brief Removes an HpbClient from a HpbClientsList.
 * @param list_cl List from which the HpbClient should be removed.
 * @param instance Hype instance of the HpbClient to be removed.
 * @return Returns >=0 if the HpbClient was removed and <0 otherwise.
 */
int hpb_list_clients_remove(HpbClientsList *list_cl, HypeInstance *instance);

/**
 * @brief Deallocates the space previously allocated for a linked list of HpbClient elements
 * @param list_cl Pointer to the pointer of the HpbClient linked list to be deallocated.
 */
void hpb_list_clients_destroy(HpbClientsList **list_cl);

/**
 * @brief Finds a given client in a linked list.
 * @param list_cl List in which the HpbClient should be searched.
 * @param instance Hype instance of the HpbClient to be searched.
 * @return Returns a pointer to the HpbClient if the search is successful or NULL otherwise.
 */
HpbClient *hpb_list_clients_find(HpbClientsList *list_cl, HypeInstance *instance);


#endif /* HPB_LIST_CLIENTS_H_INCLUDED_ */
