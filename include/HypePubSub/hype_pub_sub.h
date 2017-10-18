#include <stdlib.h>

#include "service_manager.h"
#include "subscription.h"

/**
 * @brief
 */
typedef struct HypePubSub
{
    Subscription* subscriptions; /**< Subscriptions of this client. */
    ServiceManager* managedServices; /**< Services managed by this client*/
} HypePubSub;

/**
 * @brief createHypePubSub
 * @return
 */
HypePubSub* createHypePubSub();

/**
 * @brief issueSubscribeServiceReq
 * @param serviceKey
 * @return
 */
int issueSubscribeServiceReq(char serviceKey[20]);

/**
 * @brief issueUnsubscribeServiceReq
 * @param serviceKey
 * @return
 */
int issueUnsubscribeServiceReq(char serviceKey[20]);

/**
 * @brief issuePublishReq
 * @param serviceKey
 * @param msg
 * @return
 */
int issuePublishReq(char serviceKey[20], char* msg);

/**
 * @brief processSubscribeReq
 * @param serviceKey
 * @param requesterClientId
 * @return
 */
int processSubscribeReq(char serviceKey[20], char requesterClientId[12]);

/**
 * @brief processUnsubscribeReq
 * @param serviceKey
 * @param requesterClientId
 * @return
 */
int processUnsubscribeReq(char serviceKey[20], char requesterClientId[12]);

/**
 * @brief processPublishReq
 * @param serviceKey
 * @param msg
 * @return
 */
int processPublishReq(char serviceKey[20], char* msg);

/**
 * @brief processChangeServiceManagerReq
 * @param serviceKey
 * @param newManagerId
 * @param subscribersId
 * @return
 */
int processChangeServiceManagerReq(char serviceKey[20], char newManagerId[12], char** subscribersId[12]);

/**
 * @brief updateSubscriptionsManager
 * @return
 */
static int updateSubscriptionsManager();

/**
 * @brief issueChangeServiceManagerReq
 * @param serviceKey
 * @param newManagerId
 * @param subscribersId
 * @return
 */
static int issueChangeServiceManagerReq(char serviceKey[20], char newManagerId[12], char** subscribersId[12]);

/**
 * @brief removeServiceManager
 * @param serviceKey
 * @return
 */
static int removeServiceManager(char serviceKey[20]);

/**
 * @brief sendInfoMsg
 * @param destNetworkIds
 * @return
 */
static int sendInfoMsg(char** destNetworkIds[12]);
