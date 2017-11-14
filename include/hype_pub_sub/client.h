
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
typedef struct HpbClient_
{
    HLByte id[HPB_ID_BYTE_SIZE]; /**< ID of the Hype client. */
    HLByte key[SHA1_BLOCK_SIZE]; /**< Key of the managed service. */
} HpbClient;

/**
 * @brief Allocates space for a HpbClient struct, and initializes its ID and key.
 * @param id Hype ID of the node.
 * @return Returns a pointer to the created struct or NULL if the space could not be allocated.
 */
HpbClient *hpb_client_create(HLByte id[]);

/**
 * @brief Compares 2 client IDs.
 * @param id1 First client ID.
 * @param id2 Second client ID.
 * @return Returns true if the IDs are equal and false otherwise
 */
bool hpb_client_is_id_equal(HLByte id1[], HLByte id2[]);

/**
 * @brief Deallocates the space previously allocated for the given HpbClient struct.
 * @param client Pointer to the pointer of the HpbClient struct to be deallocated.
 */
void hpb_client_destroy(HpbClient **client);

#endif /* HPB_CLIENT_H_INCLUDED_ */
