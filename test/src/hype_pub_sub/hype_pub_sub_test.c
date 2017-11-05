
#include "hype_pub_sub_test.h"

byte HPB_TEST_MANAGED_SERVICE1_REQUESTER[] = "\x10\x11\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09";
byte HPB_TEST_MANAGED_SERVICE2_REQUESTER[] = "\x66\xd8\xf2\x20\x6a\x56\xdb\xe9\x91\x23\x3b\xc2";
byte HPB_TEST_MANAGED_SERVICE1_KEY[] = "\x8b\xa1\x04\x94\xc2\x9d\x24\x76\x04\xb1\x5c\xd2\x40\x01\x32\x33\x58\xa8\x9b\xf5";
byte HPB_TEST_MANAGED_SERVICE2_KEY[] = "\xf2\x95\xa7\x85\x27\x72\xfd\x6c\x88\xb5\x14\x37\xf3\x5e\x5e\x73\x08\x9f\xad\x3e";

void hpb_test()
{
    HypePubSub *hpb = hpb_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(hpb);
    CU_ASSERT_PTR_NOT_NULL_FATAL(hpb->own_subscriptions);
    CU_ASSERT_PTR_NOT_NULL_FATAL(hpb->managed_services);
    CU_ASSERT_PTR_NOT_NULL_FATAL(hpb->network);
    CU_ASSERT_PTR_NOT_NULL_FATAL(hpb->protocol);

    hpb_test_issue_subscribe_req(hpb);
    hpb_test_issue_unsubscribe_req(hpb);
    hpb_test_issue_publish_req(hpb);

    hpb_test_process_subscribe_req(hpb);
    hpb_test_process_unsubscribe_req(hpb);
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

void hpb_test_process_subscribe_req(HypePubSub *hpb)
{
    CU_ASSERT(hpb->managed_services->size == 0);

    // Test 1st service add
    hpb_process_subscribe_req(hpb, HPB_TEST_MANAGED_SERVICE1_KEY, HPB_TEST_MANAGED_SERVICE1_REQUESTER);
    CU_ASSERT(hpb->managed_services->size == 1);

    // Test 2nd service add
    hpb_process_subscribe_req(hpb, HPB_TEST_MANAGED_SERVICE2_KEY, HPB_TEST_MANAGED_SERVICE2_REQUESTER);
    CU_ASSERT(hpb->managed_services->size == 2);

    // Test already existent service add
    hpb_process_subscribe_req(hpb, HPB_TEST_MANAGED_SERVICE1_KEY, HPB_TEST_MANAGED_SERVICE1_REQUESTER);
    CU_ASSERT(hpb->managed_services->size == 2);


}

void hpb_test_process_unsubscribe_req(HypePubSub *hpb)
{

}

void hpb_test_process_publish_req(HypePubSub *hpb)
{

}

void hpb_test_process_info_req(HypePubSub *hpb)
{

}
