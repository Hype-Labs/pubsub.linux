
#ifndef HYPE_PUB_SUB_MANAGED_SERVICES_LIST_H_INCLUDED_
#define HYPE_PUB_SUB_MANAGED_SERVICES_LIST_H_INCLUDED_

#include "linked_list.h"
#include "service_manager.h"
#include "constants.h"


typedef LinkedListElement ManagedServicesList;


ManagedServicesList* hype_pub_sub_managed_services_list_create();

int hype_pub_sub_managed_services_list_add(ManagedServicesList* mngdServList, ServiceManager* serv);

int hype_pub_sub_managed_services_list_remove(ManagedServicesList **mngdServList, ServiceManager* serv);

void hype_pub_sub_managed_services_list_destroy(ManagedServicesList* mngdServList);

void copy_service(void **dst, void* src);

bool compare_services(void* dst, void* src);

void free_service(void* id);

#endif /* HYPE_PUB_SUB_MANAGED_SERVICES_LIST_H_INCLUDED_ */
