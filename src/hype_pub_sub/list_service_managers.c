
#include "hype_pub_sub/list_service_managers.h"

ListServiceManagers *hype_pub_sub_list_service_managers_create()
{
    return linked_list_create();
}

ServiceManager* hype_pub_sub_list_service_managers_add(ListServiceManagers *list_serv_man, byte service_key[SHA1_BLOCK_SIZE])
{
    if(list_serv_man == NULL)
        return NULL;

    ServiceManager *serv_man;
    // Avoid to insert repeated ServiceManagers
    serv_man = hype_pub_sub_list_service_managers_find(list_serv_man, service_key);
    if(serv_man != NULL)
        return serv_man;

    serv_man = hype_pub_sub_service_manager_create(service_key);
    linked_list_add(list_serv_man, serv_man);
    return serv_man;
}

int hype_pub_sub_list_service_managers_remove(ListServiceManagers *list_serv_man, byte service_key[])
{
    return linked_list_remove(list_serv_man, service_key, hype_pub_sub_list_service_managers_compare_data_callback, hype_pub_sub_list_service_managers_free_data_callback);
}

void hype_pub_sub_list_service_managers_destroy(ListServiceManagers *list_serv_man)
{
    linked_list_destroy(list_serv_man, hype_pub_sub_list_service_managers_free_data_callback);
}

ServiceManager* hype_pub_sub_list_service_managers_find(ListServiceManagers* list_serv_man, byte service_key[])
{
    LinkedListElement *elem = linked_list_find(list_serv_man, service_key, hype_pub_sub_list_service_managers_compare_data_callback);

    if(elem == NULL)
        return NULL;

    return (ServiceManager*) elem->data;
}

bool hype_pub_sub_list_service_managers_compare_data_callback(void *serv_man1, void *serv_man2)
{
    if (serv_man1 == NULL || serv_man2 == NULL)
        return false;

    if(memcmp(((ServiceManager*) serv_man1)->service_key, (byte*) serv_man2, SHA1_BLOCK_SIZE * sizeof(byte)) == 0)
        return true;

    return false;
}

void hype_pub_sub_list_service_managers_free_data_callback(void *serv_man)
{
    hype_pub_sub_service_manager_destroy((ServiceManager*) serv_man);
}
