
#ifndef HYPE_PUB_SUB_CLIENT_H_INCLUDED_
#define HYPE_PUB_SUB_CLIENT_H_INCLUDED_

#include <stdlib.h>
#include <string.h>

#include "constants.h"

typedef struct Client_
{
    byte id[HYPE_ID_BYTE_SIZE];
} Client;

Client* hype_pub_sub_client_create(byte client_id[]);

void hype_pub_sub_client_destroy(Client* client);

#endif /* HYPE_PUB_SUB_CLIENT_H_INCLUDED_ */
