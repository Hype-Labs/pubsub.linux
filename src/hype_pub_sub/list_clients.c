
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
    return linked_list_remove(list_cl, client_id, hpb_list_clients_compare_data_callback, hpb_list_clients_free_data_callback);
}

void hpb_list_clients_destroy(ListClients *list_cl)
{
    linked_list_destroy(&list_cl, hpb_list_clients_free_data_callback);
}

Client *hpb_list_clients_find(ListClients *list_cl, byte client_id[])
{
    ListClientElement *elem = linked_list_find(list_cl, client_id, hpb_list_clients_compare_data_callback);

    if(elem == NULL)
        return NULL;

    return (Client*) elem->element;
}

bool hpb_list_clients_compare_data_callback(void *cl1, void *cl2)
{
    if (cl1 == NULL || cl2 == NULL)
        return false;

    if (memcmp(((Client *) cl1)->id, (byte *) cl2, HPB_ID_BYTE_SIZE * sizeof(byte)) == 0)
        return true;

    return false;
}

void hpb_list_clients_free_data_callback(void **cl)
{
    Client **ptr = (Client **) cl;
    hpb_client_destroy(ptr);
}
