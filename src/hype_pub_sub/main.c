#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "hype_pub_sub/hype_pub_sub.h"
#include "../external/include/sha/sha1.h"

void test_hash();
void test_binary_utils();
void test_message_construction();
void test_subscribers_list();
void test_service_manager();
void test_hype_pub_sub();

void print_hex_char_array(unsigned char* array, size_t len);
void print_clients_list(ListClients* head);
void print_subscription_list(ListSubscriptions* head);
void print_service_manager_list(ListServiceManagers* head);

byte EXAMPLE_ID1[] = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11\x12";
byte EXAMPLE_ID2[] = "\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11";
byte EXAMPLE_ID3[] = "\x11\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10";
byte EXAMPLE_ID4[] = "\x10\x11\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09";

int main()
{
    test_hash();

    test_message_construction();

    test_subscribers_list();

    printf("\n------------------------\n");
    printf("------------------------\n");
    printf("------------------------\n");

    test_service_manager();

    printf("\n------------------------\n");
    printf("------------------------\n");
    printf("------------------------\n");

    test_hype_pub_sub();

    test_binary_utils();

    return 0;
}

void test_hash()
{
    char service[] = {"HypeCoffe"};
    unsigned char service_key[SHA1_BLOCK_SIZE];

    sha1_digest((const BYTE*) service, strlen(service), service_key);
    print_hex_char_array(service_key, SHA1_BLOCK_SIZE);
}

void test_message_construction()
{
    char serv1[] = {"HypeCoffe"};
    byte servKey1[SHA1_BLOCK_SIZE];
    sha1_digest((const byte*) serv1, strlen(serv1), servKey1);

    char msg1[] = {"HelloWorld"};
    char msg2[] = {"HelloWorlda"};

    HypePubSub* myPubSubApp = hpb_create();

    hpb_protocol_send_subscribe_msg(servKey1,EXAMPLE_ID1);
    hpb_protocol_send_unsubscribe_msg(servKey1,EXAMPLE_ID1);
    hpb_protocol_send_publish_msg(servKey1,EXAMPLE_ID1, msg1, strlen(msg1));
    hpb_protocol_send_info_msg(servKey1,EXAMPLE_ID1, msg2, strlen(msg2));

    hpb_destroy(&myPubSubApp);
}

void test_subscribers_list()
{
    ListClients* subscribers = hpb_list_clients_create();

    printf("\nAdding id1, id2, id3, id4\n");
    hpb_list_clients_add(subscribers, EXAMPLE_ID1);
    hpb_list_clients_add(subscribers, EXAMPLE_ID2);
    hpb_list_clients_add(subscribers, EXAMPLE_ID3);
    hpb_list_clients_add(subscribers, EXAMPLE_ID4);
    print_clients_list(subscribers);

    printf("\nRemoving id3\n");
    hpb_list_clients_remove(subscribers, EXAMPLE_ID3);
    print_clients_list(subscribers);

    printf("\nRemoving id3 again\n");
    hpb_list_clients_remove(subscribers, EXAMPLE_ID3);
    print_clients_list(subscribers);

    printf("\nRemoving id4\n");
    hpb_list_clients_remove(subscribers, EXAMPLE_ID4);
    print_clients_list(subscribers);

    printf("\nRemoving id1\n");
    hpb_list_clients_remove(subscribers, EXAMPLE_ID1);
    print_clients_list(subscribers);

    printf("\nRemoving id2\n");
    hpb_list_clients_remove(subscribers, EXAMPLE_ID2);
    print_clients_list(subscribers);

    printf("\nAdding id4\n");
    hpb_list_clients_add(subscribers, EXAMPLE_ID4);
    print_clients_list(subscribers);

    printf("\nAdding id1, id2, id3, id4\n");
    hpb_list_clients_add(subscribers, EXAMPLE_ID1);
    hpb_list_clients_add(subscribers, EXAMPLE_ID2);
    hpb_list_clients_add(subscribers, EXAMPLE_ID3);
    hpb_list_clients_add(subscribers, EXAMPLE_ID4);
    print_clients_list(subscribers);

    hpb_list_clients_destroy(&subscribers);
}

void test_service_manager()
{
    char serv1[] = {"HypeCoffe"};
    char serv2[] = {"HypeFruit"};
    char serv3[] = {"HypeDrinks"};
    char serv4[] = {"HypeFood"};
    byte servKey1[SHA1_BLOCK_SIZE];
    byte servKey2[SHA1_BLOCK_SIZE];
    byte servKey3[SHA1_BLOCK_SIZE];
    byte servKey4[SHA1_BLOCK_SIZE];

    sha1_digest((const byte*) serv1, strlen(serv1), servKey1);
    sha1_digest((const byte*) serv2, strlen(serv2), servKey2);
    sha1_digest((const byte*) serv3, strlen(serv3), servKey3);
    sha1_digest((const byte*) serv4, strlen(serv4), servKey4);

    HypePubSub* myPubSubApp = hpb_create();

    printf("\nAdding serv1\n");
    hpb_list_service_managers_add(myPubSubApp->managed_services,servKey1);
    print_service_manager_list(myPubSubApp->managed_services);

    printf("\nRemoving serv1\n");
    hpb_list_service_managers_remove(myPubSubApp->managed_services,servKey1);
    print_service_manager_list(myPubSubApp->managed_services);

    printf("\nAdding serv2, serv1\n");
    hpb_list_service_managers_add(myPubSubApp->managed_services,servKey2);
    hpb_list_service_managers_add(myPubSubApp->managed_services,servKey1);
    print_service_manager_list(myPubSubApp->managed_services);

    hpb_destroy(&myPubSubApp);
}

