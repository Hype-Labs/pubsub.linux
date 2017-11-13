
#include "hype_pub_sub/cmd_interface.h"

void hpb_cmd_interface_subscribe(HypePubSub *hpb, char* input)
{
    //char ** args;
    //cmd_args_process_args(input, strlen(input),args);
    // hpb_issue_subscribe_req(hpb, service_key);
}

void hpb_cmd_interface_unsubscribe(HypePubSub *hpb)
{
    // hpb_issue_unsubscribe_req(hpb, service_key);
}

void hpb_cmd_interface_publish(HypePubSub *hpb)
{
    // hpb_issue_publish_req(hpb, service_key, msg, msg_length);
}

void hpb_cmd_interface_print_own_id(HypePubSub *hpb)
{
    printf("\n");
    printf("Own Device ID: ");
    binary_utils_print_hex_array(hpb->network->own_client->id, HPB_ID_BYTE_SIZE);
    printf("Own Device Key: ");
    binary_utils_print_hex_array(hpb->network->own_client->key, SHA1_BLOCK_SIZE);
    printf("\n");
}

void hpb_cmd_interface_print_hype_devices(HypePubSub *hpb)
{
    if(hpb->network->network_clients->size == 0){
        printf("No Hype devices found\n");
        return;
    }
    hpb_cmd_interface_print_client_list(hpb->network->network_clients);
}

void hpb_cmd_interface_print_managed_services(HypePubSub *hpb)
{
    if(hpb->managed_services->size == 0){
        printf("No services are managed by this device\n");
        return;
    }
    else{
        printf("\n");
    }

    LinkedListIterator *it = linked_list_iterator_create(hpb->managed_services);
    int srvc_n = 1;

    while(true)
    {
        ServiceManager *srvc = (ServiceManager *) linked_list_iterator_get_element(it);

        if(srvc == NULL)
            break;

        printf("Managed Service %i Key: ", srvc_n);
        binary_utils_print_hex_array(srvc->service_key, SHA1_BLOCK_SIZE);
        printf("Managed Service %i Subscribers: ", srvc_n);
        hpb_cmd_interface_print_client_list(srvc->subscribers);
        printf("\n");

        srvc_n++;
        linked_list_iterator_advance(it);
    }

    linked_list_iterator_destroy(&it);
}

void hpb_cmd_interface_print_subscriptions(HypePubSub *hpb)
{
    if(hpb->own_subscriptions->size == 0){
        printf("This device has no subscriptions\n");
        return;
    }
    else{
        printf("\n");
    }

    LinkedListIterator *it = linked_list_iterator_create(hpb->own_subscriptions);
    int sbscrptn_n = 1;

    while(true)
    {
        Subscription *sbscrptn = (Subscription *) linked_list_iterator_get_element(it);

        if(sbscrptn == NULL)
            break;

        printf("Subscription %i service name: %s\n", sbscrptn_n, sbscrptn->service_name);
        printf("Subscription %i service key: ", sbscrptn_n);
        binary_utils_print_hex_array(sbscrptn->service_key, SHA1_BLOCK_SIZE);
        printf("Subscription %i manager ID: ", sbscrptn_n);
        binary_utils_print_hex_array(sbscrptn->manager_id, HPB_ID_BYTE_SIZE);
        printf("\n");

        sbscrptn_n++;
        linked_list_iterator_advance(it);
    }

    linked_list_iterator_destroy(&it);
}

void hpb_cmd_interface_print_helper()
{
    printf("The followings options are available:\n");
    printf("\t -> %-20s : Allows to subscribe a service.\n" ,HPB_CMD_INTERFACE_SUBSCRIBE);
    printf("\t -> %-20s : Allows to unsubscribe a service.\n" ,HPB_CMD_INTERFACE_UNSUBSCRIBE);
    printf("\t -> %-20s : Allows to publish a message in a service.\n" ,HPB_CMD_INTERFACE_PUBLISH);
    printf("\t -> %-20s : Prints the Hype ID and the key of this device.\n" ,HPB_CMD_INTERFACE_PRINT_OWN_ID);
    printf("\t -> %-20s : Prints the Hype ID and the key of the known network devices.\n" ,HPB_CMD_INTERFACE_PRINT_HYPE_DEVICES);
    printf("\t -> %-20s : Prints the services which are responsibility of this device.\n" ,HPB_CMD_INTERFACE_PRINT_MANAGED_SERVICES);
    printf("\t -> %-20s : Prints the services subscribed by this device.\n" ,HPB_CMD_INTERFACE_PRINT_SUBSCRIPTIONS);
    printf("\t -> %-20s : Prints the helper menu of this application.\n" ,HPB_CMD_INTERFACE_HELP);
    printf("\t -> %-20s : Terminates the application.\n" ,HPB_CMD_INTERFACE_QUIT);
}

void hpb_cmd_interface_print_invalid_option()
{
    printf("Invalid option.\n");
}

void hpb_cmd_interface_print_header()
{
    printf("\n");
    printf(" ####################################\n");
    printf(" ##          HypePubSub            ##\n");
    printf(" ####################################\n");
    printf("\n");
}

void hpb_cmd_interface_print_client_list(ListClients *lst_cl)
{
    printf("\n");
    LinkedListIterator *it = linked_list_iterator_create(lst_cl);
    int cl_n = 1;

    while(true)
    {
        Client *client = (Client *) linked_list_iterator_get_element(it);
        if(client == NULL)
            break;

        printf("Device %i ID: ", cl_n);
        binary_utils_print_hex_array(client->id, HPB_ID_BYTE_SIZE);
        printf("Device %i Key: ", cl_n);
        binary_utils_print_hex_array(client->key, SHA1_BLOCK_SIZE);
        printf("\n");

        cl_n++;
        linked_list_iterator_advance(it);
    }

    linked_list_iterator_destroy(&it);
}
