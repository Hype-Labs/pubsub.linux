#include "sha_1.h"

typedef struct Subscription
{
    string serviceName;
    char serviceKey[SHA1_KEY_BYTE_SIZE];
    char managerID[HYPE_ID_BYTE_SIZE];
} Subscription;

/**
 * @brief create
 * @param servName
 * @param manID
 * @return
 */
Subscription create(string servName, char manID[12]);
