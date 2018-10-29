
#include "hype_pub_sub/hpb_client.h"

HpbClient *hpb_client_create(HypeInstance *instance)
{
    HpbClient* client = (HpbClient*) malloc(sizeof(HpbClient));
    client->hype_instance = hype_instance_create(instance->identifier,instance->announcement,instance->is_resolved);
    sha1_digest(client->hype_instance->identifier->data, client->hype_instance->identifier->size, client->key);
    return client;
}

bool hpb_client_is_instance_equal(HpbClient *client, HypeInstance *instance)
{
    if(client->hype_instance->identifier->size == instance->identifier->size)
    {
        if(memcmp(client->hype_instance->identifier->data, instance->identifier->data, instance->identifier->size) == 0)
            return true;
    }

    return false;
}

void hpb_client_destroy(HpbClient **client)
{
    if((*client) == NULL) {
        return;
    }

    hype_instance_release((*client)->hype_instance);
    free(*client);
    (*client) = NULL;
}
