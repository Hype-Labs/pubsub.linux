
#ifndef HPB_CLIENT_H_INCLUDED_
#define HPB_CLIENT_H_INCLUDED_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "sha/sha1.h"
#include "hpb_constants.h"
#include "binary_utils.h"
#include <hype/hype.h>


/**
 * @brief This struct represents a publisher-subscriber client.
 */
typedef struct HpbClient_
{
    HypeInstance *hype_instance;/**< Hype instance of the client. */
    HLByte key[SHA1_BLOCK_SIZE]; /**< Key of the managed service. */
} HpbClient;

/**
 * @brief Allocates space for a HpbClient struct, and initializes its instance and key.
 *        It allocates spaces for a new Hype instance struct which is initialized
 *        with the content of the instance given as parameter.
 * @param instance Hype instance of the client.
 * @return Returns a pointer to the created struct.
 */
HpbClient * hpb_client_create(HypeInstance *instance);

/**
 * @brief Compares the instance of the given HpbClient with the instance given as parameter.
 * @param client HpbClient to be analyzed.
 * @param instance Hype instance to which the HpbClient should be compared to.
 * @return Returns true if the given instance is equal to the instance of the HpbClient and false otherwise.
 */
bool hpb_client_is_instance_equal(HpbClient *client, HypeInstance *instance);

/**
 * @brief Deallocates the space previously allocated for the given HpbClient struct.
 * @param client Pointer to the pointer of the HpbClient struct to be deallocated.
 */
void hpb_client_destroy(HpbClient **client);

#endif /* HPB_CLIENT_H_INCLUDED_ */
