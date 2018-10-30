
#include "hype_pub_sub_test.h"

HLByte HPB_TEST_CLIENT1[] = "\x10\x11\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09";
HLByte HPB_TEST_CLIENT2[] = "\x66\xd8\xf2\x20\x6a\x56\xdb\xe9\x91\x23\x3b\xc2";
HLByte HPB_TEST_CLIENT3[] = "\x6a\x66\xd8\xf2\x20\x56\xdb\xe9\x91\x23\x3b\xc2";
HLByte HPB_TEST_CLIENT4[] = "\xf2\x66\xd8\x20\x6a\x56\xdb\xe9\x91\x23\x3b\xc2";
HLByte HPB_TEST_CLIENT5[] = "\xd8\x66\xf2\x20\x6a\x56\xdb\xe9\x91\x23\x3b\xc2";
HLByte HPB_TEST_CLIENT6[] = "\xdb\xe9\x91\x23\x3b\xc2\x66\xd8\xf2\x20\x6a\x56";
HLByte HPB_TEST_CLIENT7[] = "\x23\x3b\xc2\x66\xd8\xf2\x20\x6a\x56\xdb\xe9\x91";
HLByte HPB_TEST_CLIENT8[] = "\xc2\x66\xd8\xf2\x20\x6a\x56\xdb\xe9\x91\x23\x3b";
HLByte HPB_TEST_CLIENT9[] = "\x56\xdb\x66\xd8\xf2\x20\x6a\xe9\x91\x23\x3b\xc2";
HLByte HPB_TEST_CLIENT10[] = "\x6a\x56\xdb\xe9\x91\x66\xd8\xf2\x20\x23\x3b\xc2";

HLByte HPB_TEST_SERVICE1[] = "\x8b\xa1\x04\x94\xc2\x9d\x24\x76\x04\xb1\x5c\xd2\x40\x01\x32\x33\x58\xa8\x9b\xf5";
HLByte HPB_TEST_SERVICE2[] = "\xf2\x95\xa7\x85\x27\x72\xfd\x6c\x88\xb5\x14\x37\xf3\x5e\x5e\x73\x08\x9f\xad\x3e";

static int CLIENT_HYPE_ID_SIZE = 12;

void hpb_test()
{
    HypePubSub *hpb = hpb_get();
    CU_ASSERT_PTR_NOT_NULL_FATAL(hpb);
    CU_ASSERT_PTR_NOT_NULL_FATAL(hpb->own_subscriptions);
    CU_ASSERT_PTR_NOT_NULL_FATAL(hpb->managed_services);
    CU_ASSERT_PTR_NOT_NULL_FATAL(hpb->network);
    CU_ASSERT_PTR_NOT_NULL_FATAL(hpb->protocol);

    hpb_test_issue_subscribe_req(hpb);
    hpb_test_issue_unsubscribe_req(hpb);
    hpb_test_issue_publish_req(hpb);

    hpb_test_process_subscribe_and_unsubscribe(hpb);
    hpb_test_process_publish_req(hpb);
    hpb_test_process_info_req(hpb);

    hpb_destroy(&hpb);
    CU_ASSERT_PTR_NULL(hpb);
}

void hpb_test_issue_subscribe_req(HypePubSub *hpb)
{

}

void hpb_test_issue_unsubscribe_req(HypePubSub *hpb)
{

}

void hpb_test_issue_publish_req(HypePubSub *hpb)
{

}

