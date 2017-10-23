
#include "hype_pub_sub/network.h"

Network *hype_pub_sub_network_create()
{
    Network* net = (Network*) malloc(sizeof(Network));
    net->network_client_ids = hype_pub_sub_list_clients_create();
    return net;
}

byte *hype_pub_sub_network_get_service_manager_id(Network* net, byte service_key[])
{
    return NULL;
}

int hype_pub_sub_network_update_clients(Network* net)
{
    // On instance found -> hype_pub_sub_list_clients_add(net->network_client_ids, --- id ---)
    // On instance lost -> hype_pub_sub_list_clients_remove(net->network_client_ids, --- id ---)
    return 0;
}

bool hype_pub_sub_network_is_client_online(Network* net, byte client_id[])
{
    if(hype_pub_sub_list_clients_find(net->network_client_ids, client_id) != NULL)
        return true;
    return false;
}

void hype_pub_sub_network_destroy(Network *net)
{
    hype_pub_sub_list_clients_destroy(net->network_client_ids);
    free(net);
}
