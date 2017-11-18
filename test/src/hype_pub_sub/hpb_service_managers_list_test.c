#include "hpb_service_managers_list_test.h"

void hpb_list_service_managers_test()
{
    HLByte SERVICE_KEY1[] = "\xfe\xb5\xc6\xae\x8a\xb9\x7a\xdf\x53\xf8\xbc\x92\xe5\x51\x69\x82\xb6\x20\x0e\xa4";
    HLByte SERVICE_KEY2[] = "\x24\x62\xc4\x5a\x65\xd5\x91\x31\x86\xc9\xb3\x10\xa6\x90\x91\x64\xf5\x5e\xf6\x77";
    HLByte SERVICE_KEY3[] = "\x86\xc9\xb3\x10\xa6\x90\x91\x64\xf5\x5e\xf6\x77\x24\x62\xc4\x5a\x65\xd5\x91\x31";

    // Test the creation of the service managers list
    HpbServiceManager *aux_ser_manv;
    HpbServiceManagersList *serv_managers = hpb_list_service_managers_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(serv_managers);
    CU_ASSERT_PTR_NULL(serv_managers->head);
    CU_ASSERT(serv_managers->size == 0);

    // Add 3 service managers to the list
    hpb_list_service_managers_add(serv_managers, SERVICE_KEY2);
    hpb_list_service_managers_add(serv_managers, SERVICE_KEY1);
    hpb_list_service_managers_add(serv_managers, SERVICE_KEY3);

    // Validate that the service managers are inserted in the right order
    LinkedListIterator *it = linked_list_iterator_create(serv_managers);
    aux_ser_manv = (HpbServiceManager *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_ser_manv->service_key, SERVICE_KEY2, SHA1_BLOCK_SIZE);
    linked_list_iterator_advance(it);
    aux_ser_manv = (HpbServiceManager *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_ser_manv->service_key, SERVICE_KEY1, SHA1_BLOCK_SIZE);
    linked_list_iterator_advance(it);
    aux_ser_manv = (HpbServiceManager *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_ser_manv->service_key, SERVICE_KEY3, SHA1_BLOCK_SIZE);
    CU_ASSERT_PTR_NOT_NULL(serv_managers->head);
    CU_ASSERT(serv_managers->size == 3);

    // Test find against existent and non-existent service keys
    HLByte NON_EXISTENT_KEY[] = "\x86\xc9\xb3\x10\x77\x24\x62\xc4\xa6\x90\x91\x64\xf5\x5e\xf6\x5a\x65\xd5\x91\x31";
    CU_ASSERT_PTR_NOT_NULL(hpb_list_service_managers_find(serv_managers, SERVICE_KEY1));
    CU_ASSERT_PTR_NOT_NULL(hpb_list_service_managers_find(serv_managers, SERVICE_KEY2));
    CU_ASSERT_PTR_NOT_NULL(hpb_list_service_managers_find(serv_managers, SERVICE_KEY3));
    CU_ASSERT_PTR_NULL(hpb_list_service_managers_find(serv_managers, NON_EXISTENT_KEY));

    // Remove a service manager from list and validate that the list is correctly
    // modified
    hpb_list_service_managers_remove(serv_managers, SERVICE_KEY1);
    linked_list_iterator_reset(it);
    aux_ser_manv = (HpbServiceManager *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_ser_manv->service_key, SERVICE_KEY2, SHA1_BLOCK_SIZE);
    linked_list_iterator_advance(it);
    aux_ser_manv = (HpbServiceManager *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_ser_manv->service_key, SERVICE_KEY3, SHA1_BLOCK_SIZE);
    CU_ASSERT(serv_managers->size == 2);

    // Remove the service manager which is the header of the list and validate
    // that the list is correctly modified
    hpb_list_service_managers_remove(serv_managers, SERVICE_KEY2);
    linked_list_iterator_reset(it);
    aux_ser_manv = (HpbServiceManager *) linked_list_iterator_get_element(it);
    CU_ASSERT_NSTRING_EQUAL(aux_ser_manv->service_key, SERVICE_KEY3, SHA1_BLOCK_SIZE);
    CU_ASSERT(serv_managers->size == 1);

    // Remove the last service manager from the list and validate that the list
    // is correctly modified
    hpb_list_service_managers_remove(serv_managers, SERVICE_KEY3);
    CU_ASSERT(serv_managers->size == 0);
    CU_ASSERT_PTR_NULL(serv_managers->head);

    // Test the destruction of the service managers list
    linked_list_iterator_destroy(&it);
    hpb_list_service_managers_destroy(&serv_managers);
    CU_ASSERT_PTR_NULL(serv_managers);
}
