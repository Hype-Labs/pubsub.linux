#include "list_subscriptions_test.h"

void hpb_list_subscriptions_test()
{
    char SERVICE1_NAME[] = "HypeCoffe";
    char SERVICE2_NAME[] = "HypeTea";
    char SERVICE3_NAME[] = "HypeBeer";
    size_t SERVICE1_SIZE = 9;
    size_t SERVICE2_SIZE = 7;
    size_t SERVICE3_SIZE = 8;
    byte SERVICE1_KEY[] = "\x8b\xa1\x04\x94\xc2\x9d\x24\x76\x04\xb1\x5c\xd2\x40\x01\x32\x33\x58\xa8\x9b\xf5";
    byte SERVICE2_KEY[] = "\xf2\x95\xa7\x85\x27\x72\xfd\x6c\x88\xb5\x14\x37\xf3\x5e\x5e\x73\x08\x9f\xad\x3e";
    byte SERVICE3_KEY[] = "\xfb\x42\x14\x7b\xab\x42\xa4\xee\x5d\xa9\xde\x58\xa0\xa5\x07\x80\xdf\x94\x48\x88";
    byte MANAGER_ID1[] = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11\x12";
    byte MANAGER_ID2[] = "\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11";
    byte MANAGER_ID3[] = "\x11\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10";

    // Test the creation of the subscriptions list
    HpbSubscription *aux_subscr;
    ListSubscriptions *subscriptions = hpb_list_subscriptions_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(subscriptions);
    CU_ASSERT_PTR_NULL(subscriptions->head);
    CU_ASSERT(subscriptions->size == 0);

    // Add 3 subscriptions to the list
    hpb_list_subscriptions_add(subscriptions, SERVICE3_NAME, SERVICE3_SIZE, MANAGER_ID3);
    hpb_list_subscriptions_add(subscriptions, SERVICE1_NAME, SERVICE1_SIZE, MANAGER_ID1);
    hpb_list_subscriptions_add(subscriptions, SERVICE2_NAME, SERVICE2_SIZE, MANAGER_ID2);

    // Validate that the subscriptions are inserted in the right order
    LinkedListIterator *it = linked_list_iterator_create(subscriptions);
    aux_subscr = (HpbSubscription *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->manager_id, MANAGER_ID3, HPB_ID_BYTE_SIZE);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->service_name, SERVICE3_NAME, SERVICE3_SIZE);
    linked_list_iterator_advance(it);
    aux_subscr = (HpbSubscription *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->manager_id, MANAGER_ID1, HPB_ID_BYTE_SIZE);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->service_name, SERVICE1_NAME, SERVICE1_SIZE);
    linked_list_iterator_advance(it);
    aux_subscr = (HpbSubscription *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->manager_id, MANAGER_ID2, HPB_ID_BYTE_SIZE);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->service_name, SERVICE2_NAME, SERVICE2_SIZE);
    CU_ASSERT(subscriptions->size == 3);

    // Test find against existent and non-existent service keys
    byte NON_EXISTENT_KEY[] = "\xee\x5d\xa9\xde\x58\xa0\xa5\xfb\x42\x14\x7b\xab\x42\xa4\x07\x80\xdf\x94\x48\x88";
    CU_ASSERT_PTR_NOT_NULL(hpb_list_subscriptions_find(subscriptions, SERVICE1_KEY));
    CU_ASSERT_PTR_NOT_NULL(hpb_list_subscriptions_find(subscriptions, SERVICE2_KEY));
    CU_ASSERT_PTR_NOT_NULL(hpb_list_subscriptions_find(subscriptions, SERVICE3_KEY));
    CU_ASSERT_PTR_NULL(hpb_list_subscriptions_find(subscriptions, NON_EXISTENT_KEY));

    // Test element removal
    hpb_list_subscriptions_remove(subscriptions, SERVICE3_KEY);
    linked_list_iterator_reset(it);
    aux_subscr = (HpbSubscription *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->manager_id, MANAGER_ID1, HPB_ID_BYTE_SIZE);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->service_name, SERVICE1_NAME, SERVICE1_SIZE);
    linked_list_iterator_advance(it);
    aux_subscr = (HpbSubscription *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->manager_id, MANAGER_ID2, HPB_ID_BYTE_SIZE);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->service_name, SERVICE2_NAME, SERVICE2_SIZE);
    CU_ASSERT(subscriptions->size == 2);

    // Test non-existent element removal
    hpb_list_subscriptions_remove(subscriptions, NON_EXISTENT_KEY);
    CU_ASSERT(subscriptions->size == 2);

    // Test element removal
    hpb_list_subscriptions_remove(subscriptions, SERVICE2_KEY);
    linked_list_iterator_reset(it);
    aux_subscr = (HpbSubscription *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_subscr->manager_id, MANAGER_ID1, HPB_ID_BYTE_SIZE);
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

}
