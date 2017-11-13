
#ifndef HPB_SUBSCRIPTION_H_INCLUDED_
#define HPB_SUBSCRIPTION_H_INCLUDED_

#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "sha/sha1.h"
#include "binary_utils.h"

/**
 * @brief
 */
typedef struct HpbSubscription_
{
    char *service_name; /**< Name of the service subscribed. */
    byte service_key[SHA1_BLOCK_SIZE]; /**< Key of the service subscribed. */
    byte manager_id[HPB_ID_BYTE_SIZE]; /**< Hype ID of the manager of the service */
} HpbSubscription;

HpbSubscription *hpb_subscription_create(char *serv_name, size_t serv_name_len, byte man_id[HPB_ID_BYTE_SIZE]);

void hpb_subscription_destroy(HpbSubscription **subs);

#endif /* HPB_SUBSCRIPTION_H_INCLUDED_ */
