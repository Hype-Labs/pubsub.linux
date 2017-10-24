
#include "hype_pub_sub/hype_pub_sub.h"

HypePubSub* hype_pub_sub_create()
{
    HypePubSub* pub_sub = (HypePubSub*) malloc(sizeof(HypePubSub));
    pub_sub->list_subscriptions = hype_pub_sub_list_subscriptions_create();
    pub_sub->list_serv_man = hype_pub_sub_list_service_managers_create();
    pub_sub->network = hype_pub_sub_network_create();
    pub_sub->protocol = hype_pub_sub_protocol_create(pub_sub);
    return pub_sub;
}

int hype_pub_sub_issue_subscribe_service_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE])
{
    byte *dst = hype_pub_sub_network_get_service_manager_id(pub_sub->network, service_key);
    hype_pub_sub_protocol_send_subscribe_msg(service_key, dst);
    return 0;
}

int hype_pub_sub_issue_unsubscribe_service_req(HypePubSub *pub_sub, byte service_key[SHA1_BLOCK_SIZE])
{
    byte *dst = hype_pub_sub_network_get_service_manager_id(pub_sub->network, service_key);
    hype_pub_sub_protocol_send_unsubscribe_msg(service_key, dst);
    return 0;
}

int hype_pub_sub_issue_publish_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], char* msg)
{
    byte *dst = hype_pub_sub_network_get_service_manager_id(pub_sub->network, service_key);
    hype_pub_sub_protocol_send_publish_msg(service_key, dst, msg);
    return 0;
}

int hype_pub_sub_process_subscribe_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], byte requester_client_id[HYPE_ID_BYTE_SIZE])
{
    ServiceManager *service = hype_pub_sub_list_service_managers_find(pub_sub->list_serv_man, service_key);

    if(service == NULL)
        return -1;

    hype_pub_sub_list_clients_add(service->subscribers, requester_client_id);

    return 0;
}

int hype_pub_sub_process_unsubscribe_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], byte requester_client_id[HYPE_ID_BYTE_SIZE])
{
    ServiceManager *service = hype_pub_sub_list_service_managers_find(pub_sub->list_serv_man, service_key);

    if(service == NULL)
        return -1;

    hype_pub_sub_list_clients_remove(&(service->subscribers), requester_client_id);

    return 0;
}

int hype_pub_sub_process_publish_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], char* msg)
{
    ServiceManager *service = hype_pub_sub_list_service_managers_find(pub_sub->list_serv_man, service_key);

    if(service == NULL)
    {
        hype_pub_sub_add_service_manager(pub_sub, service_key);
        return -1; // Service manager created now. No subscribers.
    }

    LinkedListElement *clientsIterator = service->subscribers;

    while(true)
    {
        Client* client = hype_pub_sub_list_clients_iterator(&clientsIterator);

        if (client == NULL)
            break;

        hype_pub_sub_send_info_msg(pub_sub, client->client_id, msg);
    }
    return 0;
}

int hype_pub_sub_process_change_service_manager_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], byte new_manager_id[HYPE_ID_BYTE_SIZE], byte** subscribers_id[HYPE_ID_BYTE_SIZE])
{
    return 0;
}

static int hype_pub_sub_update_subscriptions_manager(HypePubSub* pub_sub)
{
    return 0;
}

static int hype_pub_sub_issue_change_service_manager_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], byte new_manager_id[HYPE_ID_BYTE_SIZE], byte** subscribers_id[HYPE_ID_BYTE_SIZE])
{
    return 0;
}

static int hype_pub_sub_add_service_manager(HypePubSub *pub_sub, byte service_key[SHA1_BLOCK_SIZE])
{
    hype_pub_sub_list_service_managers_add(pub_sub->list_serv_man, service_key);
    return 0;
}

static int hype_pub_sub_remove_service_manager(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE])
{
    hype_pub_sub_list_service_managers_remove(&(pub_sub->list_serv_man), service_key);
    return 0;
}

static int hype_pub_sub_send_info_msg(HypePubSub* pub_sub, byte dest[HYPE_ID_BYTE_SIZE], char* msg)
{
    hype_pub_sub_protocol_send_info_msg(pub_sub->protocol, dest, msg);
    return 0;
}

void hype_pub_sub_destroy(HypePubSub *pub_sub)
{
    hype_pub_sub_list_service_managers_destroy(pub_sub->list_serv_man);
    hype_pub_sub_list_subscriptions_destroy(pub_sub->list_subscriptions);
    hype_pub_sub_network_destroy(pub_sub->network);
    hype_pub_sub_protocol_destroy(pub_sub->protocol);
    free(pub_sub);
}
