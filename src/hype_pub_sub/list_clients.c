
#include "hype_pub_sub/list_clients.h"

ListClients *hype_pub_sub_list_clients_create()
{
    return linked_list_create();
}

int hype_pub_sub_list_clients_add(ListClients *list_cl, byte client_id[])
{
    if(hype_pub_sub_list_clients_is_inserted(list_cl, client_id))
        return -1;

    Client *cl = hype_pub_sub_client_create(client_id);
    return linked_list_add(list_cl, cl);
}

int hype_pub_sub_list_clients_remove(ListClients **list_cl, byte client_id[])
{
    return linked_list_remove(list_cl, client_id, compare_clients, free_client);
}

void hype_pub_sub_list_clients_destroy(ListClients* list_cl)
{
    linked_list_destroy(list_cl, free_client);
}

bool hype_pub_sub_list_clients_is_inserted(ListClients* list_cl, byte client_id[])
{
    return linked_list_is_element_inserted(list_cl, client_id, compare_clients);
}

bool compare_clients(void *cl1, void *cl2)
{
    if (cl1 == NULL || cl2 == NULL)
        return false;

    if (memcmp(((Client*) cl1)->client_id, (byte*) cl2, HYPE_ID_BYTE_SIZE * sizeof(byte)) == 0)
        return true;

    return false;
}

void free_client(void* cl)
{
    hype_pub_sub_client_destroy(((Client*) cl));
}
