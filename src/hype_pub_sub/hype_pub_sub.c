
#include "hype_pub_sub/hype_pub_sub.h"

HypePubSub* hpb_create()
{
    HypePubSub *hpb = (HypePubSub*) malloc(sizeof(HypePubSub));
    hpb->own_subscriptions = hpb_list_subscriptions_create();
    hpb->managed_services = hpb_list_service_managers_create();
    hpb->network = hpb_network_create();
    hpb->protocol = hpb_protocol_create(hpb);
    return hpb;
}

int hpb_issue_subscribe_req(HypePubSub *hpb, byte service_key[])
{
    if(hpb == NULL)
        return -1;

    byte *manager_id = hpb_network_get_service_manager_id(hpb->network, service_key);

    // if this client is the manager of the service we don't need to send the subscribe message to
    // the protocol manager
    if(hpb_client_is_id_equal(hpb->network->own_client->id, manager_id))
        hpb_process_subscribe_req(hpb, service_key, hpb->network->own_client->id);
    else
        hpb_protocol_send_subscribe_msg(service_key, manager_id);

    return 0;
}

int hpb_issue_unsubscribe_req(HypePubSub *hpb, byte service_key[])
{
    if(hpb == NULL)
        return -1;

    byte *manager_id = hpb_network_get_service_manager_id(hpb->network, service_key);

    // if this client is the manager of the service we don't need to send the unsubscribe message
    // to the protocol manager
    if(hpb_client_is_id_equal(hpb->network->own_client->id, manager_id))
        hpb_process_unsubscribe_req(hpb, service_key, hpb->network->own_client->id);
    else
        hpb_protocol_send_unsubscribe_msg(service_key, manager_id);

    return 0;
}

int hpb_issue_publish_req(HypePubSub *hpb, byte service_key[], char *msg, size_t msg_length)
{
    if(hpb == NULL)
        return -1;

    byte *manager_id = hpb_network_get_service_manager_id(hpb->network, service_key);

    // if this client is the manager of the service we don't need to send the publish message
    // to the protocol manager
    if(hpb_client_is_id_equal(hpb->network->own_client->id, manager_id))
        hpb_process_publish_req(hpb, service_key, msg, msg_length);
    else
        hpb_protocol_send_publish_msg(service_key, manager_id, msg, msg_length);

    return 0;
}

int hpb_process_subscribe_req(HypePubSub *hpb, byte service_key[], byte requester_client_id[])
{
    if(hpb == NULL)
        return -1;

    ServiceManager *service = hpb_list_service_managers_find(hpb->managed_services, service_key);

    if(service == NULL) // If the service does not exist we create it.
    {
        service = hpb_list_service_managers_add(hpb->managed_services, service_key);
        if(service == NULL)  // If the service could not be created we exit.
            return -2;
    }

    hpb_list_clients_add(service->subscribers, requester_client_id);

    return 0;
}

int hpb_process_unsubscribe_req(HypePubSub *hpb, byte service_key[], byte requester_client_id[])
{
    if(hpb == NULL)
        return -1;

    ServiceManager *service = hpb_list_service_managers_find(hpb->managed_services, service_key);

    if(service == NULL) // If the service does not exist we ignore the unsubscribe request.
        return -2;

    hpb_list_clients_remove(service->subscribers, requester_client_id);

    if(service->subscribers->size == 0) // Remove the service if there is no subscribers
        hpb_list_service_managers_remove(hpb->managed_services, service_key);

    return 0;
}

int hpb_process_publish_req(HypePubSub *hpb, byte service_key[], char *msg, size_t msg_length)
{
    if(hpb == NULL)
        return -1;

    ServiceManager *service = hpb_list_service_managers_find(hpb->managed_services, service_key);

    if(service == NULL)
        return -1;

    LinkedListIterator *it = linked_list_iterator_create(service->subscribers);
    do
    {
        Client* client = (Client*) linked_list_iterator_get_element(it);
        if(client == NULL)
            continue;

        if(hpb_client_is_id_equal(hpb->network->own_client->id, client->id))
            hpb_process_info_msg(hpb, service_key, msg, msg_length);
        else
            hpb_protocol_send_info_msg(service_key, client->id, msg, msg_length);

    } while(linked_list_iterator_advance(it) != -1);
    linked_list_iterator_destroy(&it);

    return 0;
}

int hpb_process_info_msg(HypePubSub *hpb, byte service_key[], char *msg, size_t msg_length)
{
    if(hpb == NULL)
        return -1;

    Subscription *subs = hpb_list_subscriptions_find(hpb->own_subscriptions, service_key);

    printf("ServiceName:");
    if(subs != NULL)
        printf(" %s \n", subs->service_name);
    else
        printf(" --- \n");

    printf("ServiceKey: 0x"); binary_utils_print_hex_array(service_key, SHA1_BLOCK_SIZE);
    printf("Message: %s", msg);
    return 0;
}

static int hpb_update_managed_services(HypePubSub *hpb)
{
    LinkedListIterator *it = linked_list_iterator_create(hpb->managed_services);
    do
    {
        ServiceManager* service_man = (ServiceManager*) linked_list_iterator_get_element(it);
        if(service_man == NULL)
            continue;

        // Check if a new Hype client with a closer key to this service key has appeared. If this happens
        // we remove the service from the list of managed services of this Hype client.
        byte *new_manager_id = hpb_network_get_service_manager_id(hpb->network, service_man->service_key);
        if(memcmp(hpb->network->own_client->id, new_manager_id, HPB_ID_BYTE_SIZE) != 0)
            hpb_list_service_managers_remove(hpb->managed_services, service_man->service_key);

    } while(linked_list_iterator_advance(it) != -1);

    linked_list_iterator_destroy(&it);
    return 0;
}

static int hpb_update_own_subscriptions(HypePubSub *hpb)
{
    if(hpb == NULL)
        return -1;

    LinkedListIterator *it = linked_list_iterator_create(hpb->own_subscriptions);
    do
    {
        Subscription* subscription = (Subscription*) linked_list_iterator_get_element(it);
        if(subscription == NULL)
            continue;

        byte *new_manager_id = hpb_network_get_service_manager_id(hpb->network, subscription->service_key);

        // If there is a node with a closer key to the service key we change the manager
        if(memcmp(subscription->manager_id, new_manager_id, HPB_ID_BYTE_SIZE) != 0)
        {
            memcpy(subscription->manager_id, new_manager_id, HPB_ID_BYTE_SIZE);
            hpb_issue_subscribe_req(hpb, subscription->service_key); // re-send the subscribe request to the new manager
        }

    } while(linked_list_iterator_advance(it) != -1);

    linked_list_iterator_destroy(&it);

    return 0;
}

void hpb_destroy(HypePubSub **hpb)
{
    if((*hpb) == NULL)
        return;

    hpb_list_subscriptions_destroy(&((*hpb)->own_subscriptions));
    hpb_list_service_managers_destroy(&((*hpb)->managed_services));
    hpb_network_destroy(&((*hpb)->network));
    hpb_protocol_destroy(&((*hpb)->protocol));
    free(*hpb);
    *hpb = NULL;
}
