
#ifndef HYPE_PUB_SUB_NETWORK_H_INCLUDED_
#define HYPE_PUB_SUB_NETWORK_H_INCLUDED_

#include <stdlib.h>
#include <stdbool.h>

#include "sha/sha1.h"
#include "constants.h"

/**
 * @brief
 */
typedef struct Network_
{
    byte own_client_id[HYPE_ID_BYTE_SIZE]; /**< Hype ID of this client. */
    byte ** network_client_ids[HYPE_ID_BYTE_SIZE]; /**< Hype ID of the clients of the network. */
} Network;

Network* hype_pub_sub_network_create();

void hype_pub_sub_network_destroy(Network* net_man);

byte* hype_pub_sub_network_get_service_manager_id(byte service_key[SHA1_BLOCK_SIZE]);

int hype_pub_sub_network_update_clients();

bool hype_pub_sub_network_is_client_online(byte client_id[HYPE_ID_BYTE_SIZE]);

byte* hype_pub_sub_network_get_own_client_id();

#endif /* HYPE_PUB_SUB_NETWORK_H_INCLUDED_ */
