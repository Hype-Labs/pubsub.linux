
#include "hype_pub_sub/client.h"

Client *hype_pub_sub_client_create(byte client_id[])
{
    Client* cl = (Client*) malloc(sizeof(Client));
    memcpy(cl->client_id, client_id, HYPE_ID_BYTE_SIZE);
    return cl;
}

void hype_pub_sub_client_destroy(Client *cl)
{
    if(cl == NULL)
        return;

    free(cl);
}
