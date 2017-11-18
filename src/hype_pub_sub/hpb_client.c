
#include "hype_pub_sub/hpb_client.h"

HpbClient *hpb_client_create(HLByte id[])
{
    HpbClient* client = (HpbClient*) malloc(sizeof(HpbClient));
    memcpy(client->id, id, HPB_ID_BYTE_SIZE);
    sha1_digest(client->id, HPB_ID_BYTE_SIZE, client->key);
    return client;
}

bool hpb_client_is_id_equal(HLByte id1[], HLByte id2[])
{
    if(memcmp(id1, id2, HPB_ID_BYTE_SIZE * sizeof(HLByte)) == 0)
        return true;
    return false;
}

void hpb_client_destroy(HpbClient **client)
{
    free(*client);
    (*client) = NULL;
}
