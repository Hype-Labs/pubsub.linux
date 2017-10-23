
#ifndef HYPE_PUB_SUB_LIST_CLIENTS_H_INCLUDED_
#define HYPE_PUB_SUB_LIST_CLIENTS_H_INCLUDED_

#include "linked_list.h"
#include "client.h"
#include "constants.h"


typedef LinkedListElement ListClients;


ListClients* hype_pub_sub_list_clients_create();

int hype_pub_sub_list_clients_add(ListClients* list_cl, byte client_id[]);

int hype_pub_sub_list_clients_remove(ListClients **list_cl, byte client_id[]);

void hype_pub_sub_list_clients_destroy(ListClients* list_cl);

bool hype_pub_sub_list_clients_is_inserted(ListClients* list_cl, byte client_id[]);

bool compare_clients(void* cl1, void* cl2);

void free_client(void* cl);

#endif /* HYPE_PUB_SUB_LIST_CLIENTS_H_INCLUDED_ */
