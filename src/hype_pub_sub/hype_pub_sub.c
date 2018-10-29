
#include "hype_pub_sub/hype_pub_sub.h"

HypePubSub* hpb_get()
{
    static HypePubSub *hpb = NULL;

    if(hpb == NULL)
    {
        hpb = (HypePubSub*) malloc(sizeof(HypePubSub));
        hpb->own_subscriptions = hpb_list_subscriptions_create();
        hpb->managed_services = hpb_list_service_managers_create();
        hpb->network = hpb_network_create();
        hpb->protocol = hpb_protocol_create(hpb);
    }

    return hpb;
}

int hpb_issue_subscribe_req(char* service_name)
{
    HypePubSub *hpb = hpb_get();

    HLByte service_key[SHA1_BLOCK_SIZE];
    sha1_digest((const BYTE *) service_name, strlen(service_name), service_key);

    HypeInstance * manager_instance = hpb_network_get_service_manager_id(hpb->network, service_key);

    // Add subscription to the list of own subscriptions
    hpb_list_subscriptions_add(hpb->own_subscriptions, service_name, strlen(service_name), manager_instance);

    // if this client is the manager of the service we don't need to send the subscribe message to
    // the protocol manager
    if(hpb_client_is_instance_equal(hpb->network->own_client, manager_instance)) {
        hpb_process_subscribe_req(service_key, hpb->network->own_client->hype_instance);
    }
    else {
        hpb_protocol_send_subscribe_msg(service_key, manager_instance);
    }

    return 0;
}

int hpb_issue_unsubscribe_req(char *service_name)
{
    HypePubSub *hpb = hpb_get();

    HLByte service_key[SHA1_BLOCK_SIZE];
    sha1_digest((const BYTE *) service_name, strlen(service_name), service_key);

    HypeInstance * manager_instance = hpb_network_get_service_manager_id(hpb->network, service_key);

    if(hpb_list_subscriptions_find(hpb->own_subscriptions, service_key) == NULL)
    {
        printf("Trying to unsubscribe a service that was not previously subscribed: %s.\n", service_name);
        return -2;
    }

    // Remove the subscription from the list of own subscriptions
    hpb_list_subscriptions_remove(hpb->own_subscriptions, service_key);

    // if this client is the manager of the service we don't need to send the unsubscribe message
    // to the protocol manager
    if(hpb_client_is_instance_equal(hpb->network->own_client, manager_instance)) {
        hpb_process_unsubscribe_req(service_key, hpb->network->own_client->hype_instance);
    }
    else {
        hpb_protocol_send_unsubscribe_msg(service_key, manager_instance);
    }

    return 0;
}

int hpb_issue_publish_req(char *service_name, char *msg, size_t msg_length)
{
    HypePubSub *hpb = hpb_get();

    HLByte service_key[SHA1_BLOCK_SIZE];
    sha1_digest((const BYTE *) service_name, strlen(service_name), service_key);

    HypeInstance * manager_instance = hpb_network_get_service_manager_id(hpb->network, service_key);

    // if this client is the manager of the service we don't need to send the publish message
    // to the protocol manager
    if(hpb_client_is_instance_equal(hpb->network->own_client, manager_instance)) {
        hpb_process_publish_req(service_key, msg, msg_length);
    }
    else {
        hpb_protocol_send_publish_msg(service_key, manager_instance, msg, msg_length);
    }

    return 0;
}

int hpb_process_subscribe_req(HLByte service_key[], HypeInstance * instance_origin)
{
    HypePubSub *hpb = hpb_get();

    HpbServiceManager *service = hpb_list_service_managers_find(hpb->managed_services, service_key);

    if(service == NULL) // If the service does not exist we create it.
    {
        service = hpb_list_service_managers_add(hpb->managed_services, service_key);
        if(service == NULL) { // If the service could not be created we exit.
            return -2;
        }
    }

    hpb_list_clients_add(service->subscribers, instance_origin);

    return 0;
}

