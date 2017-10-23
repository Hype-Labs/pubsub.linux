
#ifndef HYPE_PUB_SUB_H_INCLUDED_
#define HYPE_PUB_SUB_H_INCLUDED_

#include <stdlib.h>

#include "list_service_managers.h"
#include "list_subscriptions.h"
#include "network.h"
//#include "protocol.h"


/**
 * @brief
 */
typedef struct HypePubSub_
{
    ListSubscriptions* list_subscriptions; /**< List of subscriptions of this client. */
    ListServiceManagers* list_serv_man; /**< List of services managed by this client. */
    Network* network;
    //Protocol* protocol;

} HypePubSub;

HypePubSub* hype_pub_sub_create();

int hype_pub_sub_issue_subscribe_service_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE]);

int hype_pub_sub_issue_unsubscribe_service_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE]);

int hype_pub_sub_issue_publish_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], char* msg);

int hype_pub_sub_process_subscribe_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], byte requester_client_id[HYPE_ID_BYTE_SIZE]);

int hype_pub_sub_process_unsubscribe_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], byte requester_client_id[HYPE_ID_BYTE_SIZE]);

int hype_pub_sub_process_publish_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], char* msg);

int hype_pub_sub_process_change_service_manager_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], byte new_manager_id[HYPE_ID_BYTE_SIZE], byte** subscribers_id[HYPE_ID_BYTE_SIZE]);

static int hype_pub_sub_update_subscriptions(HypePubSub* pub_sub);

static int hype_pub_sub_issue_change_service_manager_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], byte new_manager_id[HYPE_ID_BYTE_SIZE], byte** subscribers_id[HYPE_ID_BYTE_SIZE]);

static int hype_pub_sub_remove_service_manager(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE]);

static int hype_pub_sub_send_info_msg(HypePubSub* pub_sub, byte** dest_network_ids[HYPE_ID_BYTE_SIZE], char* msg);

void hype_pub_sub_destroy(HypePubSub* pub_sub);

#endif /* HYPE_PUB_SUB_H_INCLUDED_ */
