#include <stdlib.h>

#include "constants.h"

/**
 * @brief
 */
typedef struct Subscription
{
    char* serviceName; /**< Name of the service subscribed. */
    char serviceKey[SHA1_KEY_BYTE_SIZE]; /**< Key of the service subscribed. */
    char managerID[HYPE_ID_BYTE_SIZE]; /**< Hype ID of the manager of the service */
} Subscription;

/**
 * @brief createSubscription
 * @param servName
 * @param manID
 * @return
 */
Subscription* createSubscription(char* servName, char manID[HYPE_ID_BYTE_SIZE]);
