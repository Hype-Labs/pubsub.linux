
#ifndef HYPE_PUB_SUB_PROTOCOL_MANAGER_H_INCLUDED_
#define HYPE_PUB_SUB_PROTOCOL_MANAGER_H_INCLUDED_

#include "HypePubSub/constants.h"
#include "HypePubSub/hype_pub_sub.h"

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
 * @brief hype_pub_sub_protocol_manager_create
 * @param pub_sub
 * @return
 */
ProtocolManager* hype_pub_sub_protocol_manager_create(HypePubSub* pub_sub);

/**
 * @brief hype_pub_sub_protocol_manager_send_subscribe_packet
 * @param service_key
 * @param dest_network_id
 * @return
 */
int hype_pub_sub_protocol_manager_send_subscribe_packet(char service_key[SHA1_KEY_BYTE_SIZE], char dest_network_id[HYPE_ID_BYTE_SIZE]);

/**
 * @brief hype_pub_sub_protocol_manager_send_unsubscribe_packet
 * @param service_key
 * @param dest_network_id
 * @return
 */
int hype_pub_sub_protocol_manager_send_unsubscribe_packet(char service_key[SHA1_KEY_BYTE_SIZE], char dest_network_id[HYPE_ID_BYTE_SIZE]);

/**
 * @brief hype_pub_sub_protocol_manager_send_publish_packet
 * @param service_key
 * @param dest_network_id
 * @param msg
 * @return
 */
int hype_pub_sub_protocol_manager_send_publish_packet(char service_key[SHA1_KEY_BYTE_SIZE], char dest_network_id[HYPE_ID_BYTE_SIZE], char* msg);

/**
 * @brief hype_pub_sub_protocol_manager_send_change_service_manager_packet
 * @param service_key
 * @param dest_network_id
 * @param subscribers_ids
 * @return
 */
int hype_pub_sub_protocol_manager_send_change_service_manager_packet(char service_key[SHA1_KEY_BYTE_SIZE], char dest_network_id[HYPE_ID_BYTE_SIZE], char** subscribers_ids[SHA1_KEY_BYTE_SIZE]);

/**
 * @brief hype_pub_sub_protocol_manager_send_info_packet
 * @param protocol
 * @param dest_network_id
 * @param string
 * @return
 */
int hype_pub_sub_protocol_manager_send_info_packet(ProtocolManager* protocol, char dest_network_id[HYPE_ID_BYTE_SIZE], char* string);

/**
 * @brief hype_pub_sub_protocol_manager_receive_msg
 * @param protocol
 * @param origin_network_id
 * @return
 */
int hype_pub_sub_protocol_manager_receive_msg(ProtocolManager* protocol, char origin_network_id[HYPE_ID_BYTE_SIZE]);

/**
 * @brief hype_pub_sub_protocol_manager_receive_subscribe_packet
 * @param protocol
 * @param msg
 * @return
 */
int hype_pub_sub_protocol_manager_receive_subscribe_packet(ProtocolManager* protocol, char* msg);

/**
 * @brief hype_pub_sub_protocol_manager_receive_unsubscribe_packet
 * @param protocol
 * @param msg
 * @return
 */
int hype_pub_sub_protocol_manager_receive_unsubscribe_packet(ProtocolManager* protocol, char* msg);

/**
 * @brief hype_pub_sub_protocol_manager_receive_publish_packet
 * @param protocol
 * @param msg
 * @return
 */
int hype_pub_sub_protocol_manager_receive_publish_packet(ProtocolManager* protocol, char* msg);

/**
 * @brief hype_pub_sub_protocol_manager_receive_change_service_manager_packet
 * @param protocol
 * @param msg
 * @return
 */
int hype_pub_sub_protocol_manager_receive_change_service_manager_packet(ProtocolManager* protocol, char* msg);

/**
 * @brief hype_pub_sub_protocol_manager_receive_info_packet
 * @param protocol
 * @param msg
 * @return
 */
int hype_pub_sub_protocol_manager_receive_info_packet(ProtocolManager* protocol, char* msg);

/**
 * @brief hype_pub_sub_protocol_manager_get_message_type
 * @param msg
 * @return
 */
static MessageType hype_pub_sub_protocol_manager_get_message_type(char* msg);

#endif /* HYPE_PUB_SUB_PROTOCOL_MANAGER_H_INCLUDED_ */
