#include "HypePubSub/constants.h"

typedef enum  {SUBSCRIBE_SERVICE,
               UNSUBSCRIBE_SERVICE,
               PUBLISH,
               INFO,
               CHANGE_SERVICE_MANAGER} message_type;

/**
 * @brief sendCreateServicePacket
 * @param serviceKey
 * @param destNetworkId
 * @return
 */
int sendCreateServicePacket(char serviceKey[SHA1_KEY_BYTE_SIZE], char destNetworkId[HYPE_ID_BYTE_SIZE]);

/**
 * @brief sendSubscribePacket
 * @param serviceKey
 * @param destNetworkId
 * @return
 */
int sendSubscribePacket(char serviceKey[SHA1_KEY_BYTE_SIZE], char destNetworkId[HYPE_ID_BYTE_SIZE]);

/**
 * @brief sendUnsubscribePacket
 * @param serviceKey
 * @param destNetworkId
 * @return
 */
int sendUnsubscribePacket(char serviceKey[SHA1_KEY_BYTE_SIZE], char destNetworkId[HYPE_ID_BYTE_SIZE]);

/**
 * @brief sendPublishPacket
 * @param serviceKey
 * @param destNetworkId
 * @param msg
 * @return
 */
int sendPublishPacket(char serviceKey[SHA1_KEY_BYTE_SIZE], char destNetworkId[HYPE_ID_BYTE_SIZE], char* msg);

/**
 * @brief sendChangeServiceManagerPacket
 * @param serviceKey
 * @param destNetworkId
 * @param subscribersIds
 * @return
 */
int sendChangeServiceManagerPacket(char serviceKey[SHA1_KEY_BYTE_SIZE], char destNetworkId[HYPE_ID_BYTE_SIZE], char** subscribersIds[SHA1_KEY_BYTE_SIZE]);

/**
 * @brief sendInfoPacket
 * @param destNetworkId
 * @param string
 * @return
 */
int sendInfoPacket(char destNetworkId[HYPE_ID_BYTE_SIZE], char* string);

/**
 * @brief receiveMsg
 * @param originNetworkId
 * @return
 */
int receiveMsg(char originNetworkId[HYPE_ID_BYTE_SIZE]);

/**
 * @brief receiveSubscribePacket
 * @param msg
 * @return
 */
int receiveSubscribePacket(char* msg);

/**
 * @brief receiveUnsubscribePacket
 * @param msg
 * @return
 */
int receiveUnsubscribePacket(char* msg);

/**
 * @brief receivePublishPacket
 * @param msg
 * @return
 */
int receivePublishPacket(char* msg);

/**
 * @brief receiveChangeServiceManagerPacket
 * @param msg
 * @return
 */
int receiveChangeServiceManagerPacket(char* msg);

/**
 * @brief receiveInfoPacket
 * @param msg
 * @return
 */
int receiveInfoPacket(char* msg);

/**
 * @brief getMessageType
 * @param msg
 * @return
 */
message_type getMessageType(char* msg);
