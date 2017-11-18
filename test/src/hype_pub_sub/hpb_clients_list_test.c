#include "hpb_clients_list_test.h"

void hpb_list_clients_test()
{
    HLByte CLIENT_ID1[] = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11\x12";
    HLByte CLIENT_ID2[] = "\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11";
    HLByte CLIENT_ID3[] = "\x11\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10";
    HLByte CLIENT_ID4[] = "\x10\x11\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09";

    // Test the creation of a client's list
    HpbClient *aux_cl;
    HpbClientsList *clients = hpb_list_clients_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(clients);
    CU_ASSERT_PTR_NULL(clients->head);
    CU_ASSERT(clients->size == 0);

    // Add 4 clients to the list
    hpb_list_clients_add(clients, CLIENT_ID3);
    hpb_list_clients_add(clients, CLIENT_ID2);
    hpb_list_clients_add(clients, CLIENT_ID4);
    hpb_list_clients_add(clients, CLIENT_ID1);

    // Validate that the clients are inserted in the right order
    LinkedListIterator *it = linked_list_iterator_create(clients);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID3, HPB_ID_BYTE_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID2, HPB_ID_BYTE_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID4, HPB_ID_BYTE_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID1, HPB_ID_BYTE_SIZE);
    CU_ASSERT(clients->size == 4);

    // Remove the client which is the header of the list and validate
    // that the list is correctly modified
    hpb_list_clients_remove(clients, CLIENT_ID3);
    linked_list_iterator_reset(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID2, HPB_ID_BYTE_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID4, HPB_ID_BYTE_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID1, HPB_ID_BYTE_SIZE);
    CU_ASSERT(clients->size == 3);

    // Remove client that was already removed and validate that nothing
    // happens
    hpb_list_clients_remove(clients, CLIENT_ID3);
    CU_ASSERT(clients->size == 3);

    // Remove another client and validate that the list is correctly
    // modified
    hpb_list_clients_remove(clients, CLIENT_ID4);
    linked_list_iterator_reset(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID2, HPB_ID_BYTE_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID1, HPB_ID_BYTE_SIZE);
    CU_ASSERT(clients->size == 2);

    // Remove another client and validate that the list is correctly
    // modified
    hpb_list_clients_remove(clients, CLIENT_ID1);
    linked_list_iterator_reset(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID2, HPB_ID_BYTE_SIZE);
    CU_ASSERT(clients->size == 1);

    // Remove last client of the list
    hpb_list_clients_remove(clients, CLIENT_ID2);
    linked_list_iterator_reset(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_PTR_NULL(aux_cl);
    CU_ASSERT(clients->size == 0);

    // Add a client that was previously removed
    hpb_list_clients_add(clients, CLIENT_ID4);
    linked_list_iterator_reset(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID4, HPB_ID_BYTE_SIZE);
    CU_ASSERT(clients->size == 1);

    // Add all 4 new clients again. Client 4 was already inserted so
    // we validate that it is not duplicated.
    hpb_list_clients_add(clients, CLIENT_ID1);
    hpb_list_clients_add(clients, CLIENT_ID2);
    hpb_list_clients_add(clients, CLIENT_ID3);
    hpb_list_clients_add(clients, CLIENT_ID4);
    linked_list_iterator_reset(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID4, HPB_ID_BYTE_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID1, HPB_ID_BYTE_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID2, HPB_ID_BYTE_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (HpbClient *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID3, HPB_ID_BYTE_SIZE);
    CU_ASSERT(clients->size == 4);

    // Test find against a non-existent ID
    HLByte NON_EXISTENT_CLIENT_ID[] = "\x16\x11\x12\x01\x12\x03\x04\x05\x06\x07\x08\x09";
    aux_cl = hpb_list_clients_find(clients, NON_EXISTENT_CLIENT_ID);
    CU_ASSERT_PTR_NULL(aux_cl);

    // Test find against a existent IDs. Validate client's IDs and keys.
    HLByte CLIENT_KEY3[] = "\x9a\xc1\xb0\x41\x5e\x0a\x97\x73\x8c\x57\xe7\xe6\x3f\x68\x50\xab\x21\xe4\x7e\xb4";
    HLByte CLIENT_KEY4[] = "\x44\x20\x01\xf9\x64\xd9\xfe\x34\x9a\x5f\x30\x8a\xb1\x41\x15\x0e\x05\x5b\xe5\x46";
    aux_cl = hpb_list_clients_find(clients, CLIENT_ID3);
    CU_ASSERT_PTR_NOT_NULL(aux_cl);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID3, HPB_ID_BYTE_SIZE);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->key, CLIENT_KEY3, SHA1_BLOCK_SIZE);
    aux_cl = hpb_list_clients_find(clients, CLIENT_ID4);
    CU_ASSERT_PTR_NOT_NULL(aux_cl);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID4, HPB_ID_BYTE_SIZE);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->key, CLIENT_KEY4, SHA1_BLOCK_SIZE);

    // Test the destruction of the client's list
    linked_list_iterator_destroy(&it);
    hpb_list_clients_destroy(&clients);
    CU_ASSERT_PTR_NULL(clients);
}
