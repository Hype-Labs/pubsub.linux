#include "hpb_subscription_test.h"
#include "hpb_test_utils.h"


static HLByte SUBS1_MANAGER[] = "\x85\xa9\xd4\xc4\xde\xd2\x87\x75\x0f\xc0\xed\x32";
static HLByte SUBS2_MANAGER[] = "\xd5\x5b\x68\x8c\xe5\xe8\x3f\xd4\x5e\x5d\xe1\xae";
static HLByte SUBS3_MANAGER[] = "\xdd\x52\x54\xe5\xe7\x7c\x07\xfa\x43\xb2\x70\x3d";

void hpb_subscription_test()
{
    char SUBS1_SERVICE[] = "CoffeService";
    char SUBS2_SERVICE[] = "HypeSports";
    char SUBS3_SERVICE[] = "HypeTech";
    HypeInstance *instance1 = hpb_test_utils_get_instance_from_id(SUBS1_MANAGER, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    HypeInstance *instance2 = hpb_test_utils_get_instance_from_id(SUBS2_MANAGER, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    HypeInstance *instance3 = hpb_test_utils_get_instance_from_id(SUBS3_MANAGER, HPB_UTILS_CLIENT_ID_TEST_SIZE);

    HpbSubscription *subsc1 = hpb_subscription_create(SUBS1_SERVICE, strlen(SUBS1_SERVICE), instance1);
    HpbSubscription *subsc2 = hpb_subscription_create(SUBS2_SERVICE, strlen(SUBS2_SERVICE), instance2);
    HpbSubscription *subsc3 = hpb_subscription_create(SUBS3_SERVICE, strlen(SUBS3_SERVICE), instance3);

    CU_ASSERT_PTR_NOT_NULL_FATAL(subsc1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(subsc2);
    CU_ASSERT_PTR_NOT_NULL_FATAL(subsc3);

    CU_ASSERT_NSTRING_EQUAL(subsc1->service_name, SUBS1_SERVICE, strlen(SUBS1_SERVICE));
    CU_ASSERT_NSTRING_EQUAL(subsc2->service_name, SUBS2_SERVICE, strlen(SUBS2_SERVICE));
    CU_ASSERT_NSTRING_EQUAL(subsc3->service_name, SUBS3_SERVICE, strlen(SUBS3_SERVICE));

    CU_ASSERT_NSTRING_EQUAL(subsc1->service_key, "\x49\x48\xf4\xe7\x11\x80\x98\x0f\xd7\xb9\x6b\x22\xbe\x91\x54\x20\xe4\xcd\x7e\x2b", SHA1_BLOCK_SIZE);
    CU_ASSERT_NSTRING_EQUAL(subsc2->service_key, "\x2a\x0f\x55\x8c\x63\x6f\x89\x18\x4c\x64\xe2\x5b\xc3\x7b\x86\x39\xf5\xad\x8f\x69", SHA1_BLOCK_SIZE);
    CU_ASSERT_NSTRING_EQUAL(subsc3->service_key, "\x0f\x20\xf1\x8b\x65\xbf\x1e\xa0\xcb\x21\xda\x6f\xd8\xf9\xe5\x5b\x0b\xcb\x54\x84", SHA1_BLOCK_SIZE);

    CU_ASSERT_NSTRING_EQUAL(subsc1->manager_instance->identifier->data, SUBS1_MANAGER, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    CU_ASSERT_NSTRING_EQUAL(subsc2->manager_instance->identifier->data, SUBS2_MANAGER, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    CU_ASSERT_NSTRING_EQUAL(subsc3->manager_instance->identifier->data, SUBS3_MANAGER, HPB_UTILS_CLIENT_ID_TEST_SIZE);

    hpb_subscription_destroy(&subsc1);
    hpb_subscription_destroy(&subsc2);
    hpb_subscription_destroy(&subsc3);
    CU_ASSERT_PTR_NULL(subsc1);
    CU_ASSERT_PTR_NULL(subsc2);
    CU_ASSERT_PTR_NULL(subsc3);

    hype_instance_release(instance1);
    hype_instance_release(instance2);
    hype_instance_release(instance3);
}
