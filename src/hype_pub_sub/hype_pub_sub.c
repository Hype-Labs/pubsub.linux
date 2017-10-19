
#include "hype_pub_sub/hype_pub_sub.h"

HypePubSub* hype_pub_sub_create()
{
    return NULL;
}

int hype_pub_sub_issue_subscribe_service_req(char service_key[SHA1_KEY_BYTE_SIZE])
{
    return 0;
}

int hype_pub_sub_issue_unsubscribe_service_req(char service_key[SHA1_KEY_BYTE_SIZE])
{
    return 0;
}

int hype_pub_sub_issue_publish_req(char service_key[SHA1_KEY_BYTE_SIZE], char* msg)
{
    return 0;
}

int hype_pub_sub_process_subscribe_req(char service_key[SHA1_KEY_BYTE_SIZE], char requester_client_id[HYPE_ID_BYTE_SIZE])
{
    return 0;
}

int hype_pub_sub_process_unsubscribe_req(char service_key[SHA1_KEY_BYTE_SIZE], char requester_client_id[HYPE_ID_BYTE_SIZE])
{
    return 0;
}

int hype_pub_sub_process_publish_req(char service_key[SHA1_KEY_BYTE_SIZE], char* msg)
{
    return 0;
}

int hype_pub_sub_process_change_service_manager_req(char service_key[SHA1_KEY_BYTE_SIZE], char new_manager_id[HYPE_ID_BYTE_SIZE], char** subscribers_id[HYPE_ID_BYTE_SIZE])
{
    return 0;
}

static int hype_pub_sub_update_subscriptions_manager()
{
    return 0;
}

static int hype_pub_sub_issue_change_service_manager_req(char service_key[SHA1_KEY_BYTE_SIZE], char new_manager_id[HYPE_ID_BYTE_SIZE], char** subscribers_id[HYPE_ID_BYTE_SIZE])
{
    return 0;
}

static int hype_pub_sub_remove_service_manager(char service_key[SHA1_KEY_BYTE_SIZE])
{
    return 0;
}

static int hype_pub_sub_send_info_msg(char** dest_network_ids[HYPE_ID_BYTE_SIZE])
{
    return 0;
}
