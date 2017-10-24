
#ifndef HYPE_PUB_SUB_LIST_SERVICE_MANAGERS_H_INCLUDED_
#define HYPE_PUB_SUB_LIST_SERVICE_MANAGERS_H_INCLUDED_

#include "linked_list.h"
#include "service_manager.h"
#include "constants.h"


typedef LinkedListElement ListServiceManagerElement;
typedef LinkedList ListServiceManagers;


ListServiceManagers* hype_pub_sub_list_service_managers_create();

ServiceManager* hype_pub_sub_list_service_managers_add(ListServiceManagers* list_serv_man, byte service_key[SHA1_BLOCK_SIZE]);

int hype_pub_sub_list_service_managers_remove(ListServiceManagers *list_serv_man, byte service_key[SHA1_BLOCK_SIZE]);

void hype_pub_sub_list_service_managers_destroy(ListServiceManagers* list_serv_man);

ServiceManager* hype_pub_sub_list_service_managers_find(ListServiceManagers* list_cl, byte service_key[]);

bool hype_pub_sub_list_service_managers_compare_data_callback(void* serv_man1, void *serv_man2);

void hype_pub_sub_list_service_managers_free_data_callback(void* serv_man);

#endif /* HYPE_PUB_SUB_LIST_SERVICE_MANAGERS_H_INCLUDED_ */
