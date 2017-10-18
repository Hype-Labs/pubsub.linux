#include "sha_1.h"

#define HYPE_ID_BYTE_SIZE 12

typedef struct ServiceManager
{
    char serviceKey[SHA1_KEY_BYTE_SIZE];
    char ** subscribers[HYPE_ID_BYTE_SIZE];
} ServiceManager;

// Service Manager
ServiceManager create(char serviceKey[SHA1_KEY_BYTE_SIZE]);
int addSubscriber(ServiceManager* servMan, char subscriberId[HYPE_ID_BYTE_SIZE]);
int removeSubscriber(ServiceManager* servMan, char subscriberId[HYPE_ID_BYTE_SIZE]);
bool isSubscriberRegistered(ServiceManager* servMan, char subscriberId[HYPE_ID_BYTE_SIZE]);

