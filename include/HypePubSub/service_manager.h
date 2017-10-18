#include "sha_1.h"

#define HYPE_ID_BYTE_SIZE 12

typedef struct ServiceManager
{
    char serviceKey[SHA1_KEY_BYTE_SIZE];
    char ** subscribers[HYPE_ID_BYTE_SIZE];
} ServiceManager;

/**
 * @brief create
 * @param serviceKey
 * @return
 */
ServiceManager create(char serviceKey[SHA1_KEY_BYTE_SIZE]);

/**
 * @brief addSubscriber
 * @param servMan
 * @param subscriberId
 * @return
 */
int addSubscriber(ServiceManager* servMan, char subscriberId[HYPE_ID_BYTE_SIZE]);

/**
 * @brief removeSubscriber
 * @param servMan
 * @param subscriberId
 * @return
 */
int removeSubscriber(ServiceManager* servMan, char subscriberId[HYPE_ID_BYTE_SIZE]);

/**
 * @brief isSubscriberRegistered
 * @param servMan
 * @param subscriberId
 * @return
 */
bool isSubscriberRegistered(ServiceManager* servMan, char subscriberId[HYPE_ID_BYTE_SIZE]);

