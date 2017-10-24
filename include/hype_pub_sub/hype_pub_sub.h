
#ifndef HYPE_PUB_SUB_H_INCLUDED_
#define HYPE_PUB_SUB_H_INCLUDED_

#include <stdlib.h>

#include "list_service_managers.h"
#include "list_subscriptions.h"
#include "network.h"
#include "protocol.h"

typedef struct Protocol_ Protocol; // Forward declaration due to circular dependency

typedef struct HypePubSub_
{
    ListSubscriptions *own_subscriptions; /**< List of subscriptions of this client. */
    ListServiceManagers *managed_services; /**< List of services managed by this client. */
    Network *network;
    Protocol *protocol;

} HypePubSub;

HypePubSub* hype_pub_sub_create();

int hype_pub_sub_issue_subscribe_service_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE]);

int hype_pub_sub_issue_unsubscribe_service_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE]);

int hype_pub_sub_issue_publish_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], char* msg);

int hype_pub_sub_process_subscribe_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], byte requester_client_id[HYPE_ID_BYTE_SIZE]);

int hype_pub_sub_process_unsubscribe_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], byte requester_client_id[HYPE_ID_BYTE_SIZE]);

int hype_pub_sub_process_publish_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], char* msg);

static int hype_pub_sub_update_managed_services(HypePubSub* pub_sub);

static int hype_pub_sub_update_subscriptions(HypePubSub* pub_sub);

static int hype_pub_sub_send_info_msg(HypePubSub* pub_sub, byte dest[], char* msg);

void hype_pub_sub_destroy(HypePubSub* pub_sub);

// TODO: Review this later. Currently it seems that these methods are replaced by the hype_pub_sub_update_subscriptions() and hype_pub_sub_update_managed_services() methods
// int hype_pub_sub_process_change_service_manager_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], byte new_manager_id[HYPE_ID_BYTE_SIZE], byte** subscribers_id[HYPE_ID_BYTE_SIZE]);
// static int hype_pub_sub_issue_change_service_manager_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], byte new_manager_id[HYPE_ID_BYTE_SIZE], byte** subscribers_id[HYPE_ID_BYTE_SIZE]);

#endif /* HYPE_PUB_SUB_H_INCLUDED_ */
