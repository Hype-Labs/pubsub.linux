
#ifndef HPB_CLIENT_H_INCLUDED_
#define HPB_CLIENT_H_INCLUDED_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "sha/sha1.h"
#include "constants.h"
#include "binary_utils.h"

/**
 * @brief This struct represents an Hype client.
 */
typedef struct Client_
{
    byte id[HPB_ID_BYTE_SIZE]; /**< ID of the Hype client. */
    byte key[SHA1_BLOCK_SIZE]; /**< Key of the managed service. */
} Client;

/**
 * @brief Allocates space for a Client struct, and initializes its ID.
 * @param id Hype ID of the node.
 * @return Returns a pointer to the created struct or NULL if the space could not be allocated.
 */
Client *hpb_client_create(byte id[]);

bool hpb_client_is_id_equal(byte id1[], byte id2[]);

/**
 * @brief Deallocates the space previously allocated for a Client struct.
 * @param client Pointer to the Client struct to be deallocated.
 */
void hpb_client_destroy(Client **client);

#endif /* HPB_CLIENT_H_INCLUDED_ */
