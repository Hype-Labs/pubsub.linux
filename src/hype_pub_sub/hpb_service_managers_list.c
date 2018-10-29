
#include "hype_pub_sub/hpb_service_managers_list.h"

// Static functions declaration

static bool linked_list_callback_is_service_manager_key(void *service_manager, void *key);
static void linked_list_callback_free_service_manager(void **service_manager);

// Header functions implementation

HpbServiceManagersList *hpb_list_service_managers_create()
{
    return linked_list_create();
}

HpbServiceManager *hpb_list_service_managers_add(HpbServiceManagersList *list_serv_man, HLByte service_key[SHA1_BLOCK_SIZE])
{
    if(list_serv_man == NULL)
        return NULL;

    HpbServiceManager *serv_man;
    // Avoid to insert repeated ServiceManagers
    serv_man = hpb_list_service_managers_find(list_serv_man, service_key);
    if(serv_man != NULL)
        return serv_man;

    serv_man = hpb_service_manager_create(service_key);
    linked_list_add(list_serv_man, serv_man);
    return serv_man;
}

int hpb_list_service_managers_remove(HpbServiceManagersList *list_serv_man, HLByte service_key[])
{
    return linked_list_remove(list_serv_man, service_key, linked_list_callback_is_service_manager_key, linked_list_callback_free_service_manager);
}

void hpb_list_service_managers_destroy(HpbServiceManagersList **list_serv_man)
{
    linked_list_destroy(list_serv_man, linked_list_callback_free_service_manager);
}

HpbServiceManager *hpb_list_service_managers_find(HpbServiceManagersList *list_serv_man, HLByte service_key[])
{
    LinkedListNode *node = linked_list_find(list_serv_man, service_key, linked_list_callback_is_service_manager_key);

    if(node == NULL)
        return NULL;

    return (HpbServiceManager*) node->element;
}

// Static functions implementation

static bool linked_list_callback_is_service_manager_key(void *service_manager, void *key)
{
    if (service_manager == NULL || key == NULL)
        return false;

    return is_sha1_key_equal(((HpbServiceManager*) service_manager)->service_key, (HLByte*) key);
}

static void linked_list_callback_free_service_manager(void **service_manager)
{
    hpb_service_manager_destroy((HpbServiceManager**) service_manager);
}
