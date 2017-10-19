
#ifndef HYPE_PUB_SUB_PROTOCOL_H_INCLUDED_
#define HYPE_PUB_SUB_PROTOCOL_H_INCLUDED_

#include "constants.h"
#include "hype_pub_sub.h"

typedef enum  {SUBSCRIBE_SERVICE,
               UNSUBSCRIBE_SERVICE,
               PUBLISH,
               INFO,
               CHANGE_SERVICE_MANAGER} MessageType;

/**
 * @brief
 */
typedef struct ProtocolManager_
{
    HypePubSub* application; /**< Hype ID of this client. */
} ProtocolManager;

/**
 * @brief hype_pub_sub_protocol_create
 * @param pub_sub
 * @return
 */
ProtocolManager* hype_pub_sub_protocol_create(HypePubSub* pub_sub);

/**
 * @brief hype_pub_sub_protocol_send_subscribe_msg
 * @param service_key
 * @param dest_network_id
 * @return
 */
int hype_pub_sub_protocol_send_subscribe_msg(char service_key[SHA1_KEY_BYTE_SIZE], char dest_network_id[HYPE_ID_BYTE_SIZE]);

/**
 * @brief hype_pub_sub_protocol_send_unsubscribe_msg
 * @param service_key
 * @param dest_network_id
 * @return
 */
int hype_pub_sub_protocol_send_unsubscribe_msg(char service_key[SHA1_KEY_BYTE_SIZE], char dest_network_id[HYPE_ID_BYTE_SIZE]);

/**
 * @brief hype_pub_sub_protocol_send_publish_msg
 * @param service_key
 * @param dest_network_id
 * @param msg
 * @return
 */
int hype_pub_sub_protocol_send_publish_msg(char service_key[SHA1_KEY_BYTE_SIZE], char dest_network_id[HYPE_ID_BYTE_SIZE], char* msg);

/**
 * @brief hype_pub_sub_protocol_send_change_service_manager_msg
 * @param service_key
 * @param dest_network_id
 * @param subscribers_ids
 * @return
 */
int hype_pub_sub_protocol_send_change_service_manager_msg(char service_key[SHA1_KEY_BYTE_SIZE], char dest_network_id[HYPE_ID_BYTE_SIZE], char** subscribers_ids[SHA1_KEY_BYTE_SIZE]);

/**
 * @brief hype_pub_sub_protocol_send_info_msg
 * @param protocol
 * @param dest_network_id
 * @param string
 * @return
 */
int hype_pub_sub_protocol_send_info_msg(ProtocolManager* protocol, char dest_network_id[HYPE_ID_BYTE_SIZE], char* string);

/**
 * @brief hype_pub_sub_protocol_receive_msg
 * @param protocol
 * @param origin_network_id
 * @return
 */
int hype_pub_sub_protocol_receive_msg(ProtocolManager* protocol, char origin_network_id[HYPE_ID_BYTE_SIZE]);

/**
 * @brief hype_pub_sub_protocol_receive_subscribe_msg
 * @param protocol
 * @param msg
 * @return
 */
int hype_pub_sub_protocol_receive_subscribe_msg(ProtocolManager* protocol, char* msg);

/**
 * @brief hype_pub_sub_protocol_receive_unsubscribe_msg
 * @param protocol
 * @param msg
 * @return
 */
int hype_pub_sub_protocol_receive_unsubscribe_msg(ProtocolManager* protocol, char* msg);

/**
 * @brief hype_pub_sub_protocol_receive_publish_msg
 * @param protocol
 * @param msg
 * @return
 */
int hype_pub_sub_protocol_receive_publish_msg(ProtocolManager* protocol, char* msg);

/**
 * @brief hype_pub_sub_protocol_receive_change_service_manager_msg
 * @param protocol
 * @param msg
 * @return
 */
int hype_pub_sub_protocol_receive_change_service_manager_msg(ProtocolManager* protocol, char* msg);

/**
 * @brief hype_pub_sub_protocol_receive_info_msg
 * @param protocol
 * @param msg
 * @return
 */
int hype_pub_sub_protocol_receive_info_msg(ProtocolManager* protocol, char* msg);

/**
 * @brief hype_pub_sub_protocol_get_message_type
 * @param msg
 * @return
 */
static MessageType hype_pub_sub_protocol_get_message_type(char* msg);

#endif /* HYPE_PUB_SUB_PROTOCOL_H_INCLUDED_ */
