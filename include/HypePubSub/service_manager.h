#include <stdlib.h>
#include <stdbool.h>

#include "sha_1.h"
#include "constants.h"

/**
 * @brief
 */
typedef struct ServiceManager
{
    char serviceKey[SHA1_KEY_BYTE_SIZE]; /**< Key of the managed service. */
    char ** subscribers[HYPE_ID_BYTE_SIZE]; /**< Subscribers of the service. */
} ServiceManager;

/**
 * @brief createServiceManager
 * @param serviceKey
 * @return
 */
ServiceManager* createServiceManager(char serviceKey[SHA1_KEY_BYTE_SIZE]);

/**
 * @brief addSubscriberToServiceManager
 * @param servMan
 * @param subscriberId
 * @return
 */
int addSubscriberToServiceManager(ServiceManager* servMan, char subscriberId[HYPE_ID_BYTE_SIZE]);

/**
 * @brief removeSubscriberFromServiceManager
 * @param servMan
 * @param subscriberId
 * @return
 */
int removeSubscriberFromServiceManager(ServiceManager* servMan, char subscriberId[HYPE_ID_BYTE_SIZE]);

/**
 * @brief isSubscriberInServiceManager
 * @param servMan
 * @param subscriberId
 * @return
 */
bool isSubscriberInServiceManager(ServiceManager* servMan, char subscriberId[HYPE_ID_BYTE_SIZE]);

