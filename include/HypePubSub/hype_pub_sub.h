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
int issueSubscribeServiceReq(char serviceKey[SHA1_KEY_BYTE_SIZE]);

/**
 * @brief issueUnsubscribeServiceReq
 * @param serviceKey
 * @return
 */
int issueUnsubscribeServiceReq(char serviceKey[SHA1_KEY_BYTE_SIZE]);

/**
 * @brief issuePublishReq
 * @param serviceKey
 * @param msg
 * @return
 */
int issuePublishReq(char serviceKey[SHA1_KEY_BYTE_SIZE], char* msg);

/**
 * @brief processSubscribeReq
 * @param serviceKey
 * @param requesterClientId
 * @return
 */
int processSubscribeReq(char serviceKey[SHA1_KEY_BYTE_SIZE], char requesterClientId[HYPE_ID_BYTE_SIZE]);

/**
 * @brief processUnsubscribeReq
 * @param serviceKey
 * @param requesterClientId
 * @return
 */
int processUnsubscribeReq(char serviceKey[SHA1_KEY_BYTE_SIZE], char requesterClientId[HYPE_ID_BYTE_SIZE]);

/**
 * @brief processPublishReq
 * @param serviceKey
 * @param msg
 * @return
 */
int processPublishReq(char serviceKey[SHA1_KEY_BYTE_SIZE], char* msg);

/**
 * @brief processChangeServiceManagerReq
 * @param serviceKey
 * @param newManagerId
 * @param subscribersId
 * @return
 */
int processChangeServiceManagerReq(char serviceKey[SHA1_KEY_BYTE_SIZE], char newManagerId[HYPE_ID_BYTE_SIZE], char** subscribersId[HYPE_ID_BYTE_SIZE]);

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
static int issueChangeServiceManagerReq(char serviceKey[SHA1_KEY_BYTE_SIZE], char newManagerId[HYPE_ID_BYTE_SIZE], char** subscribersId[HYPE_ID_BYTE_SIZE]);

/**
 * @brief removeServiceManager
 * @param serviceKey
 * @return
 */
static int removeServiceManager(char serviceKey[SHA1_KEY_BYTE_SIZE]);

/**
 * @brief sendInfoMsg
 * @param destNetworkIds
 * @return
 */
static int sendInfoMsg(char** destNetworkIds[HYPE_ID_BYTE_SIZE]);
