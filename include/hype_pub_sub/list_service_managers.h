
#ifndef HPB_LIST_SERVICE_MANAGERS_H_INCLUDED_
#define HPB_LIST_SERVICE_MANAGERS_H_INCLUDED_

#include "linked_list.h"
#include "service_manager.h"
#include "constants.h"


typedef LinkedListNode ListServiceManagerElement;
typedef LinkedList ListServiceManagers;


ListServiceManagers *hpb_list_service_managers_create();

ServiceManager *hpb_list_service_managers_add(ListServiceManagers *list_serv_man, byte service_key[SHA1_BLOCK_SIZE]);

int hpb_list_service_managers_remove(ListServiceManagers *list_serv_man, byte service_key[SHA1_BLOCK_SIZE]);

void hpb_list_service_managers_destroy(ListServiceManagers *list_serv_man);

ServiceManager *hpb_list_service_managers_find(ListServiceManagers *list_cl, byte service_key[]);

bool hpb_list_service_managers_compare_data_callback(void *serv_man1, void *serv_man2);

void hpb_list_service_managers_free_data_callback(void **serv_man);

#endif /* HPB_LIST_SERVICE_MANAGERS_H_INCLUDED_ */
