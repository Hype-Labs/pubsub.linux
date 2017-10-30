
#include "hype_pub_sub/list_clients.h"

ListClients *hpb_list_clients_create()
{
    return linked_list_create();
}

Client *hpb_list_clients_add(ListClients *list_cl, byte client_id[])
{
    if(list_cl == NULL)
        return NULL;

    Client *cl;
    // Avoid to insert repeated Clients
    cl = hpb_list_clients_find(list_cl, client_id);
    if(cl != NULL)
        return cl;

    cl = hpb_client_create(client_id);
    linked_list_add(list_cl, cl);
    return cl;
}

int hpb_list_clients_remove(ListClients *list_cl, byte client_id[])
{
    return linked_list_remove(list_cl, client_id, linked_list_callback_is_client_id, linked_list_callback_free_client);
}

void hpb_list_clients_destroy(ListClients **list_cl)
{
    linked_list_destroy(list_cl, linked_list_callback_free_client);
}

Client *hpb_list_clients_find(ListClients *list_cl, byte client_id[])
{
    ListClientNode *node = linked_list_find(list_cl, client_id, linked_list_callback_is_client_id);

    if(node == NULL)
        return NULL;

    return (Client*) node->element;
}

static bool linked_list_callback_is_client_id(void *client, void *id)
{
    if (client == NULL || id == NULL)
        return false;

    return hpb_client_is_id_equal((((Client *) client)->id), (byte *) id);
}

static void linked_list_callback_free_client(void **client)
{
    hpb_client_destroy((Client **) client);
}
