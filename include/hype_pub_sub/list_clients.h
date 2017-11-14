
#ifndef HPB_LIST_CLIENTS_H_INCLUDED_
#define HPB_LIST_CLIENTS_H_INCLUDED_

#include "linked_list.h"
#include "client.h"
#include "constants.h"

typedef LinkedListNode HpbClientsListNode;
typedef LinkedList HpbClientsList;

/**
 * @brief Allocates space for a linked list of HpbClient elements.
 * @return Returns a pointer to the created linked list or NULL if the space could not be allocated.
 */
HpbClientsList *hpb_list_clients_create();

/**
 * @brief Adds an HpbClient to a HpbClientsList.
 * @param list_cl List in which the client should be added.
 * @param client_id ID of the client to be added.
 * @return Returns a pointer to the added client.
 */
HpbClient *hpb_list_clients_add(HpbClientsList *list_cl, HLByte client_id[]);

/**
 * @brief Removes an HpbClient from a HpbClientsList.
 * @param list_cl List from which the client should be removed.
 * @param client_id ID of the client to be removed.
 * @return Returns >=0 if the client was removed and <0 otherwise.
 */
int hpb_list_clients_remove(HpbClientsList *list_cl, HLByte client_id[]);

/**
 * @brief Deallocates the space previously allocated for a linked list of Client elements
 * @param list_cl Pointer to the pointer of the Client linked list to be deallocated.
 */
void hpb_list_clients_destroy(HpbClientsList **list_cl);

/**
 * @brief Finds a given client in a linked list.
 * @param list_cl List in which the client should be searched.
 * @param client_id ID of the client to be searched.
 * @return Returns a pointer to the client if the search is successful or NULL otherwise.
 */
HpbClient *hpb_list_clients_find(HpbClientsList *list_cl, HLByte client_id[]);

/**
 * @brief Callback to identify a client in the linked list.
 * @param client Client to
 * @param id ID
 * @return Returns true if the specified ID corresponds to the ID of the specified client.
 */
static bool linked_list_callback_is_client_id(void *client, void *id);

/**
 * @brief Callback to deallocate the space reserved for a client of the linked list.
 * @param client Pointer to the pointer of the client to be deallocated
 */
static void linked_list_callback_free_client(void **client);

#endif /* HPB_LIST_CLIENTS_H_INCLUDED_ */
