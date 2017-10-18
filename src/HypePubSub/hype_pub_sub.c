
#include "HypePubSub/hype_pub_sub.h"

HypePubSub* createHypePubSub()
{
    return NULL;
}

int issueSubscribeServiceReq(char serviceKey[SHA1_KEY_BYTE_SIZE])
{
    return 0;
}

int issueUnsubscribeServiceReq(char serviceKey[SHA1_KEY_BYTE_SIZE])
{
    return 0;
}

int issuePublishReq(char serviceKey[SHA1_KEY_BYTE_SIZE], char* msg)
{
    return 0;
}

int processSubscribeReq(char serviceKey[SHA1_KEY_BYTE_SIZE], char requesterClientId[HYPE_ID_BYTE_SIZE])
{
    return 0;
}

int processUnsubscribeReq(char serviceKey[SHA1_KEY_BYTE_SIZE], char requesterClientId[HYPE_ID_BYTE_SIZE])
{
    return 0;
}

int processPublishReq(char serviceKey[SHA1_KEY_BYTE_SIZE], char* msg)
{
    return 0;
}

int processChangeServiceManagerReq(char serviceKey[SHA1_KEY_BYTE_SIZE], char newManagerId[HYPE_ID_BYTE_SIZE], char** subscribersId[HYPE_ID_BYTE_SIZE])
{
    return 0;
}

static int updateSubscriptionsManager()
{
    return 0;
}

static int issueChangeServiceManagerReq(char serviceKey[SHA1_KEY_BYTE_SIZE], char newManagerId[HYPE_ID_BYTE_SIZE], char** subscribersId[HYPE_ID_BYTE_SIZE])
{
    return 0;
}

static int removeServiceManager(char serviceKey[SHA1_KEY_BYTE_SIZE])
{
    return 0;
}

static int sendInfoMsg(char** destNetworkIds[HYPE_ID_BYTE_SIZE])
{
    return 0;
}
