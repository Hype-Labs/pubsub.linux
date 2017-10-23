#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "hype_pub_sub/hype_pub_sub.h"
#include "../external/include/sha/sha1.h"

void test_subscribers_list();
void test_service_manager();
void test_hype_pub_sub();

void print_hex_char_array(unsigned char* array, size_t len);
void print_subs_list(ListSubscribers* head);
void print_subscription_list(ListSubscriptions* head);

byte EXAMPLE_ID1[] = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11\x12";
byte EXAMPLE_ID2[] = "\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11";
byte EXAMPLE_ID3[] = "\x11\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10";
byte EXAMPLE_ID4[] = "\x10\x11\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09";

int main()
{
    char service[] = {"HypeCoffe"};
    unsigned char service_key[SHA1_BLOCK_SIZE];

    sha1_digest((const BYTE*) service, strlen(service), service_key);
    print_hex_char_array(service_key, SHA1_BLOCK_SIZE);

    Subscription* hSubs = hype_pub_sub_subscription_create(service, strlen(service), EXAMPLE_ID1);
    printf("Service name: %s\n", hSubs->service_name);
    print_hex_char_array(hSubs->service_key, SHA1_BLOCK_SIZE);
    hype_pub_sub_subscription_destroy(hSubs);

    //test_subscribers_list();

    test_service_manager();

    //test_hype_pub_sub();

    return 0;
}


void test_subscribers_list()
{
    LinkedListElement* subscribers = hype_pub_sub_list_subscribers_create();
    hype_pub_sub_list_subscribers_add(subscribers, EXAMPLE_ID1);
    hype_pub_sub_list_subscribers_add(subscribers, EXAMPLE_ID2);
    hype_pub_sub_list_subscribers_add(subscribers, EXAMPLE_ID3);
    hype_pub_sub_list_subscribers_add(subscribers, EXAMPLE_ID4);
    printf("\nAdded id1, id2, id3, id4\n");
    print_subs_list(subscribers);


    hype_pub_sub_list_subscribers_remove(&subscribers, EXAMPLE_ID3);
    printf("\nRemoved id3\n");
    print_subs_list(subscribers);

    hype_pub_sub_list_subscribers_remove(&subscribers, EXAMPLE_ID3);
    printf("\nRemoved id3 again\n");
    print_subs_list(subscribers);

    hype_pub_sub_list_subscribers_remove(&subscribers, EXAMPLE_ID4);
    printf("\nRemoved id4\n");
    print_subs_list(subscribers);

    hype_pub_sub_list_subscribers_remove(&subscribers, EXAMPLE_ID1);
    printf("\nRemoved id1\n");
    print_subs_list(subscribers);

    hype_pub_sub_list_subscribers_remove(&subscribers, EXAMPLE_ID2);
    printf("\nRemoved id2\n");
    print_subs_list(subscribers);

    hype_pub_sub_list_subscribers_add(subscribers, EXAMPLE_ID4);
    printf("\nAdded id4\n");
    print_subs_list(subscribers);


    printf("\nAdded id1, id2, id3, id4\n");
    hype_pub_sub_list_subscribers_add(subscribers, EXAMPLE_ID1);
    hype_pub_sub_list_subscribers_add(subscribers, EXAMPLE_ID2);
    hype_pub_sub_list_subscribers_add(subscribers, EXAMPLE_ID3);
    hype_pub_sub_list_subscribers_add(subscribers, EXAMPLE_ID4);
    print_subs_list(subscribers);

    hype_pub_sub_list_subscribers_destroy(subscribers);
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

    ServiceManager* servMan1 = hype_pub_sub_service_manager_create(servKey1);
    ServiceManager* servMan2 = hype_pub_sub_service_manager_create(servKey2);
    ServiceManager* servMan3 = hype_pub_sub_service_manager_create(servKey3);
    ServiceManager* servMan4 = hype_pub_sub_service_manager_create(servKey4);

    HypePubSub* myPubSubApp = hype_pub_sub_create();

    hype_pub_sub_list_service_managers_add(myPubSubApp->list_serv_man,servMan1);

    hype_pub_sub_destroy(myPubSubApp);
}

void test_hype_pub_sub()
{
    HypePubSub* myPubSubApp = hype_pub_sub_create();

    char serv1[] = {"HypeCoffe"};
    byte serv1ManId[] = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11\x12";
    char serv2[] = {"HypeFruit"};
    byte serv2ManId[] = "\x02\x01\x03\x04\x05\x06\x07\x08\x09\x10\x11\x12";
    char serv3[] = {"HypeDrinks"};
    byte serv3ManId[] = "\x03\x01\x02\x04\x05\x06\x07\x08\x09\x10\x11\x12";
    char serv4[] = {"HypeFood"};
    byte serv4ManId[] = "\x04\x01\x02\x03\x05\x06\x07\x08\x09\x10\x11\x12";

    Subscription* subscription1 = hype_pub_sub_subscription_create(serv1, strlen(serv1), serv1ManId);
    Subscription* subscription2 = hype_pub_sub_subscription_create(serv2, strlen(serv2), serv2ManId);
    Subscription* subscription3 = hype_pub_sub_subscription_create(serv3, strlen(serv3), serv3ManId);
    Subscription* subscription4 = hype_pub_sub_subscription_create(serv4, strlen(serv4), serv4ManId);

    hype_pub_sub_list_subscriptions_add(myPubSubApp->list_subscriptions, subscription1);
    print_subscription_list(myPubSubApp->list_subscriptions);

    hype_pub_sub_list_subscriptions_add(myPubSubApp->list_subscriptions, subscription2);
    hype_pub_sub_list_subscriptions_add(myPubSubApp->list_subscriptions, subscription3);
    print_subscription_list(myPubSubApp->list_subscriptions);

    hype_pub_sub_list_subscriptions_add(myPubSubApp->list_subscriptions, subscription4);
    print_subscription_list(myPubSubApp->list_subscriptions);

    hype_pub_sub_destroy(myPubSubApp);
}

void print_hex_char_array(unsigned char* array, size_t len)
{
    for(int i=0; i<len; i++)
        printf("%.2x", array[i]);

    printf("\n");
}

void print_subs_list(ListSubscribers* head)
{
    printf("SubscriberList: \n");
    if(head == NULL || head->data == NULL)
        return;

    ListSubscribers* current_subs = head;

    do
    {
        print_hex_char_array((byte *) current_subs->data, HYPE_ID_BYTE_SIZE);
        current_subs = current_subs->next;
    }
    while(current_subs != NULL);
}

void print_subscription_list(ListSubscriptions* head)
{
    printf("SubscriptionsList: \n");
    if(head == NULL || head->data == NULL)
        return;

    ListSubscriptions* current_subs = head;

    int i=1;
    do
    {
        printf("Subscription %i\n",i);
        printf("\tManagerId:  ");
        print_hex_char_array(((Subscription *) current_subs->data)->manager_id, HYPE_ID_BYTE_SIZE);
        printf("\tServiceKey:  ");
        print_hex_char_array(((Subscription *) current_subs->data)->service_key, SHA1_BLOCK_SIZE);
        printf("\tServiceName:  %s\n", ((Subscription *) current_subs->data)->service_name);
        current_subs = current_subs->next;
        i++;
    }
    while(current_subs != NULL);
}

