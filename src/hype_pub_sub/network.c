
#include "hype_pub_sub/network.h"

Network *hype_pub_sub_network_create()
{
    Network* net = (Network*) malloc(sizeof(Network));
    net->own_client = hype_pub_sub_client_create(hype_pub_sub_network_get_own_id());
    net->network_clients = hype_pub_sub_list_clients_create();
    return net;
}

byte *hype_pub_sub_network_get_service_manager_id(Network* net, byte service_key[])
{
    // Compare the service key with the hash of the Hype clients id and return
    // the id of the closest client. Consider own ID also!!!!

    byte *manager_id = net->own_client->id;
    byte *lowest_dist = binary_utils_xor(service_key, net->own_client->key, SHA1_BLOCK_SIZE);
    byte *dist = NULL;


    LinkedListIterator *it = linked_list_create_iterator(net->network_clients);
    while(linked_list_get_element_data_iterator(it) != NULL)
    {
        Client* client = (Client*) linked_list_get_element_data_iterator(it);

        byte *dist = binary_utils_xor(service_key, client->key, SHA1_BLOCK_SIZE);

        if(binary_utils_get_higher_binary_string(lowest_dist, dist, SHA1_BLOCK_SIZE) == 1)
        {
            memcpy(lowest_dist, dist, SHA1_BLOCK_SIZE);
            manager_id = client->id;
        }

        linked_list_advance_iterator(it);
    }
    linked_list_destroy_iterator(&it);


    free(lowest_dist);
    free(dist);

    return manager_id;
}

int hype_pub_sub_network_update_clients(Network* net)
{
    // On instance found -> hype_pub_sub_list_clients_add(net->network_client_ids, --- id ---)
    // On instance lost -> hype_pub_sub_list_clients_remove(net->network_client_ids, --- id ---)
    return 0;
}

bool hype_pub_sub_network_is_client_online(Network* net, byte client_id[])
{
    if(hype_pub_sub_list_clients_find(net->network_clients, client_id) != NULL)
        return true;
    return false;
}

byte* hype_pub_sub_network_get_own_id()
{
    // TODO: get from HypeSDK! Check memory allocation!
    // Dummy id just to prevent seg.fault when creating a network manager
    byte * own_id = (byte*) malloc(HYPE_CONSTANTS_ID_BYTE_SIZE * sizeof(byte));
    memcpy(own_id, "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11\x12", HYPE_CONSTANTS_ID_BYTE_SIZE);
    return own_id;
}

void hype_pub_sub_network_destroy(Network **net)
{
    if((*net) == NULL)
        return;

    hype_pub_sub_client_destroy(&((*net)->own_client));
    hype_pub_sub_list_clients_destroy((*net)->network_clients);
    free(*net);
    (*net) = NULL;
}
