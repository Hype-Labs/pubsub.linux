
#ifndef HPB_SUBSCRIPTION_H_INCLUDED_
#define HPB_SUBSCRIPTION_H_INCLUDED_

#include <stdlib.h>
#include <string.h>

#include "hpb_constants.h"
#include "sha/sha1.h"
#include "binary_utils.h"

/**
 * @brief This struct represents an HpbSubscription. Each subscription associates a certain service with a manager client.
 */
typedef struct HpbSubscription_
{
    char *service_name; /**< Name of the service subscribed. */
    HLByte service_key[SHA1_BLOCK_SIZE]; /**< Key of the service subscribed. */
    HLByte manager_id[HPB_ID_BYTE_SIZE]; /**< Hype ID of the manager of the service */
} HpbSubscription;

/**
 * @brief Allocates space for a HpbSubscription struct, and it initializes the service name, service key and manager ID.
 * @return Returns a pointer to the created struct or NULL if the space could not be allocated.
 */
HpbSubscription *hpb_subscription_create(char *serv_name, size_t serv_name_len, HLByte man_id[HPB_ID_BYTE_SIZE]);

/**
 * @brief Deallocates the space previously allocated for the given HpbSubscription struct.
 * @param subs Pointer to the pointer of the HpbSubscription struct to be deallocated.
 */
void hpb_subscription_destroy(HpbSubscription **subs);

#endif /* HPB_SUBSCRIPTION_H_INCLUDED_ */
