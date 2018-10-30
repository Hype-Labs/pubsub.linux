
#include "hype_pub_sub/hpb_cmd_interface.h"

void hpb_cmd_interface_subscribe(HypePubSub *hpb, char* service_name)
{
    string_utils_to_lower_case(service_name);
    hpb_issue_subscribe_req(service_name);
}

void hpb_cmd_interface_unsubscribe(HypePubSub *hpb, char* service_name)
{
    string_utils_to_lower_case(service_name);
    hpb_issue_unsubscribe_req(service_name);
}

void hpb_cmd_interface_publish(HypePubSub *hpb, char* service_name)
{
    string_utils_to_lower_case(service_name);
    printf("Insert message to be published on the service '%s': ", service_name);
    size_t msg_size = 1000;
    char msg[msg_size];
    fgets(msg, msg_size, stdin);
    msg[strcspn(msg, "\n")] = '\0'; // Remove \n read by fgets()

    hpb_issue_publish_req(service_name, msg, strlen(msg));
}

void hpb_cmd_interface_print_own_id(HypePubSub *hpb)
{
    printf("\n");
    printf("Own Device ID: ");
    binary_utils_print_hex_array(hpb->network->own_client->hype_instance->identifier->data, hpb->network->own_client->hype_instance->identifier->size);
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

    do
    {
        HpbServiceManager *srvc = (HpbServiceManager *) linked_list_iterator_get_element(it);

        if(srvc == NULL) {
            continue;
        }

        printf("Managed Service %i Key: ", srvc_n);
        binary_utils_print_hex_array(srvc->service_key, SHA1_BLOCK_SIZE);
        printf("Managed Service %i Subscribers: ", srvc_n);
        hpb_cmd_interface_print_client_list(srvc->subscribers);
        printf("\n");

        srvc_n++;
    } while(linked_list_iterator_advance(it) != -1);

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

    do
    {
        HpbSubscription *sbscrptn = (HpbSubscription *) linked_list_iterator_get_element(it);

        if(sbscrptn == NULL) {
            continue;
        }

        printf("Subscription %i service name: %s\n", sbscrptn_n, sbscrptn->service_name);
        printf("Subscription %i service key: ", sbscrptn_n);
        binary_utils_print_hex_array(sbscrptn->service_key, SHA1_BLOCK_SIZE);
        printf("Subscription %i manager ID: ", sbscrptn_n);
        binary_utils_print_hex_array(sbscrptn->manager_instance->identifier->data, sbscrptn->manager_instance->identifier->size);
        printf("\n");

        sbscrptn_n++;
    } while(linked_list_iterator_advance(it) != -1);

    linked_list_iterator_destroy(&it);
}

void hpb_cmd_interface_print_helper()
{
    printf("\n");
    printf("The followings options are available:\n");
    printf(" --%-25s : Allows to subscribe a service.\n" ,HPB_CMD_INTERFACE_SUBSCRIBE);
    printf(" --%-25s : Allows to unsubscribe a service.\n" ,HPB_CMD_INTERFACE_UNSUBSCRIBE);
    printf(" --%-25s : Allows to publish a message in a service.\n" ,HPB_CMD_INTERFACE_PUBLISH);
    printf(" --%-25s : Prints the Hype identifier and the key of this device.\n" ,HPB_CMD_INTERFACE_PRINT_OWN_ID);
    printf(" --%-25s : Prints the Hype identifier and the key of the devices found in the network.\n" ,HPB_CMD_INTERFACE_PRINT_HYPE_DEVICES);
    printf(" --%-25s : Prints the services which are managed by this device.\n" ,HPB_CMD_INTERFACE_PRINT_MANAGED_SERVICES);
    printf(" --%-25s : Prints the services subscribed by this device.\n" ,HPB_CMD_INTERFACE_PRINT_SUBSCRIPTIONS);
    printf(" --%-25s : Prints the helper menu of this application.\n" ,HPB_CMD_INTERFACE_HELP);
    printf(" --%-25s : Terminates the application.\n" ,HPB_CMD_INTERFACE_QUIT);
    printf("\n");
}

void hpb_cmd_interface_print_header()
{
    printf("\n");
    printf(" ####################################\n");
    printf(" ##          HypePubSub            ##\n");
    printf(" ####################################\n");
    printf("\n");
}

void hpb_cmd_interface_print_client_list(HpbClientsList *lst_cl)
{
    printf("\n");
    LinkedListIterator *it = linked_list_iterator_create(lst_cl);
    int cl_n = 1;

    do
    {
        HpbClient *client = (HpbClient *) linked_list_iterator_get_element(it);
        if(client == NULL) {
            continue;
        }

        printf("Device %i ID: ", cl_n);
        binary_utils_print_hex_array(client->hype_instance->identifier->data, client->hype_instance->identifier->size);
        printf("Device %i Key: ", cl_n);
        binary_utils_print_hex_array(client->key, SHA1_BLOCK_SIZE);
        printf("\n");

        cl_n++;
    } while(linked_list_iterator_advance(it) != -1);

    linked_list_iterator_destroy(&it);
}

int hpb_cmd_interface_arg_split( char *result[], char *str_to_split, const char *delim)
{
    int count = 0;
    int i=0;
    char *p=NULL;
    for(i=0, result[0]=NULL, p=strtok(str_to_split, delim); p!=NULL; p=strtok(NULL, delim), i++ )
    {
           result[i]=p;
           result[i+1]=NULL;
           count++;
    }
    return count;
}
