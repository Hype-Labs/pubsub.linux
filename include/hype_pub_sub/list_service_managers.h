
#ifndef HYPE_PUB_SUB_LIST_SERVICE_MANAGERS_H_INCLUDED_
#define HYPE_PUB_SUB_LIST_SERVICE_MANAGERS_H_INCLUDED_

#include "linked_list.h"
#include "service_manager.h"
#include "constants.h"


typedef LinkedListElement ListServiceManagers;


ListServiceManagers* hype_pub_sub_list_service_managers_create();

int hype_pub_sub_list_service_managers_add(ListServiceManagers* list_serv_man, byte service_key[SHA1_BLOCK_SIZE]);

int hype_pub_sub_list_service_managers_remove(ListServiceManagers **list_serv_man, byte service_key[SHA1_BLOCK_SIZE]);

void hype_pub_sub_list_service_managers_destroy(ListServiceManagers* list_serv_man);

bool hype_pub_sub_list_service_managers_is_inserted(ListServiceManagers* list_cl, byte service_key[]);

bool compare_service_manager(void* serv_man1, void *serv_man2);

void free_service_manager(void* serv_man);

#endif /* HYPE_PUB_SUB_LIST_SERVICE_MANAGERS_H_INCLUDED_ */
