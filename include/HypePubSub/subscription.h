#include "sha_1.h"

typedef struct Subscription
{
    string serviceName;
    char serviceKey[SHA1_KEY_BYTE_SIZE];
    char managerID[HYPE_ID_BYTE_SIZE];
} Subscription;
