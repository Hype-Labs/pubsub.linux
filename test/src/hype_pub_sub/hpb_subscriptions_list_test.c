#include "hpb_subscriptions_list_test.h"
#include "hpb_test_utils.h"

static HLByte MANAGER_ID1[] = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11\x12";
static HLByte MANAGER_ID2[] = "\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11";
static HLByte MANAGER_ID3[] = "\x11\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10";

void hpb_list_subscriptions_test()
{
    char SERVICE1_NAME[] = "HypeCoffe";
    char SERVICE2_NAME[] = "HypeTea";
    char SERVICE3_NAME[] = "HypeBeer";
    size_t SERVICE1_SIZE = 9;
    size_t SERVICE2_SIZE = 7;
    size_t SERVICE3_SIZE = 8;
    HLByte SERVICE1_KEY[] = "\x8b\xa1\x04\x94\xc2\x9d\x24\x76\x04\xb1\x5c\xd2\x40\x01\x32\x33\x58\xa8\x9b\xf5";
    HLByte SERVICE2_KEY[] = "\xf2\x95\xa7\x85\x27\x72\xfd\x6c\x88\xb5\x14\x37\xf3\x5e\x5e\x73\x08\x9f\xad\x3e";
    HLByte SERVICE3_KEY[] = "\xfb\x42\x14\x7b\xab\x42\xa4\xee\x5d\xa9\xde\x58\xa0\xa5\x07\x80\xdf\x94\x48\x88";

    // Test the creation of the subscriptions list
    HpbSubscription *aux_subscr;
    HpbSubscriptionsList *subscriptions = hpb_list_subscriptions_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(subscriptions);
    CU_ASSERT_PTR_NULL(subscriptions->head);
    CU_ASSERT(subscriptions->size == 0);

    // Add 3 subscriptions to the list
    HypeInstance *instance1 = hpb_test_utils_get_instance_from_id(MANAGER_ID1, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    HypeInstance *instance2 = hpb_test_utils_get_instance_from_id(MANAGER_ID2, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    HypeInstance *instance3 = hpb_test_utils_get_instance_from_id(MANAGER_ID3, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    hpb_list_subscriptions_add(subscriptions, SERVICE3_NAME, SERVICE3_SIZE, instance3);
    hpb_list_subscriptions_add(subscriptions, SERVICE1_NAME, SERVICE1_SIZE, instance1);
    hpb_list_subscriptions_add(subscriptions, SERVICE2_NAME, SERVICE2_SIZE, instance2);

    // Validate that the subscriptions are inserted in the right order
    LinkedListIterator *it = linked_list_iterator_create(subscriptions);
    aux_subscr = (HpbSubscription *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->manager_instance->identifier->data, MANAGER_ID3, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->service_name, SERVICE3_NAME, SERVICE3_SIZE);
    linked_list_iterator_advance(it);
    aux_subscr = (HpbSubscription *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->manager_instance->identifier->data, MANAGER_ID1, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->service_name, SERVICE1_NAME, SERVICE1_SIZE);
    linked_list_iterator_advance(it);
    aux_subscr = (HpbSubscription *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->manager_instance->identifier->data, MANAGER_ID2, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->service_name, SERVICE2_NAME, SERVICE2_SIZE);
    CU_ASSERT(subscriptions->size == 3);

    // Test find against existent and non-existent service keys
    HLByte NON_EXISTENT_KEY[] = "\xee\x5d\xa9\xde\x58\xa0\xa5\xfb\x42\x14\x7b\xab\x42\xa4\x07\x80\xdf\x94\x48\x88";
    CU_ASSERT_PTR_NOT_NULL(hpb_list_subscriptions_find(subscriptions, SERVICE1_KEY));
    CU_ASSERT_PTR_NOT_NULL(hpb_list_subscriptions_find(subscriptions, SERVICE2_KEY));
    CU_ASSERT_PTR_NOT_NULL(hpb_list_subscriptions_find(subscriptions, SERVICE3_KEY));
    CU_ASSERT_PTR_NULL(hpb_list_subscriptions_find(subscriptions, NON_EXISTENT_KEY));

    // Test element removal
    hpb_list_subscriptions_remove(subscriptions, SERVICE3_KEY);
    linked_list_iterator_reset(it);
    aux_subscr = (HpbSubscription *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->manager_instance->identifier->data, MANAGER_ID1, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->service_name, SERVICE1_NAME, SERVICE1_SIZE);
    linked_list_iterator_advance(it);
    aux_subscr = (HpbSubscription *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->manager_instance->identifier->data, MANAGER_ID2, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->service_name, SERVICE2_NAME, SERVICE2_SIZE);
    CU_ASSERT(subscriptions->size == 2);

    // Test non-existent element removal
    hpb_list_subscriptions_remove(subscriptions, NON_EXISTENT_KEY);
    CU_ASSERT(subscriptions->size == 2);

    // Test element removal
    hpb_list_subscriptions_remove(subscriptions, SERVICE2_KEY);
    linked_list_iterator_reset(it);
    aux_subscr = (HpbSubscription *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->manager_instance->identifier->data, MANAGER_ID1, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->service_name, SERVICE1_NAME, SERVICE1_SIZE);
    CU_ASSERT(subscriptions->size == 1);

    // Test last element removal
    hpb_list_subscriptions_remove(subscriptions, SERVICE1_KEY);
    linked_list_iterator_reset(it);
    aux_subscr = (HpbSubscription *) linked_list_iterator_get_element(it);
    CU_ASSERT_PTR_NULL(it->it_node);
    CU_ASSERT_PTR_NULL(aux_subscr);
    CU_ASSERT(subscriptions->size == 0);

    // Test the destruction of the subscriptions list
    linked_list_iterator_destroy(&it);
    hpb_list_subscriptions_destroy(&subscriptions);
    CU_ASSERT_PTR_NULL(subscriptions);

    // clear heap memory
    hype_instance_release(instance1);
    hype_instance_release(instance2);
    hype_instance_release(instance3);
}
