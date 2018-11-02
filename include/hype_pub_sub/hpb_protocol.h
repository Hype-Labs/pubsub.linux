
#ifndef HPB_PROTOCOL_H_INCLUDED_
#define HPB_PROTOCOL_H_INCLUDED_

#include <stdarg.h>

#include "hpb_constants.h"
#include "hype_pub_sub.h"

#define MESSAGE_TYPE_BYTE_SIZE 1

/**
 * @brief This struct represents the message types of the HpbProtocol packets.
 */
typedef enum {
    SUBSCRIBE_SERVICE, /**< Represents a packet which contains a subscribe message */
    UNSUBSCRIBE_SERVICE, /**< Represents a packet which contains a unsubscribe message */
    PUBLISH, /**< Represents a packet which contains a publish message */
    INFO, /**< Represents a packet which contains a info message */
    INVALID /**< Represents a invalid packet */
} MessageType;

/**
 * @brief This struct represents a field which is a part of a protocol packet.
 */
typedef struct HpbProtocolPacketField_
{
    HLByte *data; /**< Byte array containing the data of the field */
    size_t size; /**< Size of the data byte array */
} HpbProtocolPacketField;

/**
 * @brief Method to send a subscribe message.
 * @param service_key Service to subscribe.
 * @param packet In-out parameter where the packet is stored.
 * @return Returns the size of the packet created.
 */
size_t hpb_protocol_build_subscribe_msg(HLByte service_key[SHA1_BLOCK_SIZE], HLByte ** packet);

/**
 * @brief Method to send an unsubscribe message.
 * @param service_key Service to unsubscribe.
 * @param packet In-out parameter where the packet is stored.
 * @return Returns the size of the packet created.
 */
size_t hpb_protocol_build_unsubscribe_msg(HLByte service_key[SHA1_BLOCK_SIZE], HLByte ** packet);

/**
 * @brief Method to send a publish message.
 * @param service_key Service in which to publish.
 * @param msg Message to be published.
 * @param msg_length Length of the message to be published.
 * @param packet In-out parameter where the packet is stored.
 * @return Returns the size of the packet created.
 */
size_t hpb_protocol_build_publish_msg(HLByte service_key[SHA1_BLOCK_SIZE], char *msg, size_t msg_length, HLByte ** packet);

/**
 * @brief Method to send an info message.
 * @param service_key Service to which the info message belongs.
 * @param msg Message to be sent.
 * @param msg_length Length of the message to be sent.
 * @param packet In-out parameter where the packet is stored.
 * @return Returns the size of the packet created.
 */
size_t hpb_protocol_build_info_msg(HLByte service_key[SHA1_BLOCK_SIZE], char *msg, size_t msg_length, HLByte ** packet);

/**
 * @brief Method called when a message is received.
 * @param origin_network_id ID of the Hype device which sent the message.
 * @param msg Received message.
 * @param msg_length Size of the received message.
 * @return Return 0 in case of success and -1 otherwise.
 */
int hpb_protocol_receive_msg(HypeInstance * instance_origin, HLByte *msg, size_t msg_length);

#endif /* HPB_PROTOCOL_H_INCLUDED_ */
