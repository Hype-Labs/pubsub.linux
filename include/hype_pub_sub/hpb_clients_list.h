
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
 * @param client_id ID of the HpbClient to be added.
 * @return Returns a pointer to the added HpbClient.
 */
HpbClient *hpb_list_clients_add(HpbClientsList *list_cl, HLByte client_id[]);

/**
 * @brief Removes an HpbClient from a HpbClientsList.
 * @param list_cl List from which the HpbClient should be removed.
 * @param client_id ID of the HpbClient to be removed.
 * @return Returns >=0 if the HpbClient was removed and <0 otherwise.
 */
int hpb_list_clients_remove(HpbClientsList *list_cl, HLByte client_id[]);

/**
 * @brief Deallocates the space previously allocated for a linked list of HpbClient elements
 * @param list_cl Pointer to the pointer of the HpbClient linked list to be deallocated.
 */
void hpb_list_clients_destroy(HpbClientsList **list_cl);

/**
 * @brief Finds a given client in a linked list.
 * @param list_cl List in which the HpbClient should be searched.
 * @param client_id ID of the HpbClient to be searched.
 * @return Returns a pointer to the HpbClient if the search is successful or NULL otherwise.
 */
HpbClient *hpb_list_clients_find(HpbClientsList *list_cl, HLByte client_id[]);

/**
 * @brief Callback to identify a HpbClient in the linked list.
 * @param client HpbClient to be analyzed.
 * @param id ID to which the HpbClient should be compared.
 * @return Returns true if the specified ID corresponds to the ID of the specified HpbClient.
 */
static bool linked_list_callback_is_client_id(void *client, void *id);

/**
 * @brief Callback to deallocate the space reserved for a HpbClient of the linked list.
 * @param client Pointer to the pointer of the HpbClient to be deallocated.
 */
static void linked_list_callback_free_client(void **client);

#endif /* HPB_LIST_CLIENTS_H_INCLUDED_ */
