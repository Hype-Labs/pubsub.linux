
#include "hype_pub_sub/hpb_clients_list.h"

//
// Static functions declaration
//

static bool linked_list_callback_is_client_instance(void *client, void *id);
static void linked_list_callback_free_client(void **client);

//
// Header functions implementation
//

HpbClientsList *hpb_list_clients_create()
{
    return linked_list_create();
}

HpbClient *hpb_list_clients_add(HpbClientsList *list_cl, HypeInstance * instance)
{
    if(list_cl == NULL) {
        return NULL;
    }

    HpbClient *cl;
    // Avoid to insert repeated Clients
    cl = hpb_list_clients_find(list_cl, instance);
    if(cl != NULL) {
        return cl;
    }

    cl = hpb_client_create(instance);
    linked_list_add(list_cl, cl);
    return cl;
}

int hpb_list_clients_remove(HpbClientsList *list_cl, HypeInstance * instance)
{
    return linked_list_remove(list_cl, instance, linked_list_callback_is_client_instance, linked_list_callback_free_client);
}

void hpb_list_clients_destroy(HpbClientsList **list_cl)
{
    linked_list_destroy(list_cl, linked_list_callback_free_client);
}

HpbClient *hpb_list_clients_find(HpbClientsList *list_cl, HypeInstance * instance)
{
    HpbClientsListNode *node = linked_list_find(list_cl, instance, linked_list_callback_is_client_instance);

    if(node == NULL) {
        return NULL;
    }

    return (HpbClient*) node->element;
}

//
// Static functions implementation
//

static bool linked_list_callback_is_client_instance(void *client, void *id)
{
    if(client == NULL || id == NULL) {
        return false;
    }

    return hpb_client_is_instance_equal((((HpbClient *) client)), (HypeInstance *) id);
}

static void linked_list_callback_free_client(void **client)
{
    hpb_client_destroy((HpbClient **) client);
}
