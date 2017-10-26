
#ifndef HYPE_PUB_SUB_SUBSCRIPTION_H_INCLUDED_
#define HYPE_PUB_SUB_SUBSCRIPTION_H_INCLUDED_

#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "sha/sha1.h"
#include "binary_utils.h"

/**
 * @brief
 */
typedef struct Subscription_
{
    char* service_name; /**< Name of the service subscribed. */
    byte service_key[SHA1_BLOCK_SIZE]; /**< Key of the service subscribed. */
    byte manager_id[HYPE_CONSTANTS_ID_BYTE_SIZE]; /**< Hype ID of the manager of the service */
} Subscription;

Subscription* hype_pub_sub_subscription_create(char* serv_name, size_t serv_name_len, byte man_id[HYPE_CONSTANTS_ID_BYTE_SIZE]);

void hype_pub_sub_subscription_destroy(Subscription **subs);

#endif /* HYPE_PUB_SUB_SUBSCRIPTION_H_INCLUDED_ */
