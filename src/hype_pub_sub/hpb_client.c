
#include "hype_pub_sub/hpb_client.h"

HpbClient *hpb_client_create(HypeInstance * instance)
{
    HpbClient* client = (HpbClient*) malloc(sizeof(HpbClient));
    client->hype_instance = hype_instance_create(instance->identifier,instance->announcement,instance->is_resolved);
    sha1_digest(client->hype_instance->identifier->data, client->hype_instance->identifier->size, client->key);

    return client;
}

bool hpb_client_is_id_equal(HypeInstance * instance1, HypeInstance * instance2)
{
    if(instance1->identifier->size == instance2->identifier->size)
    {
        if(memcmp(instance1->identifier->data, instance2->identifier->data, instance1->identifier->size) == 0)
            return true;

    }

    return false;
}

void hpb_client_destroy(HpbClient **client)
{
    free(*client);
    hype_instance_release((*client)->hype_instance);
    (*client) = NULL;
}
