
#ifndef HPB_LIST_CLIENTS_H_INCLUDED_
#define HPB_LIST_CLIENTS_H_INCLUDED_

#include "linked_list.h"
#include "client.h"
#include "constants.h"

typedef LinkedListNode ListClientNode;
typedef LinkedList ListClients;

/**
 * @brief hype_pub_sub_list_clients_create Allocates space for a linked list of Client elements.
 * @return Returns a pointer to the created linked list or NULL if the space could not be allocated.
 */
ListClients *hpb_list_clients_create();

HpbClient *hpb_list_clients_add(ListClients *list_cl, HLByte client_id[]);

int hpb_list_clients_remove(ListClients *list_cl, HLByte client_id[]);

/**
 * @brief hype_pub_sub_list_clients_destroy Deallocates the space previously allocated for a linked list of Client elements
 * @param list_cl Pointer to the Client linked list to be deallocated.
 */
void hpb_list_clients_destroy(ListClients **list_cl);

HpbClient *hpb_list_clients_find(ListClients *list_cl, HLByte client_id[]);

static bool linked_list_callback_is_client_id(void *client, void *id);

static void linked_list_callback_free_client(void **client);

#endif /* HPB_LIST_CLIENTS_H_INCLUDED_ */
