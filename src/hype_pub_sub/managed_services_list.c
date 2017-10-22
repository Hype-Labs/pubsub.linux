
#include "hype_pub_sub/managed_services_list.h"

ManagedServicesList *hype_pub_sub_managed_services_list_create()
{
    return linked_list_create();
}

int hype_pub_sub_managed_services_list_add(ManagedServicesList *mngdServList, ServiceManager *serv)
{
    linked_list_add(mngdServList, serv, copy_service, compare_services);
    return 0;
}

int hype_pub_sub_managed_services_list_remove(ManagedServicesList **mngdServList, ServiceManager *serv)
{

    linked_list_remove(mngdServList, serv, compare_services, free_service);
    return 0;
}

void hype_pub_sub_managed_services_list_destroy(ManagedServicesList *mngdServList)
{
    linked_list_destroy(mngdServList, free_service);
}

void copy_service(void **dst, void *src)
{

}

bool compare_services(void *dst, void *src)
{
    if(memcmp(((ServiceManager*) dst)->service_key,((ServiceManager*) src)->service_key, SHA1_BLOCK_SIZE) == 0)
        return true;
    return false;
}

void free_service(void *id)
{

}
