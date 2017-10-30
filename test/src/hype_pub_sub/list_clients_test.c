#include "list_clients_test.h"

void hype_pub_sub_list_clients_test()
{
    byte CLIENT_ID1[] = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11\x12";
    byte CLIENT_ID2[] = "\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11";
    byte CLIENT_ID3[] = "\x11\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10";
    byte CLIENT_ID4[] = "\x10\x11\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09";

    Client *aux_cl;
    ListClients *clients = hpb_list_clients_create();

    CU_ASSERT_PTR_NOT_NULL_FATAL(clients);
    CU_ASSERT_PTR_NULL(clients->head);
    CU_ASSERT(clients->size == 0);

    //Client *hpb_list_clients_find(ListClients *list_cl, byte client_id[]);

    hpb_list_clients_add(clients, CLIENT_ID3);
    hpb_list_clients_add(clients, CLIENT_ID2);
    hpb_list_clients_add(clients, CLIENT_ID4);
    hpb_list_clients_add(clients, CLIENT_ID1);

    LinkedListIterator *it = linked_list_iterator_create(clients);

    aux_cl = (Client *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID3, HPB_ID_BYTE_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (Client *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID2, HPB_ID_BYTE_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (Client *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID4, HPB_ID_BYTE_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (Client *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID1, HPB_ID_BYTE_SIZE);
    CU_ASSERT(clients->size == 4);

    hpb_list_clients_remove(clients, CLIENT_ID3);
    linked_list_iterator_reset(it);
    aux_cl = (Client *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID2, HPB_ID_BYTE_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (Client *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID4, HPB_ID_BYTE_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (Client *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID1, HPB_ID_BYTE_SIZE);
    CU_ASSERT(clients->size == 3);

    hpb_list_clients_remove(clients, CLIENT_ID3);
    CU_ASSERT(clients->size == 3);

    hpb_list_clients_remove(clients, CLIENT_ID4);
    linked_list_iterator_reset(it);
    aux_cl = (Client *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID2, HPB_ID_BYTE_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (Client *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID1, HPB_ID_BYTE_SIZE);
    CU_ASSERT(clients->size == 2);

    hpb_list_clients_remove(clients, CLIENT_ID1);
    linked_list_iterator_reset(it);
    aux_cl = (Client *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID2, HPB_ID_BYTE_SIZE);
    CU_ASSERT(clients->size == 1);

    hpb_list_clients_remove(clients, CLIENT_ID2);
    linked_list_iterator_reset(it);
    aux_cl = (Client *) linked_list_iterator_get_element(it);
    CU_ASSERT_PTR_NULL(aux_cl);
    CU_ASSERT(clients->size == 0);

    hpb_list_clients_add(clients, CLIENT_ID4);
    linked_list_iterator_reset(it);
    aux_cl = (Client *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID4, HPB_ID_BYTE_SIZE);
    CU_ASSERT(clients->size == 1);

    hpb_list_clients_add(clients, CLIENT_ID1);
    hpb_list_clients_add(clients, CLIENT_ID2);
    hpb_list_clients_add(clients, CLIENT_ID3);
    hpb_list_clients_add(clients, CLIENT_ID4);
    linked_list_iterator_reset(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID4, HPB_ID_BYTE_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (Client *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID1, HPB_ID_BYTE_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (Client *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID2, HPB_ID_BYTE_SIZE);
    linked_list_iterator_advance(it);
    aux_cl = (Client *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_cl->id, CLIENT_ID3, HPB_ID_BYTE_SIZE);
    CU_ASSERT(clients->size == 4);

    hpb_list_clients_destroy(&clients);
    CU_ASSERT_PTR_NULL(clients);
}
