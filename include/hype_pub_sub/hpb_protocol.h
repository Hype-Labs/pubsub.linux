
#ifndef HPB_PROTOCOL_H_INCLUDED_
#define HPB_PROTOCOL_H_INCLUDED_

#include <stdarg.h>

#include "hpb_constants.h"
#include "hype_pub_sub.h"

#define MESSAGE_TYPE_BYTE_SIZE 1

/**
 * @brief This struct represents the message types of the HpbProtocol packets.
 */
typedef enum  {SUBSCRIBE_SERVICE, /**< Represents a packet which contains a subscribe message */
               UNSUBSCRIBE_SERVICE, /**< Represents a packet which contains a unsubscribe message */
               PUBLISH, /**< Represents a packet which contains a publish message */
               INFO, /**< Represents a packet which contains a info message */
               INVALID /**< Represents a invalid packet */
} MessageType;

/**
 * @brief This struct represents an HpbProtocol manager.
 */
typedef struct HpbProtocol_
{
    struct HypePubSub_ *hpb; /**< Pointer to the HypePubSub application */
} HpbProtocol;

/**
 * @brief This struct represents a field which is a part of a protocol packet.
 */
typedef struct HpbProtocolPacketField_
{
    HLByte *data; /**< Byte array containing the data of the field */
    size_t size; /**< Size of the data byte array */
} HpbProtocolPacketField;

/**
 * @brief Allocates space for a HpbProtocol struct.
 * @return Returns a pointer to the created struct or NULL if the space could not be allocated.
 */
HpbProtocol *hpb_protocol_create(struct HypePubSub_ *hpb);

/**
 * @brief Method to send a subscribe message.
 * @param service_key Service to subscribe.
 * @param dest_network_id ID of the Hype device for which the message is destined.
 * @return
 */
HLByte *hpb_protocol_send_subscribe_msg(HLByte service_key[SHA1_BLOCK_SIZE], HypeInstance * instance_dest);

/**
 * @brief Method to send an unsubscribe message.
 * @param service_key Service to unsubscribe.
 * @param dest_network_id ID of the Hype device for which the message is destined.
 * @return
 */
HLByte *hpb_protocol_send_unsubscribe_msg(HLByte service_key[SHA1_BLOCK_SIZE], HypeInstance * instance_dest);

/**
 * @brief Method to send a publish message.
 * @param service_key Service in which to publish.
 * @param dest_network_id ID of the Hype device for which the message is destined.
 * @param msg Message to be published.
 * @param msg_length Length of the message to be published.
 * @return
 */
HLByte *hpb_protocol_send_publish_msg(HLByte service_key[SHA1_BLOCK_SIZE], HypeInstance * instance_dest, char *msg, size_t msg_length);

/**
 * @brief Method to send an info message.
 * @param service_key Service to which the info message belongs.
 * @param dest_network_id ID of the Hype device for which the message is destined.
 * @param msg Message to be sent.
 * @param msg_length Length of the message to be sent.
 * @return
 */
HLByte *hpb_protocol_send_info_msg(HLByte service_key[SHA1_BLOCK_SIZE], HypeInstance * instance_dest, char *msg, size_t msg_length);

/**
 * @brief Method called when a message is received.
 * @param protocol Pointer to the HpbProtocol.
 * @param origin_network_id ID of the Hype device which sent the message.
 * @param msg Received message.
 * @param msg_length Size of the received message.
 * @return Return 0 in case of success and -1 otherwise.
 */
int hpb_protocol_receive_msg(HpbProtocol *protocol, HypeInstance * instance_origin, HLByte *msg, size_t msg_length);

/**
 * @brief Deallocates the space previously allocated for the given HpbProtocol struct.
 * @param protocol Pointer to the pointer of the HpbProtocol struct to be deallocated.
 */
void hpb_protocol_destroy(HpbProtocol **protocol);

// TODO: Review this later. Currently it seems that these methods are replaced by the hpb_update_subscriptions() and hpb_update_managed_services() methods
// int hpb_protocol_send_change_service_manager_msg(byte service_key[SHA1_BLOCK_SIZE], byte dest_network_id[HYPE_CONSTANTS_ID_BYTE_SIZE], byte** subscribers_ids[SHA1_BLOCK_SIZE]);
// int hpb_protocol_receive_change_service_manager_msg(Protocol* protocol, char* msg);

#endif /* HPB_PROTOCOL_H_INCLUDED_ */
