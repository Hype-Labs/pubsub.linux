
#ifndef HYPE_PUB_SUB_PROTOCOL_H_INCLUDED_
#define HYPE_PUB_SUB_PROTOCOL_H_INCLUDED_

#include "constants.h"
#include "hype_pub_sub.h"

typedef struct HypePubSub_ HypePubSub; // Forward declaration due to circular dependency

typedef enum  {SUBSCRIBE_SERVICE,
               UNSUBSCRIBE_SERVICE,
               PUBLISH,
               INFO,
               CHANGE_SERVICE_MANAGER} MessageType;

/**
 * @brief
 */
typedef struct Protocol_
{
    HypePubSub* application; /**< Hype ID of this client. */
} Protocol;

Protocol* hype_pub_sub_protocol_create(HypePubSub* pub_sub);

void hype_pub_sub_protocol_destroy(Protocol* protocol);

int hype_pub_sub_protocol_send_subscribe_msg(byte service_key[SHA1_BLOCK_SIZE], byte dest_network_id[HYPE_ID_BYTE_SIZE]);

int hype_pub_sub_protocol_send_unsubscribe_msg(byte service_key[SHA1_BLOCK_SIZE], byte dest_network_id[HYPE_ID_BYTE_SIZE]);

int hype_pub_sub_protocol_send_publish_msg(byte service_key[SHA1_BLOCK_SIZE], byte dest_network_id[HYPE_ID_BYTE_SIZE], char* msg);

int hype_pub_sub_protocol_send_change_service_manager_msg(byte service_key[SHA1_BLOCK_SIZE], byte dest_network_id[HYPE_ID_BYTE_SIZE], byte** subscribers_ids[SHA1_BLOCK_SIZE]);

int hype_pub_sub_protocol_send_info_msg(Protocol* protocol, byte dest_network_id[HYPE_ID_BYTE_SIZE], char* string);

int hype_pub_sub_protocol_receive_msg(Protocol* protocol, byte origin_network_id[HYPE_ID_BYTE_SIZE]);

int hype_pub_sub_protocol_receive_subscribe_msg(Protocol* protocol, char* msg);

int hype_pub_sub_protocol_receive_unsubscribe_msg(Protocol* protocol, char* msg);

int hype_pub_sub_protocol_receive_publish_msg(Protocol* protocol, char* msg);

int hype_pub_sub_protocol_receive_change_service_manager_msg(Protocol* protocol, char* msg);

int hype_pub_sub_protocol_receive_info_msg(Protocol* protocol, char* msg);

static MessageType hype_pub_sub_protocol_get_message_type(char* msg);

#endif /* HYPE_PUB_SUB_PROTOCOL_H_INCLUDED_ */
