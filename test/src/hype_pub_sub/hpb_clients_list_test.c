#include "hpb_clients_list_test.h"
#include "hpb_test_utils.h"


static HLByte CLIENT1_HYPE_ID[] = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11\x12";
static HLByte CLIENT2_HYPE_ID[] = "\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11";
static HLByte CLIENT3_HYPE_ID[] = "\x11\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10";
static HLByte CLIENT4_HYPE_ID[] = "\x10\x11\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09";
static HLByte NON_EXISTENT_CLIENT_HYPE_ID[] = "\x16\x11\x12\x01\x12\x03\x04\x05\x06\x07\x08\x09";

void hpb_list_clients_test()
{
    HypeInstance *instance1 = hpb_test_utils_get_instance_from_id(CLIENT1_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    HypeInstance *instance2 = hpb_test_utils_get_instance_from_id(CLIENT2_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    HypeInstance *instance3 = hpb_test_utils_get_instance_from_id(CLIENT3_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    HypeInstance *instance4 = hpb_test_utils_get_instance_from_id(CLIENT4_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    HypeInstance *non_existent_instance = hpb_test_utils_get_instance_from_id(NON_EXISTENT_CLIENT_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);

    // Test the creation of a client's list
    HpbClient *aux_cl;
    HpbClientsList *clients = hpb_list_clients_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(clients);
    CU_ASSERT_PTR_NULL(clients->head);
    CU_ASSERT(clients->size == 0);

    // Add 4 clients to the list
    hpb_list_clients_add(clients, instance3);
    hpb_list_clients_add(clients, instance2);
    hpb_list_clients_add(clients, instance4);
    hpb_list_clients_add(clients, instance1);

    // Validate that the clients are inserted in the right order
    LinkedListIterator *it = linked_list_iterator_create(clients);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->hype_instance->identifier->data, CLIENT3_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->hype_instance->identifier->data, CLIENT2_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->hype_instance->identifier->data, CLIENT4_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->hype_instance->identifier->data, CLIENT1_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    CU_ASSERT(clients->size == 4);

    // Remove the client which is the header of the list and validate
    // that the list is correctly modified
    hpb_list_clients_remove(clients, instance3);
    linked_list_iterator_reset(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->hype_instance->identifier->data, CLIENT2_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->hype_instance->identifier->data, CLIENT4_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->hype_instance->identifier->data, CLIENT1_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    CU_ASSERT(clients->size == 3);

    // Remove client that was already removed and validate that nothing
    // happens
    hpb_list_clients_remove(clients, instance3);
    CU_ASSERT(clients->size == 3);

    // Remove another client and validate that the list is correctly
    // modified
    hpb_list_clients_remove(clients, instance4);
    linked_list_iterator_reset(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->hype_instance->identifier->data, CLIENT2_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->hype_instance->identifier->data, CLIENT1_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    CU_ASSERT(clients->size == 2);

    // Remove another client and validate that the list is correctly
    // modified
    hpb_list_clients_remove(clients, instance1);
    linked_list_iterator_reset(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->hype_instance->identifier->data, CLIENT2_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    CU_ASSERT(clients->size == 1);

    // Remove last client of the list
    hpb_list_clients_remove(clients, instance2);
    linked_list_iterator_reset(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_PTR_NULL(aux_cl);
    CU_ASSERT(clients->size == 0);

    // Add a client that was previously removed
    hpb_list_clients_add(clients, instance4);
    linked_list_iterator_reset(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->hype_instance->identifier->data, CLIENT4_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    CU_ASSERT(clients->size == 1);

    // Add all 4 new clients again. Client 4 was already inserted so
    // we validate that it is not duplicated.
    hpb_list_clients_add(clients, instance1);
    hpb_list_clients_add(clients, instance2);
    hpb_list_clients_add(clients, instance3);
    hpb_list_clients_add(clients, instance4);
    linked_list_iterator_reset(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->hype_instance->identifier->data, CLIENT4_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->hype_instance->identifier->data, CLIENT1_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->hype_instance->identifier->data, CLIENT2_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->hype_instance->identifier->data, CLIENT3_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    CU_ASSERT(clients->size == 4);

    // Test find against a non-existent ID
    aux_cl = hpb_list_clients_find(clients, non_existent_instance);
    CU_ASSERT_PTR_NULL(aux_cl);

    // Test find against a existent IDs. Validate client's IDs and keys.
    HLByte CLIENT_KEY3[] = "\x9a\xc1\xb0\x41\x5e\x0a\x97\x73\x8c\x57\xe7\xe6\x3f\x68\x50\xab\x21\xe4\x7e\xb4";
    HLByte CLIENT_KEY4[] = "\x44\x20\x01\xf9\x64\xd9\xfe\x34\x9a\x5f\x30\x8a\xb1\x41\x15\x0e\x05\x5b\xe5\x46";
    aux_cl = hpb_list_clients_find(clients, instance3);
    CU_ASSERT_PTR_NOT_NULL(aux_cl);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->hype_instance->identifier->data, CLIENT3_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->key, CLIENT_KEY3, SHA1_BLOCK_SIZE);
    aux_cl = hpb_list_clients_find(clients, instance4);
    CU_ASSERT_PTR_NOT_NULL(aux_cl);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->hype_instance->identifier->data, CLIENT4_HYPE_ID, HPB_UTILS_CLIENT_ID_TEST_SIZE);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->key, CLIENT_KEY4, SHA1_BLOCK_SIZE);

    // Test the destruction of the client's list
    linked_list_iterator_destroy(&it);
    hpb_list_clients_destroy(&clients);
    CU_ASSERT_PTR_NULL(clients);

    // Clear heap memory
    hype_instance_release(instance1);
    hype_instance_release(instance2);
    hype_instance_release(instance3);
    hype_instance_release(instance4);
    hype_instance_release(non_existent_instance);
}
