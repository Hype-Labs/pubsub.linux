
#ifndef HYPE_PUB_SUB_NETWORK_H_INCLUDED_
#define HYPE_PUB_SUB_NETWORK_H_INCLUDED_

#include <stdlib.h>
#include <stdbool.h>

#include "sha/sha1.h"
#include "constants.h"

/**
 * @brief
 */
typedef struct NetworkManager_
{
    byte own_client_id[HYPE_ID_BYTE_SIZE]; /**< Hype ID of this client. */
    byte ** network_client_ids[HYPE_ID_BYTE_SIZE]; /**< Hype ID of the clients of the network. */
} NetworkManager;


/**
 * @brief hype_pub_sub_network_create
 * @return
 */
NetworkManager* hype_pub_sub_network_create();

/**
 * @brief hype_pub_sub_network_get_service_manager_id
 * @param service_key
 * @return
 */
byte* hype_pub_sub_network_get_service_manager_id(byte service_key[SHA1_BLOCK_SIZE]); // TODO: Check return type

/**
 * @brief hype_pub_sub_network_update_clients
 * @return
 */
int hype_pub_sub_network_update_clients();

/**
 * @brief hype_pub_sub_network_is_client_online
 * @param client_id
 * @return
 */
bool hype_pub_sub_network_is_client_online(byte client_id[HYPE_ID_BYTE_SIZE]);

/**
 * @brief hype_pub_sub_network_get_own_client_id
 * @return
 */
byte* hype_pub_sub_network_get_own_client_id(); // TODO: Check return type

#endif /* HYPE_PUB_SUB_NETWORK_H_INCLUDED_ */
