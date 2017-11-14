
#include "hype_pub_sub/network.h"

HpbNetwork *hpb_network_create()
{
    HpbNetwork *net = (HpbNetwork*) malloc(sizeof(HpbNetwork));
    HLByte *own_id = hpb_network_get_own_id();
    net->own_client = hpb_client_create(own_id);
    net->network_clients = hpb_list_clients_create();
    free(own_id);
    return net;
}

HLByte *hpb_network_get_service_manager_id(HpbNetwork *net, HLByte service_key[])
{
    // Compare the service key with the hash of the Hype clients id and return
    // the id of the closest client. Consider own ID also!!!!

    HLByte *manager_id = net->own_client->id;
    HLByte *lowest_dist = binary_utils_xor(service_key, net->own_client->key, SHA1_BLOCK_SIZE);

    LinkedListIterator *it = linked_list_iterator_create(net->network_clients);
    do
    {
        HpbClient *client = (HpbClient*) linked_list_iterator_get_element(it);

        if(client == NULL)
            continue;

        HLByte *dist = binary_utils_xor(service_key, client->key, SHA1_BLOCK_SIZE);

        if(binary_utils_get_higher_binary_string(lowest_dist, dist, SHA1_BLOCK_SIZE) == 1)
        {
            memcpy(lowest_dist, dist, SHA1_BLOCK_SIZE);
            manager_id = client->id;
        }
        free(dist);

    } while(linked_list_iterator_advance(it) != -1);

    linked_list_iterator_destroy(&it);

    free(lowest_dist);

    return manager_id;
}

void hpb_network_update_clients(HpbNetwork *net)
{
    // On instance found -> hype_pub_sub_list_clients_add(net->network_client_ids, --- id ---)
    // On instance lost -> hype_pub_sub_list_clients_remove(net->network_client_ids, --- id ---)
    return;
}

bool hpb_network_is_client_online(HpbNetwork *net, HLByte client_id[])
{
    if(hpb_list_clients_find(net->network_clients, client_id) != NULL)
        return true;
    return false;
}

HLByte *hpb_network_get_own_id()
{
    // TODO: get from HypeSDK! Check memory allocation!
    // Dummy id just to prevent seg.fault when creating a network manager
    HLByte *own_id = (HLByte*) malloc(HPB_ID_BYTE_SIZE * sizeof(HLByte));
    memcpy(own_id, "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11\x12", HPB_ID_BYTE_SIZE);
    return own_id;
}

void hpb_network_destroy(HpbNetwork **net)
{
    if((*net) == NULL)
        return;

    hpb_client_destroy(&((*net)->own_client));
    hpb_list_clients_destroy(&((*net)->network_clients));
    free(*net);
    (*net) = NULL;
}
