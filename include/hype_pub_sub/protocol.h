
#ifndef HPB_PROTOCOL_H_INCLUDED_
#define HPB_PROTOCOL_H_INCLUDED_

#include <stdarg.h>

#include "constants.h"
#include "hype_pub_sub.h"

#define MESSAGE_TYPE_BYTE_SIZE 1

typedef struct HypePubSub_ HypePubSub; // Forward declaration due to circular dependency

typedef enum  {SUBSCRIBE_SERVICE,
               UNSUBSCRIBE_SERVICE,
               PUBLISH,
               INFO,
               INVALID} MessageType;

/**
 * @brief
 */
typedef struct HpbProtocol_
{
    HypePubSub *hpb;
} HpbProtocol;

typedef struct PacketField_
{
    byte *data;
    size_t size;
} PacketField;

HpbProtocol *hpb_protocol_create(HypePubSub *hpb);

byte *hpb_protocol_send_subscribe_msg(byte service_key[SHA1_BLOCK_SIZE], byte dest_network_id[HPB_ID_BYTE_SIZE]);

byte *hpb_protocol_send_unsubscribe_msg(byte service_key[SHA1_BLOCK_SIZE], byte dest_network_id[HPB_ID_BYTE_SIZE]);

byte *hpb_protocol_send_publish_msg(byte service_key[SHA1_BLOCK_SIZE], byte dest_network_id[HPB_ID_BYTE_SIZE], char *msg, size_t msg_length);

byte *hpb_protocol_send_info_msg(byte service_key[SHA1_BLOCK_SIZE], byte dest_network_id[HPB_ID_BYTE_SIZE], char *msg, size_t msg_length);

byte *hpb_protocol_build_packet(int n_fields, ...);

int hpb_protocol_receive_msg(HpbProtocol *protocol, byte origin_network_id[], byte *msg, size_t msg_length);

int hpb_protocol_receive_subscribe_msg(HpbProtocol *protocol, byte origin_network_id[], byte *msg, size_t msg_length);

int hpb_protocol_receive_unsubscribe_msg(HpbProtocol *protocol, byte origin_network_id[], byte *msg, size_t msg_length);

int hpb_protocol_receive_publish_msg(HpbProtocol *protocol, byte origin_network_id[], byte *msg, size_t msg_length);

int hpb_protocol_receive_info_msg(HpbProtocol *protocol, byte *msg, size_t msg_length);

MessageType hpb_protocol_get_message_type(byte *msg);

void hpb_protocol_destroy(HpbProtocol **protocol);

// TODO: Review this later. Currently it seems that these methods are replaced by the hpb_update_subscriptions() and hpb_update_managed_services() methods
// int hpb_protocol_send_change_service_manager_msg(byte service_key[SHA1_BLOCK_SIZE], byte dest_network_id[HYPE_CONSTANTS_ID_BYTE_SIZE], byte** subscribers_ids[SHA1_BLOCK_SIZE]);
// int hpb_protocol_receive_change_service_manager_msg(Protocol* protocol, char* msg);

#endif /* HPB_PROTOCOL_H_INCLUDED_ */
