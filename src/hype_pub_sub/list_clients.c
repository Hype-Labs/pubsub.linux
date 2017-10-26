
#include "hype_pub_sub/list_clients.h"

ListClients *hype_pub_sub_list_clients_create()
{
    return linked_list_create();
}

Client* hype_pub_sub_list_clients_add(ListClients *list_cl, byte client_id[])
{
    if(list_cl == NULL)
        return NULL;

    Client *cl;
    // Avoid to insert repeated Clients
    cl = hype_pub_sub_list_clients_find(list_cl, client_id);
    if(cl != NULL)
        return cl;

    cl = hype_pub_sub_client_create(client_id);
    linked_list_add(list_cl, cl);
    return cl;
}

int hype_pub_sub_list_clients_remove(ListClients *list_cl, byte client_id[])
{
    return linked_list_remove(list_cl, client_id, hype_pub_sub_list_clients_compare_data_callback, hype_pub_sub_list_clients_free_data_callback);
}

void hype_pub_sub_list_clients_destroy(ListClients *list_cl)
{
    linked_list_destroy(&list_cl, hype_pub_sub_list_clients_free_data_callback);
}

Client* hype_pub_sub_list_clients_find(ListClients* list_cl, byte client_id[])
{
    ListClientElement *elem = linked_list_find(list_cl, client_id, hype_pub_sub_list_clients_compare_data_callback);

    if(elem == NULL)
        return NULL;

    return (Client*) elem->data;
}

bool hype_pub_sub_list_clients_compare_data_callback(void *cl1, void *cl2)
{
    if (cl1 == NULL || cl2 == NULL)
        return false;

    if (memcmp(((Client*) cl1)->id, (byte*) cl2, HYPE_CONSTANTS_ID_BYTE_SIZE * sizeof(byte)) == 0)
        return true;

    return false;
}

void hype_pub_sub_list_clients_free_data_callback(void** cl)
{
    Client **ptr = (Client**) cl;
    hype_pub_sub_client_destroy(ptr);
}
