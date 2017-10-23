
#include "hype_pub_sub/network.h"

Network *hype_pub_sub_network_create()
{
    Network* net = (Network*) malloc(sizeof(Network));
    return net;
}

byte *hype_pub_sub_network_get_service_manager_id(Network* net, byte service_key[])
{
    return NULL;
}

int hype_pub_sub_network_update_clients(Network* net)
{
    return 0;
}

bool hype_pub_sub_network_is_client_online(Network* net, byte client_id[])
{
    return false;
}

void hype_pub_sub_network_destroy(Network *net)
{
    free(net);
}
