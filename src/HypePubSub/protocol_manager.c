
#include "HypePubSub/protocol_manager.h"

int sendCreateServicePacket(char serviceKey[SHA1_KEY_BYTE_SIZE], char destNetworkId[HYPE_ID_BYTE_SIZE])
{
    return 0;
}

int sendSubscribePacket(char serviceKey[SHA1_KEY_BYTE_SIZE], char destNetworkId[HYPE_ID_BYTE_SIZE])
{
    return 0;
}

int sendUnsubscribePacket(char serviceKey[SHA1_KEY_BYTE_SIZE], char destNetworkId[HYPE_ID_BYTE_SIZE])
{
    return 0;
}

int sendPublishPacket(char serviceKey[SHA1_KEY_BYTE_SIZE], char destNetworkId[HYPE_ID_BYTE_SIZE], char* msg)
{
    return 0;
}

int sendChangeServiceManagerPacket(char serviceKey[SHA1_KEY_BYTE_SIZE], char destNetworkId[HYPE_ID_BYTE_SIZE], char** subscribersIds[SHA1_KEY_BYTE_SIZE])
{
    return 0;
}

int sendInfoPacket(char destNetworkId[HYPE_ID_BYTE_SIZE], char* string)
{
    return 0;
}

int receiveMsg(char originNetworkId[HYPE_ID_BYTE_SIZE])
{
    return 0;
}

int receiveSubscribePacket(char* msg)
{
    return 0;
}

int receiveUnsubscribePacket(char* msg)
{
    return 0;
}

int receivePublishPacket(char* msg)
{
    return 0;
}

int receiveChangeServiceManagerPacket(char* msg)
{
    return 0;
}

int receiveInfoPacket(char* msg)
{
    return 0;
}

message_type getMessageType(char* msg)
{
    return 0;
}
