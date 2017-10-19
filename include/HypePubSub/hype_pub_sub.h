
#ifndef HYPE_PUB_SUB_H_INCLUDED_
#define HYPE_PUB_SUB_H_INCLUDED_

#include <stdlib.h>

#include "service_manager.h"
#include "subscription.h"

/**
 * @brief
 */
typedef struct HypePubSub_
{
    Subscription* subscriptions; /**< Subscriptions of this client. */
    ServiceManager* managed_services; /**< Services managed by this client*/
} HypePubSub;

/**
 * @brief hype_pub_sub_create
 * @return
 */
HypePubSub* hype_pub_sub_create();

/**
 * @brief hype_pub_sub_issue_subscribe_service_req
 * @param service_key
 * @return
 */
int hype_pub_sub_issue_subscribe_service_req(char service_key[SHA1_KEY_BYTE_SIZE]);

/**
 * @brief hype_pub_sub_issue_unsubscribe_service_req
 * @param service_key
 * @return
 */
int hype_pub_sub_issue_unsubscribe_service_req(char service_key[SHA1_KEY_BYTE_SIZE]);

/**
 * @brief hype_pub_sub_issue_publish_req
 * @param service_key
 * @param msg
 * @return
 */
int hype_pub_sub_issue_publish_req(char service_key[SHA1_KEY_BYTE_SIZE], char* msg);

/**
 * @brief hype_pub_sub_process_subscribe_req
 * @param service_key
 * @param requester_client_id
 * @return
 */
int hype_pub_sub_process_subscribe_req(char service_key[SHA1_KEY_BYTE_SIZE], char requester_client_id[HYPE_ID_BYTE_SIZE]);

/**
 * @brief hype_pub_sub_process_unsubscribe_req
 * @param service_key
 * @param requester_client_id
 * @return
 */
int hype_pub_sub_process_unsubscribe_req(char service_key[SHA1_KEY_BYTE_SIZE], char requester_client_id[HYPE_ID_BYTE_SIZE]);

/**
 * @brief hype_pub_sub_process_publish_req
 * @param service_key
 * @param msg
 * @return
 */
int hype_pub_sub_process_publish_req(char service_key[SHA1_KEY_BYTE_SIZE], char* msg);

/**
 * @brief hype_pub_sub_process_change_service_manager_req
 * @param service_key
 * @param new_manager_id
 * @param subscribers_id
 * @return
 */
int hype_pub_sub_process_change_service_manager_req(char service_key[SHA1_KEY_BYTE_SIZE], char new_manager_id[HYPE_ID_BYTE_SIZE], char** subscribers_id[HYPE_ID_BYTE_SIZE]);

/**
 * @brief hype_pub_sub_update_subscriptions_manager
 * @return
 */
static int hype_pub_sub_update_subscriptions_manager();

/**
 * @brief hype_pub_sub_issue_change_service_manager_req
 * @param service_key
 * @param new_manager_id
 * @param subscribers_id
 * @return
 */
static int hype_pub_sub_issue_change_service_manager_req(char service_key[SHA1_KEY_BYTE_SIZE], char new_manager_id[HYPE_ID_BYTE_SIZE], char** subscribers_id[HYPE_ID_BYTE_SIZE]);

/**
 * @brief hype_pub_sub_remove_service_manager
 * @param service_key
 * @return
 */
static int hype_pub_sub_remove_service_manager(char service_key[SHA1_KEY_BYTE_SIZE]);

/**
 * @brief hype_pub_sub_send_info_msg
 * @param dest_network_ids
 * @return
 */
static int hype_pub_sub_send_info_msg(char** dest_network_ids[HYPE_ID_BYTE_SIZE]);

#endif /* HYPE_PUB_SUB_H_INCLUDED_ */
