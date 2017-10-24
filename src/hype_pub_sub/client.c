
#include "hype_pub_sub/client.h"

Client *hype_pub_sub_client_create(byte client_id[])
{
    Client* client = (Client*) malloc(sizeof(Client));
    memcpy(client->id, client_id, HYPE_ID_BYTE_SIZE);
    return client;
}

void hype_pub_sub_client_destroy(Client *client)
{
    if(client == NULL)
        return;

    free(client);
}