void hpb_test_process_subscribe_and_unsubscribe(HypePubSub *hpb)
{
    HypeBuffer *client1_buffer_id = hype_buffer_create_from(HPB_TEST_CLIENT1, CLIENT_HYPE_ID_SIZE);
    HypeBuffer *client2_buffer_id = hype_buffer_create_from(HPB_TEST_CLIENT2, CLIENT_HYPE_ID_SIZE);
    HypeBuffer *client3_buffer_id = hype_buffer_create_from(HPB_TEST_CLIENT3, CLIENT_HYPE_ID_SIZE);
    HypeBuffer *client4_buffer_id = hype_buffer_create_from(HPB_TEST_CLIENT4, CLIENT_HYPE_ID_SIZE);
    HypeBuffer *client5_buffer_id = hype_buffer_create_from(HPB_TEST_CLIENT5, CLIENT_HYPE_ID_SIZE);
    HypeBuffer *client6_buffer_id = hype_buffer_create_from(HPB_TEST_CLIENT6, CLIENT_HYPE_ID_SIZE);
    HypeBuffer *client7_buffer_id = hype_buffer_create_from(HPB_TEST_CLIENT7, CLIENT_HYPE_ID_SIZE);
    HypeBuffer *client8_buffer_id = hype_buffer_create_from(HPB_TEST_CLIENT8, CLIENT_HYPE_ID_SIZE);
    HypeBuffer *client9_buffer_id = hype_buffer_create_from(HPB_TEST_CLIENT9, CLIENT_HYPE_ID_SIZE);
    HypeBuffer *client10_buffer_id = hype_buffer_create_from(HPB_TEST_CLIENT10, CLIENT_HYPE_ID_SIZE);
    HypeInstance *instance1 = hype_instance_create(client1_buffer_id, NULL, false);
    HypeInstance *instance2 = hype_instance_create(client2_buffer_id, NULL, false);
    HypeInstance *instance3 = hype_instance_create(client3_buffer_id, NULL, false);
    HypeInstance *instance4 = hype_instance_create(client1_buffer_id, NULL, false);
    HypeInstance *instance5 = hype_instance_create(client2_buffer_id, NULL, false);
    HypeInstance *instance6 = hype_instance_create(client3_buffer_id, NULL, false);
    HypeInstance *instance7 = hype_instance_create(client1_buffer_id, NULL, false);
    HypeInstance *instance8 = hype_instance_create(client2_buffer_id, NULL, false);
    HypeInstance *instance9 = hype_instance_create(client3_buffer_id, NULL, false);
    HypeInstance *instance10 = hype_instance_create(client3_buffer_id, NULL, false);

    CU_ASSERT(hpb->managed_services->size == 0);

    CU_ASSERT(hpb_process_subscribe_req(HPB_TEST_SERVICE1, instance1) == -1);
    CU_ASSERT(hpb_process_unsubscribe_req(HPB_TEST_SERVICE1, instance1) == -1);
    CU_ASSERT(hpb_process_unsubscribe_req(HPB_TEST_SERVICE1, instance1) == -2);

    // Basic test with 2 services with 3 clients
    hpb_process_subscribe_req(HPB_TEST_SERVICE1, instance1);
    CU_ASSERT(hpb->managed_services->size == 1);
    hpb_process_subscribe_req(HPB_TEST_SERVICE2, instance2);
    CU_ASSERT(hpb->managed_services->size == 2);
    hpb_process_subscribe_req(HPB_TEST_SERVICE1, instance3);
    CU_ASSERT(hpb->managed_services->size == 2);

    HpbServiceManager *service1 = hpb_list_service_managers_find(hpb->managed_services, HPB_TEST_SERVICE1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(service1);
    CU_ASSERT(service1->subscribers->size == 2);
    HpbServiceManager *service2 = hpb_list_service_managers_find(hpb->managed_services, HPB_TEST_SERVICE2);
    CU_ASSERT_PTR_NOT_NULL_FATAL(service2);
    CU_ASSERT(service2->subscribers->size == 1);

    CU_ASSERT_PTR_NOT_NULL(hpb_list_clients_find(service1->subscribers, instance1));
    CU_ASSERT_PTR_NULL(hpb_list_clients_find(service1->subscribers, instance2));
    CU_ASSERT_PTR_NOT_NULL(hpb_list_clients_find(service1->subscribers, instance3));
    CU_ASSERT_PTR_NULL(hpb_list_clients_find(service2->subscribers, instance1));
    CU_ASSERT_PTR_NOT_NULL(hpb_list_clients_find(service2->subscribers, instance2));
    CU_ASSERT_PTR_NULL(hpb_list_clients_find(service2->subscribers, instance3));

    // Test unsubscriptions on the 1st managed service
    hpb_process_unsubscribe_req(HPB_TEST_SERVICE1, instance1);
    CU_ASSERT(service1->subscribers->size == 1);
    hpb_process_unsubscribe_req(HPB_TEST_SERVICE1, instance2);
    CU_ASSERT(service1->subscribers->size == 1);
    hpb_process_unsubscribe_req(HPB_TEST_SERVICE1, instance3);
    CU_ASSERT(hpb->managed_services->size == 1);

    // Test subscriptions on the 2nd managed service
    hpb_process_subscribe_req(HPB_TEST_SERVICE2, instance1);
    hpb_process_subscribe_req(HPB_TEST_SERVICE2, instance2);
    hpb_process_subscribe_req(HPB_TEST_SERVICE2, instance3);
    hpb_process_subscribe_req(HPB_TEST_SERVICE2, instance4);
    hpb_process_subscribe_req(HPB_TEST_SERVICE2, instance5);
    hpb_process_subscribe_req(HPB_TEST_SERVICE2, instance6);
    hpb_process_subscribe_req(HPB_TEST_SERVICE2, instance7);
    hpb_process_subscribe_req(HPB_TEST_SERVICE2, instance8);
    hpb_process_subscribe_req(HPB_TEST_SERVICE2, instance9);
    hpb_process_subscribe_req(HPB_TEST_SERVICE2, instance10);
    CU_ASSERT(service2->subscribers->size == 10);
    CU_ASSERT_PTR_NOT_NULL(hpb_list_clients_find(service2->subscribers, instance1));
    CU_ASSERT_PTR_NOT_NULL(hpb_list_clients_find(service2->subscribers, instance2));
    CU_ASSERT_PTR_NOT_NULL(hpb_list_clients_find(service2->subscribers, instance3));
    CU_ASSERT_PTR_NOT_NULL(hpb_list_clients_find(service2->subscribers, instance4));
    CU_ASSERT_PTR_NOT_NULL(hpb_list_clients_find(service2->subscribers, instance5));
    CU_ASSERT_PTR_NOT_NULL(hpb_list_clients_find(service2->subscribers, instance6));
    CU_ASSERT_PTR_NOT_NULL(hpb_list_clients_find(service2->subscribers, instance7));
    CU_ASSERT_PTR_NOT_NULL(hpb_list_clients_find(service2->subscribers, instance8));
    CU_ASSERT_PTR_NOT_NULL(hpb_list_clients_find(service2->subscribers, instance9));
    CU_ASSERT_PTR_NOT_NULL(hpb_list_clients_find(service2->subscribers, instance10));

    // Test unsubscriptions on the 2nd managed service
    hpb_process_unsubscribe_req(HPB_TEST_SERVICE2, instance3);
    hpb_process_unsubscribe_req(HPB_TEST_SERVICE2, instance7);
    hpb_process_unsubscribe_req(HPB_TEST_SERVICE2, instance9);
    CU_ASSERT(service2->subscribers->size == 7);
    CU_ASSERT_PTR_NULL(hpb_list_clients_find(service2->subscribers, instance3));
    CU_ASSERT_PTR_NULL(hpb_list_clients_find(service2->subscribers, instance7));
    CU_ASSERT_PTR_NULL(hpb_list_clients_find(service2->subscribers, instance9));

    // Clear heap memory
    hype_instance_release(instance1);
    hype_instance_release(instance2);
    hype_instance_release(instance3);
    hype_instance_release(instance4);
    hype_instance_release(instance5);
    hype_instance_release(instance6);
    hype_instance_release(instance7);
    hype_instance_release(instance8);
    hype_instance_release(instance9);
    hype_instance_release(instance10);
    hype_buffer_release(client1_buffer_id);
    hype_buffer_release(client2_buffer_id);
    hype_buffer_release(client3_buffer_id);
    hype_buffer_release(client4_buffer_id);
    hype_buffer_release(client5_buffer_id);
    hype_buffer_release(client6_buffer_id);
    hype_buffer_release(client7_buffer_id);
    hype_buffer_release(client8_buffer_id);
    hype_buffer_release(client9_buffer_id);
    hype_buffer_release(client10_buffer_id);
}


void hpb_test_process_publish_req(HypePubSub *hpb)
{

}

void hpb_test_process_info_req(HypePubSub *hpb)
{

}
