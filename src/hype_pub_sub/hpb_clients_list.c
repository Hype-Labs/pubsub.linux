
#include "hype_pub_sub/hpb_clients_list.h"

HpbClientsList *hpb_list_clients_create()
{
    return linked_list_create();
}

HpbClient *hpb_list_clients_add(HpbClientsList *list_cl, HypeInstance * instance)
{
    if(list_cl == NULL)
        return NULL;

    HpbClient *cl;
    // Avoid to insert repeated Clients
    cl = hpb_list_clients_find(list_cl, instance);
    if(cl != NULL)
        return cl;

    cl = hpb_client_create(instance);
    linked_list_add(list_cl, cl);
    return cl;
}

int hpb_list_clients_remove(HpbClientsList *list_cl, HypeInstance * instance)
{
    return linked_list_remove(list_cl, instance, linked_list_callback_is_client_id, linked_list_callback_free_client);
}

void hpb_list_clients_destroy(HpbClientsList **list_cl)
{
    linked_list_destroy(list_cl, linked_list_callback_free_client);
}

HpbClient *hpb_list_clients_find(HpbClientsList *list_cl, HypeInstance * instance)
{
    HpbClientsListNode *node = linked_list_find(list_cl, instance, linked_list_callback_is_client_id);

    if(node == NULL)
        return NULL;

    return (HpbClient*) node->element;
}

static bool linked_list_callback_is_client_id(void *client, void *id)
{
    if (client == NULL || id == NULL)
        return false;

    return hpb_client_is_id_equal((((HpbClient *) client)->hype_instance), (HypeInstance *) id);
}

static void linked_list_callback_free_client(void **client)
{
    hpb_client_destroy((HpbClient **) client);
}