int hpb_process_unsubscribe_req(HLByte service_key[], HypeInstance * instance_origin)
{
    HypePubSub *hpb = hpb_get();

    HpbServiceManager *service = hpb_list_service_managers_find(hpb->managed_services, service_key);

    if(service == NULL) { // If the service does not exist we ignore the unsubscribe request.
        return -2;
    }

    hpb_list_clients_remove(service->subscribers, instance_origin);

    if(service->subscribers->size == 0) { // Remove the service if there is no subscribers
        hpb_list_service_managers_remove(hpb->managed_services, service_key);
    }

    return 0;
}

int hpb_process_publish_req(HLByte service_key[], char *msg, size_t msg_length)
{
    HypePubSub *hpb = hpb_get();

    HpbServiceManager *service = hpb_list_service_managers_find(hpb->managed_services, service_key);

    if(service == NULL) {
        return -2;
    }

    LinkedListIterator *it = linked_list_iterator_create(service->subscribers);
    do
    {
        HpbClient* client = (HpbClient*) linked_list_iterator_get_element(it);
        if(client == NULL) {
            continue;
        }

        if(hpb_client_is_instance_equal(hpb->network->own_client, client->hype_instance)) {
            hpb_process_info_msg(service_key, msg, msg_length);
        }
        else {
            hpb_protocol_send_info_msg(service_key, client->hype_instance, msg, msg_length);
        }

    } while(linked_list_iterator_advance(it) != -1);
    linked_list_iterator_destroy(&it);

    return 0;
}

int hpb_process_info_msg(HLByte service_key[], char *msg, size_t msg_length)
{
    HypePubSub *hpb = hpb_get();

    HpbSubscription *subs = hpb_list_subscriptions_find(hpb->own_subscriptions, service_key);

    if(subs == NULL){
        printf("Received message from an unsubscribed service: %s\n\n", msg);
        return -1;
    }

    printf("\n### Message Received! ###\n");
    printf("ServiceName: %s \n", subs->service_name);

    printf("ServiceKey: 0x"); binary_utils_print_hex_array(service_key, SHA1_BLOCK_SIZE);
    printf("Message: %s\n\n", msg);
    return 0;
}

int hpb_update_managed_services()
{
    HypePubSub *hpb = hpb_get();

    LinkedListIterator *it = linked_list_iterator_create(hpb->managed_services);
    do
    {
        HpbServiceManager* service_man = (HpbServiceManager*) linked_list_iterator_get_element(it);
        if(service_man == NULL) {
            continue;
        }

        // Check if a new Hype client with a closer key to this service key has appeared. If this happens
        // we remove the service from the list of managed services of this Hype client.
        HypeInstance *new_manager_instance = hpb_network_get_service_manager_id(hpb->network, service_man->service_key);
        if(memcmp(hpb->network->own_client->hype_instance, new_manager_instance, new_manager_instance->identifier->size) != 0) {
            hpb_list_service_managers_remove(hpb->managed_services, service_man->service_key);
        }

    } while(linked_list_iterator_advance(it) != -1);

    linked_list_iterator_destroy(&it);
    return 0;
}

int hpb_update_own_subscriptions()
{
    HypePubSub *hpb = hpb_get();

    LinkedListIterator *it = linked_list_iterator_create(hpb->own_subscriptions);
    do
    {
        HpbSubscription* subscription = (HpbSubscription*) linked_list_iterator_get_element(it);
        if(subscription == NULL) {
            continue;
        }

        HypeInstance *new_manager_instance = hpb_network_get_service_manager_id(hpb->network, subscription->service_key);

        // If there is a node with a closer key to the service key we change the manager
        if(memcmp(subscription->manager_instance, new_manager_instance, new_manager_instance->identifier->size) != 0)
        {
            memcpy(subscription->manager_instance, new_manager_instance, new_manager_instance->identifier->size);
            hpb_issue_subscribe_req(subscription->service_name); // re-send the subscribe request to the new manager
        }

    } while(linked_list_iterator_advance(it) != -1);

    linked_list_iterator_destroy(&it);

    return 0;
}

void hpb_destroy(HypePubSub **hpb)
{
    if((*hpb) == NULL) {
        return;
    }

    hpb_list_subscriptions_destroy(&((*hpb)->own_subscriptions));
    hpb_list_service_managers_destroy(&((*hpb)->managed_services));
    hpb_network_destroy(&((*hpb)->network));
    hpb_protocol_destroy(&((*hpb)->protocol));
    free(*hpb);
    *hpb = NULL;
}
