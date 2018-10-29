
#include "hype_pub_sub/hpb_network.h"

HpbNetwork *hpb_network_create(HypeInstance *own_instance)
{
    HpbNetwork *net = (HpbNetwork*) malloc(sizeof(HpbNetwork));
    net->own_client = hpb_client_create(own_instance);
    net->network_clients = hpb_list_clients_create();
    return net;
}

HypeInstance *hpb_network_get_service_manager_id(HpbNetwork *net, HLByte service_key[])
{
    // Compare the service key with the hash of the Hype clients id and return
    // the id of the closest client. Consider own ID also!!!!

    HypeInstance *manager_instance = net->own_client->hype_instance;
    HLByte *lowest_dist = binary_utils_xor(service_key, net->own_client->key, SHA1_BLOCK_SIZE);

    LinkedListIterator *it = linked_list_iterator_create(net->network_clients);
    do
    {
        HpbClient *client = (HpbClient*) linked_list_iterator_get_element(it);

        if(client == NULL) {
            continue;
        }

        HLByte *dist = binary_utils_xor(service_key, client->key, SHA1_BLOCK_SIZE);

        if(binary_utils_get_higher_byte_array(lowest_dist, dist, SHA1_BLOCK_SIZE) == 1)
        {
            memcpy(lowest_dist, dist, SHA1_BLOCK_SIZE);
            manager_instance = client->hype_instance;
        }
        free(dist);

    } while(linked_list_iterator_advance(it) != -1);

    linked_list_iterator_destroy(&it);

    free(lowest_dist);

    return manager_instance;
}

void hpb_network_update_clients(HpbNetwork *net)
{
    // On instance found -> hype_pub_sub_list_clients_add(net->network_client_ids, --- id ---)
    // On instance lost -> hype_pub_sub_list_clients_remove(net->network_client_ids, --- id ---)
    return;
}

void hpb_network_destroy(HpbNetwork **net)
{
    if((*net) == NULL) {
        return;
    }

    hpb_client_destroy(&((*net)->own_client));
    hpb_list_clients_destroy(&((*net)->network_clients));
    free(*net);
    (*net) = NULL;
}
