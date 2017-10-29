
#include "hype_pub_sub/client.h"

Client *hpb_client_create(byte id[])
{
    Client* client = (Client*) malloc(sizeof(Client));
    memcpy(client->id, id, HPB_ID_BYTE_SIZE);
    sha1_digest(client->id, HPB_ID_BYTE_SIZE, client->key);
    return client;
}

bool hpb_client_is_id_equal(byte id1[], byte id2[])
{
    if(memcmp(id1, id2, HPB_ID_BYTE_SIZE * sizeof(byte)) == 0)
        return true;
    return false;
}

void hpb_client_destroy(Client **client)
{
    free(*client);
    (*client) = NULL;
}
