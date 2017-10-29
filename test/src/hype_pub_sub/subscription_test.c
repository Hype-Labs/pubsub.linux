#include "subscription_test.h"

void hype_pub_sub_subscription_test()
{

    char SUBS1_SERVICE[] = "CoffeService";
    byte SUBS1_MANAGER[] = "\x85\xa9\xd4\xc4\xde\xd2\x87\x75\x0f\xc0\xed\x32";
    char SUBS2_SERVICE[] = "HypeSports";
    byte SUBS2_MANAGER[] = "\xd5\x5b\x68\x8c\xe5\xe8\x3f\xd4\x5e\x5d\xe1\xae";
    char SUBS3_SERVICE[] = "HypeTech";
    byte SUBS3_MANAGER[] = "\xdd\x52\x54\xe5\xe7\x7c\x07\xfa\x43\xb2\x70\x3d";

    Subscription *subsc1 = hpb_subscription_create(SUBS1_SERVICE, strlen(SUBS1_SERVICE), SUBS1_MANAGER);
    Subscription *subsc2 = hpb_subscription_create(SUBS2_SERVICE, strlen(SUBS2_SERVICE), SUBS2_MANAGER);
    Subscription *subsc3 = hpb_subscription_create(SUBS3_SERVICE, strlen(SUBS3_SERVICE), SUBS3_MANAGER);

    CU_ASSERT_PTR_NOT_NULL_FATAL(subsc1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(subsc2);
    CU_ASSERT_PTR_NOT_NULL_FATAL(subsc3);

    CU_ASSERT_NSTRING_EQUAL(subsc1->service_name, SUBS1_SERVICE, strlen(SUBS1_SERVICE));
    CU_ASSERT_NSTRING_EQUAL(subsc2->service_name, SUBS2_SERVICE, strlen(SUBS2_SERVICE));
    CU_ASSERT_NSTRING_EQUAL(subsc3->service_name, SUBS3_SERVICE, strlen(SUBS3_SERVICE));

    CU_ASSERT_NSTRING_EQUAL(subsc1->service_key, "\x49\x48\xf4\xe7\x11\x80\x98\x0f\xd7\xb9\x6b\x22\xbe\x91\x54\x20\xe4\xcd\x7e\x2b", SHA1_BLOCK_SIZE);
    CU_ASSERT_NSTRING_EQUAL(subsc2->service_key, "\x2a\x0f\x55\x8c\x63\x6f\x89\x18\x4c\x64\xe2\x5b\xc3\x7b\x86\x39\xf5\xad\x8f\x69", SHA1_BLOCK_SIZE);
    CU_ASSERT_NSTRING_EQUAL(subsc3->service_key, "\x0f\x20\xf1\x8b\x65\xbf\x1e\xa0\xcb\x21\xda\x6f\xd8\xf9\xe5\x5b\x0b\xcb\x54\x84", SHA1_BLOCK_SIZE);

    CU_ASSERT_NSTRING_EQUAL(subsc1->manager_id, "\x85\xa9\xd4\xc4\xde\xd2\x87\x75\x0f\xc0\xed\x32", HYPE_CONSTANTS_ID_BYTE_SIZE);
    CU_ASSERT_NSTRING_EQUAL(subsc2->manager_id, "\xd5\x5b\x68\x8c\xe5\xe8\x3f\xd4\x5e\x5d\xe1\xae", HYPE_CONSTANTS_ID_BYTE_SIZE);
    CU_ASSERT_NSTRING_EQUAL(subsc3->manager_id, "\xdd\x52\x54\xe5\xe7\x7c\x07\xfa\x43\xb2\x70\x3d", HYPE_CONSTANTS_ID_BYTE_SIZE);

    hpb_subscription_destroy(&subsc1);
    hpb_subscription_destroy(&subsc2);
    hpb_subscription_destroy(&subsc3);
    CU_ASSERT_PTR_NULL(subsc1);
    CU_ASSERT_PTR_NULL(subsc2);
    CU_ASSERT_PTR_NULL(subsc3);
}
