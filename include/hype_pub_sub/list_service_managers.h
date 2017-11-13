
#ifndef HPB_LIST_SERVICE_MANAGERS_H_INCLUDED_
#define HPB_LIST_SERVICE_MANAGERS_H_INCLUDED_

#include "linked_list.h"
#include "service_manager.h"
#include "constants.h"


typedef LinkedListNode ListServiceManagerNode;
typedef LinkedList ListServiceManagers;


ListServiceManagers *hpb_list_service_managers_create();

HpbServiceManager *hpb_list_service_managers_add(ListServiceManagers *list_serv_man, HLByte service_key[SHA1_BLOCK_SIZE]);

int hpb_list_service_managers_remove(ListServiceManagers *list_serv_man, HLByte service_key[SHA1_BLOCK_SIZE]);

void hpb_list_service_managers_destroy(ListServiceManagers **list_serv_man);

HpbServiceManager *hpb_list_service_managers_find(ListServiceManagers *list_cl, HLByte service_key[]);

static bool linked_list_callback_is_service_manager_key(void *service_manager, void *key);

static void linked_list_callback_free_service_manager(void **service_manager);

#endif /* HPB_LIST_SERVICE_MANAGERS_H_INCLUDED_ */