void test_hype_pub_sub()
{
    HypePubSub* myPubSubApp = hpb_create();

    char serv1[] = {"HypeCoffe"};
    char serv2[] = {"HypeFruit"};
    char serv3[] = {"HypeDrinks"};
    char serv4[] = {"HypeFood"};
    byte serv1ManId[] = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11\x12";
    byte serv2ManId[] = "\x02\x01\x03\x04\x05\x06\x07\x08\x09\x10\x11\x12";
    byte serv3ManId[] = "\x03\x01\x02\x04\x05\x06\x07\x08\x09\x10\x11\x12";
    byte serv4ManId[] = "\x04\x01\x02\x03\x05\x06\x07\x08\x09\x10\x11\x12";

    hpb_list_subscriptions_add(myPubSubApp->own_subscriptions, serv1, strlen(serv1), serv1ManId);
    print_subscription_list(myPubSubApp->own_subscriptions);

    hpb_list_subscriptions_add(myPubSubApp->own_subscriptions, serv2, strlen(serv2), serv2ManId);
    hpb_list_subscriptions_add(myPubSubApp->own_subscriptions, serv3, strlen(serv3), serv3ManId);
    print_subscription_list(myPubSubApp->own_subscriptions);

    hpb_list_subscriptions_add(myPubSubApp->own_subscriptions, serv4, strlen(serv4), serv4ManId);
    print_subscription_list(myPubSubApp->own_subscriptions);

    hpb_list_subscriptions_remove(myPubSubApp->own_subscriptions, serv3, strlen(serv3), serv3ManId);
    print_subscription_list(myPubSubApp->own_subscriptions);

    hpb_destroy(&myPubSubApp);
}

void print_hex_char_array(unsigned char* array, size_t len)
{
    for(int i=0; i<len; i++)
        printf("%.2x", array[i]);

    printf("\n");
}

void print_clients_list(ListClients* clientList)
{
    printf("ClientList (size %zu): \n", clientList->size);

    LinkedListIterator *it = linked_list_iterator_create(clientList);
    do
    {
        Client* client = (Client*) linked_list_iterator_get_element(it);
        if(client == NULL)
            continue;

        print_hex_char_array(client->id, HPB_ID_BYTE_SIZE);
    } while(linked_list_iterator_advance(it) != -1);

    linked_list_iterator_destroy(&it);
}

void print_subscription_list(ListSubscriptions* subsList)
{
    printf("\nSubscriptionsList (size %zu): \n", subsList->size);

    int i=1;
    LinkedListIterator *it = linked_list_iterator_create(subsList);
    do
    {
        Subscription* subs = (Subscription*) linked_list_iterator_get_element(it);
        if(subs == NULL)
            continue;

        printf("Subscription %i\n",i); i++;
        printf("\tManagerId:  "); print_hex_char_array(subs->manager_id, HPB_ID_BYTE_SIZE);
        printf("\tServiceKey:  "); print_hex_char_array(subs->service_key, SHA1_BLOCK_SIZE);
        printf("\tServiceName:  %s\n", subs->service_name);
        linked_list_iterator_advance(it);
    } while(linked_list_iterator_advance(it) != -1);
    linked_list_iterator_destroy(&it);
}

void print_service_manager_list(ListServiceManagers* srvManList)
{
    printf("\nServiceManagerList (size %zu): \n", srvManList->size);

    int i=1;
    LinkedListIterator *it = linked_list_iterator_create(srvManList);
    do
    {
        ServiceManager* serMan = (ServiceManager*) linked_list_iterator_get_element(it);
        if(serMan == NULL)
            continue;

        printf("Subscription %i\n",i); i++;
        printf("\tManagedServiceKey:  "); print_hex_char_array(serMan->service_key, SHA1_BLOCK_SIZE);
    } while(linked_list_iterator_advance(it) != -1);
    linked_list_iterator_destroy(&it);

}

void test_binary_utils()
{
    char *bin_str;
    byte bin_str1[] = {'a', 'b'};
    byte bin_str2[] = {0xf1, 0xa5};
    byte bin_str3[] = {0xf1, 0xa5};
    int higher = -1;

    bin_str = binary_utils_get_formatted_binary_str(bin_str1,2);
    printf("bin_str1: %s\n", bin_str);
    free(bin_str);

    bin_str = binary_utils_get_formatted_binary_str(bin_str2,2);
    printf("bin_str2: %s\n", bin_str);
    free(bin_str);

    byte *xor_result = binary_utils_xor(bin_str1, bin_str2, 2);
    bin_str = binary_utils_get_formatted_binary_str(xor_result,2);

    print_hex_char_array(xor_result, 2);
    printf("bin_str_: %s\n", bin_str);
    free(bin_str);

    higher = binary_utils_get_higher_binary_string(bin_str1, bin_str2, 2);
    printf("higher: %i\n", higher);
    higher = binary_utils_get_higher_binary_string(bin_str2, bin_str1, 2);
    printf("higher: %i\n", higher);
    higher = binary_utils_get_higher_binary_string(bin_str2, bin_str3, 2);
    printf("higher: %i\n", higher);
}
