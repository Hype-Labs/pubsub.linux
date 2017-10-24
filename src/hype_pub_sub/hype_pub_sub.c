
#include "hype_pub_sub/hype_pub_sub.h"

HypePubSub* hype_pub_sub_create()
{
    HypePubSub* pub_sub = (HypePubSub*) malloc(sizeof(HypePubSub));
    pub_sub->own_subscriptions = hype_pub_sub_list_subscriptions_create();
    pub_sub->managed_services = hype_pub_sub_list_service_managers_create();
    pub_sub->network = hype_pub_sub_network_create();
    pub_sub->protocol = hype_pub_sub_protocol_create(pub_sub);
    return pub_sub;
}

int hype_pub_sub_issue_subscribe_service_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE])
{
    if(pub_sub == NULL)
        return -1;

    byte *dst = hype_pub_sub_network_get_service_manager_id(pub_sub->network, service_key);
    hype_pub_sub_protocol_send_subscribe_msg(service_key, dst);
    return 0;
}

int hype_pub_sub_issue_unsubscribe_service_req(HypePubSub *pub_sub, byte service_key[SHA1_BLOCK_SIZE])
{
    if(pub_sub == NULL)
        return -1;

    byte *dst = hype_pub_sub_network_get_service_manager_id(pub_sub->network, service_key);
    hype_pub_sub_protocol_send_unsubscribe_msg(service_key, dst);
    return 0;
}

int hype_pub_sub_issue_publish_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], char* msg)
{
    if(pub_sub == NULL)
        return -1;

    byte *dst = hype_pub_sub_network_get_service_manager_id(pub_sub->network, service_key);
    hype_pub_sub_protocol_send_publish_msg(service_key, dst, msg);
    return 0;
}

int hype_pub_sub_process_subscribe_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], byte requester_client_id[HYPE_ID_BYTE_SIZE])
{
    if(pub_sub == NULL)
        return -1;

    ServiceManager *service = hype_pub_sub_list_service_managers_find(pub_sub->managed_services, service_key);

    if(service == NULL) // Add the service if we don't have it yet
        service = hype_pub_sub_list_service_managers_add(pub_sub->managed_services, service_key);

    hype_pub_sub_list_clients_add(service->subscribers, requester_client_id);

    return 0;
}

int hype_pub_sub_process_unsubscribe_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], byte requester_client_id[HYPE_ID_BYTE_SIZE])
{
    if(pub_sub == NULL)
        return -1;

    ServiceManager *service = hype_pub_sub_list_service_managers_find(pub_sub->managed_services, service_key);

    if(service == NULL)
        return -1;

    hype_pub_sub_list_clients_remove(service->subscribers, requester_client_id);

    return 0;
}

int hype_pub_sub_process_publish_req(HypePubSub* pub_sub, byte service_key[SHA1_BLOCK_SIZE], char* msg)
{
    if(pub_sub == NULL)
        return -1;

    ServiceManager *service = hype_pub_sub_list_service_managers_find(pub_sub->managed_services, service_key);

    if(service == NULL)
        return -1;

    LinkedListIterator *it = linked_list_create_iterator(service->subscribers);
    while(linked_list_get_element_data_iterator(it) != NULL)
    {
        Client* client = (Client*) linked_list_get_element_data_iterator(it);
        hype_pub_sub_send_info_msg(pub_sub, client->id, msg);
        linked_list_advance_iterator(it);
    }
    linked_list_destroy_iterator(it);

    return 0;
}

static int hype_pub_sub_update_managed_services(HypePubSub* pub_sub)
{
    LinkedListIterator *it = linked_list_create_iterator(pub_sub->managed_services);
    while(linked_list_get_element_data_iterator(it) != NULL)
    {
        ServiceManager* service_man = (ServiceManager*) linked_list_get_element_data_iterator(it);

        byte *new_manager_id = hype_pub_sub_network_get_service_manager_id(pub_sub->network, service_man->service_key);

        if(memcmp(pub_sub->network->own_client_id, new_manager_id, HYPE_ID_BYTE_SIZE) != 0)
            hype_pub_sub_list_service_managers_remove(pub_sub->managed_services, service_man->service_key); // we are no longer the manager of that service

        linked_list_advance_iterator(it);
    }
    linked_list_destroy_iterator(it);
    return 0;
}

static int hype_pub_sub_update_subscriptions(HypePubSub* pub_sub)
{
    if(pub_sub == NULL)
        return -1;

    LinkedListIterator *it = linked_list_create_iterator(pub_sub->own_subscriptions);
    while(linked_list_get_element_data_iterator(it) != NULL)
    {
        Subscription* subscription = (Subscription*) linked_list_get_element_data_iterator(it);

        byte *new_manager_id = hype_pub_sub_network_get_service_manager_id(pub_sub->network, subscription->service_key);

        // If there is a node with a closer key to the service key we change the manager
        if(memcmp(subscription->manager_id, new_manager_id, HYPE_ID_BYTE_SIZE) != 0)
        {
            memcpy(subscription->manager_id, new_manager_id, HYPE_ID_BYTE_SIZE);
            hype_pub_sub_issue_subscribe_service_req(pub_sub, subscription->service_key); // re-send the subscribe request to the new manager
        }

        linked_list_advance_iterator(it);
    }
    linked_list_destroy_iterator(it);


    return 0;
}

static int hype_pub_sub_send_info_msg(HypePubSub* pub_sub, byte dest[HYPE_ID_BYTE_SIZE], char* msg)
{
    hype_pub_sub_protocol_send_info_msg(pub_sub->protocol, dest, msg);
    return 0;
}

void hype_pub_sub_destroy(HypePubSub *pub_sub)
{
    hype_pub_sub_list_service_managers_destroy(pub_sub->managed_services);
    hype_pub_sub_list_subscriptions_destroy(pub_sub->own_subscriptions);
    hype_pub_sub_network_destroy(pub_sub->network);
    hype_pub_sub_protocol_destroy(pub_sub->protocol);
    free(pub_sub);
}
