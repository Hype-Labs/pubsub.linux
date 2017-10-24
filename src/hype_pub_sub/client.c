
#include "hype_pub_sub/client.h"

Client *hype_pub_sub_client_create(byte id[])
{
    Client* client = (Client*) malloc(sizeof(Client));
    memcpy(client->id, id, HYPE_CONSTANTS_ID_BYTE_SIZE);
    return client;
}

void hype_pub_sub_client_destroy(Client *client)
{
    free(client);
}
