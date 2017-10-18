
#include "HypePubSub/hype_pub_sub.h"

HypePubSub* createHypePubSub()
{
    return NULL;
}

int issueSubscribeServiceReq(char serviceKey[20])
{
    return 0;
}

int issueUnsubscribeServiceReq(char serviceKey[20])
{
    return 0;
}

int issuePublishReq(char serviceKey[20], char* msg)
{
    return 0;
}

int processSubscribeReq(char serviceKey[20], char requesterClientId[12])
{
    return 0;
}

int processUnsubscribeReq(char serviceKey[20], char requesterClientId[12])
{
    return 0;
}

int processPublishReq(char serviceKey[20], char* msg)
{
    return 0;
}

int processChangeServiceManagerReq(char serviceKey[20], char newManagerId[12], char** subscribersId[12])
{
    return 0;
}

static int updateSubscriptionsManager()
{
    return 0;
}

static int issueChangeServiceManagerReq(char serviceKey[20], char newManagerId[12], char** subscribersId[12])
{
    return 0;
}

static int removeServiceManager(char serviceKey[20])
{
    return 0;
}

static int sendInfoMsg(char** destNetworkIds[12])
{
    return 0;
}
