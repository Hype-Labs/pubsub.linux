#include "hpb_service_manager_test.h"

static HLByte SUBSCRIBER_ID1[] = "\x85\xa9\xd4\xc4\xde\xd2\x87\x75\x0f\xc0\xed\x32";
static HLByte SUBSCRIBER_ID2[] = "\xe7\x79\x34\x6c\x66\x9c\x17\xf4\x34\xc8\xce\x0e";
static size_t CLIENT_HYPE_ID_SIZE = 12;

void hpb_service_manager_test()
{
    HLByte SERVICE1_KEY[] = "\x49\x48\xf4\xe7\x11\x80\x98\x0f\xd7\xb9\x6b\x22\xbe\x91\x54\x20\xe4\xcd\x7e\x2b";
    HLByte SERVICE2_KEY[] = "\x0f\x20\xf1\x8b\x65\xbf\x1e\xa0\xcb\x21\xda\x6f\xd8\xf9\xe5\x5b\x0b\xcb\x54\x84";

    HpbServiceManager *serv1 = hpb_service_manager_create(SERVICE1_KEY);
    HpbServiceManager *serv2 = hpb_service_manager_create(SERVICE2_KEY);

    CU_ASSERT_PTR_NOT_NULL_FATAL(serv1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(serv2);

    CU_ASSERT_NSTRING_EQUAL(serv1->service_key, "\x49\x48\xf4\xe7\x11\x80\x98\x0f\xd7\xb9\x6b\x22\xbe\x91\x54\x20\xe4\xcd\x7e\x2b", SHA1_BLOCK_SIZE);
    CU_ASSERT_NSTRING_EQUAL(serv2->service_key, "\x0f\x20\xf1\x8b\x65\xbf\x1e\xa0\xcb\x21\xda\x6f\xd8\xf9\xe5\x5b\x0b\xcb\x54\x84", SHA1_BLOCK_SIZE);
    CU_ASSERT(serv1->subscribers->size == 0);
    CU_ASSERT_PTR_NULL(serv1->subscribers->head);
    CU_ASSERT(serv2->subscribers->size == 0);
    CU_ASSERT_PTR_NULL(serv2->subscribers->head);

    // Test add_subscriber
    HypeBuffer *client1_buffer_id = hype_buffer_create_from(SUBSCRIBER_ID1, CLIENT_HYPE_ID_SIZE);
    HypeBuffer *client2_buffer_id = hype_buffer_create_from(SUBSCRIBER_ID2, CLIENT_HYPE_ID_SIZE);
    HypeInstance *instance1 = hype_instance_create(client1_buffer_id, NULL, false);
    HypeInstance *instance2 = hype_instance_create(client2_buffer_id, NULL, false);
    hpb_service_manager_add_subscriber(serv1, instance1);
    CU_ASSERT_PTR_NOT_NULL(serv1->subscribers->head);
    CU_ASSERT(serv1->subscribers->size == 1);
    hpb_service_manager_add_subscriber(serv1, instance2);
    CU_ASSERT_FATAL(serv1->subscribers->size == 2);
    CU_ASSERT_NSTRING_EQUAL(((HpbClient *) serv1->subscribers->head->element)->hype_instance->identifier->data, SUBSCRIBER_ID1, CLIENT_HYPE_ID_SIZE);
    CU_ASSERT_NSTRING_EQUAL(((HpbClient *) serv1->subscribers->head->next->element)->hype_instance->identifier->data, SUBSCRIBER_ID2, CLIENT_HYPE_ID_SIZE);

    // Test remove_subscriber
    hpb_service_manager_remove_subscriber(serv1, instance1);
    CU_ASSERT_FATAL(serv1->subscribers->size == 1);
    CU_ASSERT_NSTRING_EQUAL(((HpbClient *) serv1->subscribers->head->element)->hype_instance->identifier->data, SUBSCRIBER_ID2, CLIENT_HYPE_ID_SIZE);
    hpb_service_manager_remove_subscriber(serv1, instance1);
    CU_ASSERT_FATAL(serv1->subscribers->size == 1);
    hpb_service_manager_remove_subscriber(serv1, instance2);
    CU_ASSERT_FATAL(serv1->subscribers->size == 0);
    CU_ASSERT_PTR_NULL(serv1->subscribers->head);

    hpb_service_manager_destroy(&serv1);
    hpb_service_manager_destroy(&serv2);
    CU_ASSERT_PTR_NULL(serv1);
    CU_ASSERT_PTR_NULL(serv2);

    hype_instance_release(instance1);
    hype_instance_release(instance2);
    hype_buffer_release(client1_buffer_id);
    hype_buffer_release(client2_buffer_id);
}
