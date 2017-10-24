#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "hype_pub_sub/hype_pub_sub.h"
#include "../external/include/sha/sha1.h"

void test_hash();
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
    //test_hash();

    //test_subscribers_list();

    test_service_manager();

    //test_hype_pub_sub();

    return 0;
}

void test_hash()
{
    char service[] = {"HypeCoffe"};
    unsigned char service_key[SHA1_BLOCK_SIZE];

    sha1_digest((const BYTE*) service, strlen(service), service_key);
    print_hex_char_array(service_key, SHA1_BLOCK_SIZE);
}

void test_subscribers_list()
{
    ListClients* subscribers = hype_pub_sub_list_clients_create();

    printf("\nAdding id1, id2, id3, id4\n");
    hype_pub_sub_list_clients_add(subscribers, EXAMPLE_ID1);
    hype_pub_sub_list_clients_add(subscribers, EXAMPLE_ID2);
    hype_pub_sub_list_clients_add(subscribers, EXAMPLE_ID3);
    hype_pub_sub_list_clients_add(subscribers, EXAMPLE_ID4);
    print_clients_list(subscribers);

    printf("\nRemoving id3\n");
    hype_pub_sub_list_clients_remove(subscribers, EXAMPLE_ID3);
    print_clients_list(subscribers);

    printf("\nRemoving id3 again\n");
    hype_pub_sub_list_clients_remove(subscribers, EXAMPLE_ID3);
    print_clients_list(subscribers);

    printf("\nRemoving id4\n");
    hype_pub_sub_list_clients_remove(subscribers, EXAMPLE_ID4);
    print_clients_list(subscribers);

    printf("\nRemoving id1\n");
    hype_pub_sub_list_clients_remove(subscribers, EXAMPLE_ID1);
    print_clients_list(subscribers);

    printf("\nRemoving id2\n");
    hype_pub_sub_list_clients_remove(subscribers, EXAMPLE_ID2);
    print_clients_list(subscribers);

    printf("\nAdding id4\n");
    hype_pub_sub_list_clients_add(subscribers, EXAMPLE_ID4);
    print_clients_list(subscribers);

    printf("\nAdding id1, id2, id3, id4\n");
    hype_pub_sub_list_clients_add(subscribers, EXAMPLE_ID1);
    hype_pub_sub_list_clients_add(subscribers, EXAMPLE_ID2);
    hype_pub_sub_list_clients_add(subscribers, EXAMPLE_ID3);
    hype_pub_sub_list_clients_add(subscribers, EXAMPLE_ID4);
    print_clients_list(subscribers);

    hype_pub_sub_list_clients_destroy(subscribers);
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

    HypePubSub* myPubSubApp = hype_pub_sub_create();

    printf("\nAdding serv1\n");
    hype_pub_sub_list_service_managers_add(myPubSubApp->list_serv_man,servKey1);
    print_service_manager_list(myPubSubApp->list_serv_man);

    printf("\nRemoving serv1\n");
    hype_pub_sub_list_service_managers_remove(myPubSubApp->list_serv_man,servKey1);
    print_service_manager_list(myPubSubApp->list_serv_man);

    printf("\nAdding serv2, serv1\n");
    hype_pub_sub_list_service_managers_add(myPubSubApp->list_serv_man,servKey2);
    hype_pub_sub_list_service_managers_add(myPubSubApp->list_serv_man,servKey1);
    print_service_manager_list(myPubSubApp->list_serv_man);

    hype_pub_sub_destroy(myPubSubApp);
}

void test_hype_pub_sub()
{
    HypePubSub* myPubSubApp = hype_pub_sub_create();

    char serv1[] = {"HypeCoffe"};
    char serv2[] = {"HypeFruit"};
    char serv3[] = {"HypeDrinks"};
    char serv4[] = {"HypeFood"};
    byte serv1ManId[] = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11\x12";
    byte serv2ManId[] = "\x02\x01\x03\x04\x05\x06\x07\x08\x09\x10\x11\x12";
    byte serv3ManId[] = "\x03\x01\x02\x04\x05\x06\x07\x08\x09\x10\x11\x12";
    byte serv4ManId[] = "\x04\x01\x02\x03\x05\x06\x07\x08\x09\x10\x11\x12";

    hype_pub_sub_list_subscriptions_add(myPubSubApp->list_subscriptions, serv1, strlen(serv1), serv1ManId);
    print_subscription_list(myPubSubApp->list_subscriptions);

    hype_pub_sub_list_subscriptions_add(myPubSubApp->list_subscriptions, serv2, strlen(serv2), serv2ManId);
    hype_pub_sub_list_subscriptions_add(myPubSubApp->list_subscriptions, serv3, strlen(serv3), serv3ManId);
    print_subscription_list(myPubSubApp->list_subscriptions);

    hype_pub_sub_list_subscriptions_add(myPubSubApp->list_subscriptions, serv4, strlen(serv4), serv4ManId);
    print_subscription_list(myPubSubApp->list_subscriptions);

    hype_pub_sub_list_subscriptions_remove(myPubSubApp->list_subscriptions, serv3, strlen(serv3), serv3ManId);
    print_subscription_list(myPubSubApp->list_subscriptions);

    hype_pub_sub_destroy(myPubSubApp);
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

    LinkedListIterator *it = linked_list_create_iterator(clientList);
    while(linked_list_get_element_data_iterator(it) != NULL)
    {
        Client* client = (Client*) linked_list_get_element_data_iterator(it);
        print_hex_char_array(client->client_id, HYPE_ID_BYTE_SIZE);
        linked_list_advance_iterator(it);
    }
    linked_list_destroy_iterator(it);
}

void print_subscription_list(ListSubscriptions* subsList)
{
    printf("\nSubscriptionsList (size %zu): \n", subsList->size);

    int i=1;
    LinkedListIterator *it = linked_list_create_iterator(subsList);
    while(linked_list_get_element_data_iterator(it) != NULL)
    {
        Subscription* subs = (Subscription*) linked_list_get_element_data_iterator(it);
        printf("Subscription %i\n",i); i++;
        printf("\tManagerId:  "); print_hex_char_array(subs->manager_id, HYPE_ID_BYTE_SIZE);
        printf("\tServiceKey:  "); print_hex_char_array(subs->service_key, SHA1_BLOCK_SIZE);
        printf("\tServiceName:  %s\n", subs->service_name);
        linked_list_advance_iterator(it);
    }
    linked_list_destroy_iterator(it);
}

void print_service_manager_list(ListServiceManagers* srvManList)
{
    printf("\nServiceManagerList (size %zu): \n", srvManList->size);

    int i=1;
    LinkedListIterator *it = linked_list_create_iterator(srvManList);
    while(linked_list_get_element_data_iterator(it) != NULL)
    {
        ServiceManager* serMan = (ServiceManager*) linked_list_get_element_data_iterator(it);
        printf("Subscription %i\n",i); i++;
        printf("\tManagedServiceKey:  "); print_hex_char_array(serMan->service_key, SHA1_BLOCK_SIZE);
        linked_list_advance_iterator(it);
    }
    linked_list_destroy_iterator(it);

}
