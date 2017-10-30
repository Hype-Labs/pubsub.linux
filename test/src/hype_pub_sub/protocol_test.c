#include "protocol_test.h"

void hpb_protocol_test()
{
    HypePubSub *hpb = hpb_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(hpb);

    Protocol *prtcl = hpb_protocol_create(hpb);
    CU_ASSERT_PTR_NOT_NULL_FATAL(prtcl);

    hpb_protocol_test_sending();
    hpb_protocol_test_receiving(prtcl);

    hpb_destroy(&hpb);
    hpb_protocol_destroy(&prtcl);
    CU_ASSERT_PTR_NULL(prtcl);
}

void hpb_protocol_test_sending()
{
    hpb_protocol_test_sending_subscribe();
    hpb_protocol_test_sending_unsubscribe();
    hpb_protocol_test_sending_publish();
    hpb_protocol_test_sending_info();
    hpb_protocol_test_sending_build_packet();
}

void hpb_protocol_test_sending_subscribe()
{
    byte *packet;
    byte DEST_ID1[] = "\x10\x11\x12\x01\x02\x03\x04\x05\x06\x07\x08\x09";
    byte SERVICE_KEY1[] = "\x9a\xc1\xb0\x41\x5e\x0a\x97\x73\x8c\x57\xe7\xe6\x3f\x68\x50\xab\x21\xe4\x7e\xb4";
    byte DEST_ID2[] = "\x66\xd8\xf2\x20\x6a\x56\xdb\xe9\x91\x23\x3b\xc2";
    byte SERVICE_KEY2[] = "\xe4\x9a\xa7\x79\x2c\xf4\xfd\x09\x6c\x10\x3f\x4b\xa4\x63\xe2\x7b\x91\x60\x9e\x6b";

    packet = hpb_protocol_send_subscribe_msg(SERVICE_KEY1, DEST_ID1);
    CU_ASSERT(packet[0] == (byte) SUBSCRIBE_SERVICE);
    CU_ASSERT(memcmp(packet + MESSAGE_TYPE_BYTE_SIZE, SERVICE_KEY1, SHA1_BLOCK_SIZE) == 0);
    free(packet);

    packet = hpb_protocol_send_subscribe_msg(SERVICE_KEY2, DEST_ID2);
    CU_ASSERT(packet[0] == (byte) SUBSCRIBE_SERVICE);
    CU_ASSERT(memcmp(packet + MESSAGE_TYPE_BYTE_SIZE, SERVICE_KEY2, SHA1_BLOCK_SIZE) == 0);
    free(packet);
}

void hpb_protocol_test_sending_unsubscribe()
{
    byte *packet;
    byte DEST_ID1[] = "\x85\xa9\xd4\xc4\xde\xd2\x87\x75\x0f\xc0\xed\x32";
    byte SERVICE_KEY1[] = "\x05\xeb\x63\x7c\xbd\x3f\x33\x69\x1d\x74\x3c\x2a\x39\xaf\xee\xda\x5e\xc9\x45\xad";
    byte DEST_ID2[] = "\xe7\x79\x34\x6c\x66\x9c\x17\xf4\x34\xc8\xce\x0e";
    byte SERVICE_KEY2[] = "\xf6\xcb\x6d\x9d\xb0\x98\x91\x9b\x2d\x39\x55\x11\x41\xc5\xcb\xe7\x67\xb5\x06\xd6";

    packet = hpb_protocol_send_unsubscribe_msg(SERVICE_KEY1, DEST_ID1);
    CU_ASSERT(packet[0] == (byte) UNSUBSCRIBE_SERVICE);
    CU_ASSERT(memcmp(packet + MESSAGE_TYPE_BYTE_SIZE, SERVICE_KEY1, SHA1_BLOCK_SIZE) == 0);
    free(packet);

    packet = hpb_protocol_send_unsubscribe_msg(SERVICE_KEY2, DEST_ID2);
    CU_ASSERT(packet[0] == (byte) UNSUBSCRIBE_SERVICE);
    CU_ASSERT(memcmp(packet + MESSAGE_TYPE_BYTE_SIZE, SERVICE_KEY2, SHA1_BLOCK_SIZE) == 0);
    free(packet);
}

void hpb_protocol_test_sending_publish()
{
    byte *packet;
    int offset = 0;
    byte DEST_ID1[] = "\x85\xa9\xd4\xc4\xde\xd2\x87\x75\x0f\xc0\xed\x32";
    byte SERVICE_KEY1[] = "\x05\xeb\x63\x7c\xbd\x3f\x33\x69\x1d\x74\x3c\x2a\x39\xaf\xee\xda\x5e\xc9\x45\xad";
    byte MSG1[] = "HelloHypeWorld";
    size_t MSG1_SIZE = 14;
    byte DEST_ID2[] = "\xe7\x79\x34\x6c\x66\x9c\x17\xf4\x34\xc8\xce\x0e";
    byte SERVICE_KEY2[] = "\xf6\xcb\x6d\x9d\xb0\x98\x91\x9b\x2d\x39\x55\x11\x41\xc5\xcb\xe7\x67\xb5\x06\xd6";
    byte MSG2[] = "HypePubSubApp";
    size_t MSG2_SIZE = 13;

    packet = hpb_protocol_send_publish_msg(SERVICE_KEY1, DEST_ID1, (char*) MSG1, MSG1_SIZE);
    CU_ASSERT(packet[0] == (byte) PUBLISH);
    offset = MESSAGE_TYPE_BYTE_SIZE;
    CU_ASSERT(memcmp(packet + offset, SERVICE_KEY1, SHA1_BLOCK_SIZE) == 0);
    offset += SHA1_BLOCK_SIZE;
    CU_ASSERT(memcmp(packet + offset, MSG1, MSG1_SIZE) == 0);
    free(packet);

    packet = hpb_protocol_send_publish_msg(SERVICE_KEY2, DEST_ID2, (char*) MSG2, MSG2_SIZE);
    CU_ASSERT(packet[0] == (byte) PUBLISH);
    offset = MESSAGE_TYPE_BYTE_SIZE;
    CU_ASSERT(memcmp(packet + offset, SERVICE_KEY2, SHA1_BLOCK_SIZE) == 0);
    offset += SHA1_BLOCK_SIZE;
    CU_ASSERT(memcmp(packet + offset, MSG2, MSG2_SIZE) == 0);
    free(packet);
}

void hpb_protocol_test_sending_info()
{
    byte *packet;
    int offset = 0;
    byte DEST_ID1[] = "\x85\xa9\xd4\xc4\xde\xd2\x87\x75\x0f\xc0\xed\x32";
    byte SERVICE_KEY1[] = "\x05\xeb\x63\x7c\xbd\x3f\x33\x69\x1d\x74\x3c\x2a\x39\xaf\xee\xda\x5e\xc9\x45\xad";
    byte MSG1[] = "Info-HelloHypeWorld";
    size_t MSG1_SIZE = 19;
    byte DEST_ID2[] = "\xe7\x79\x34\x6c\x66\x9c\x17\xf4\x34\xc8\xce\x0e";
    byte SERVICE_KEY2[] = "\xf6\xcb\x6d\x9d\xb0\x98\x91\x9b\x2d\x39\x55\x11\x41\xc5\xcb\xe7\x67\xb5\x06\xd6";
    byte MSG2[] = "Info-HypePubSubApp";
    size_t MSG2_SIZE = 18;

    packet = hpb_protocol_send_info_msg(SERVICE_KEY1, DEST_ID1, (char*) MSG1, MSG1_SIZE);
    CU_ASSERT(packet[0] == (byte) INFO);
    offset = MESSAGE_TYPE_BYTE_SIZE;
    CU_ASSERT(memcmp(packet + offset, SERVICE_KEY1, SHA1_BLOCK_SIZE) == 0);
    offset += SHA1_BLOCK_SIZE;
    CU_ASSERT(memcmp(packet + offset, MSG1, MSG1_SIZE) == 0);
    free(packet);

    packet = hpb_protocol_send_info_msg(SERVICE_KEY2, DEST_ID2, (char*) MSG2, MSG2_SIZE);
    CU_ASSERT(packet[0] == (byte) INFO);
    offset = MESSAGE_TYPE_BYTE_SIZE;
    CU_ASSERT(memcmp(packet + offset, SERVICE_KEY2, SHA1_BLOCK_SIZE) == 0);
    offset += SHA1_BLOCK_SIZE;
    CU_ASSERT(memcmp(packet + offset, MSG2, MSG2_SIZE) == 0);
    free(packet);
}

void hpb_protocol_test_sending_build_packet()
{
    byte FIELD1_DATA[] = "field1-hello";
    size_t FIELD1_SIZE = 12;
    PacketField field1 = {FIELD1_DATA, FIELD1_SIZE };

    byte FIELD2_DATA[] = "field2-test";
    size_t FIELD2_SIZE = 11;
    PacketField field2 = {FIELD2_DATA, FIELD2_SIZE };

    byte FIELD3_DATA[] = "field3";
    size_t FIELD3_SIZE = 6;
    PacketField field3 = {FIELD3_DATA, FIELD3_SIZE };

    byte FIELD4_DATA[] = "hypef4-";
    size_t FIELD4_SIZE = 7;
    PacketField field4 = {FIELD4_DATA, FIELD4_SIZE };

    byte *packet = hpb_protocol_build_packet(4, &field1, &field2, &field3, &field4);
    int offset = 0;

    CU_ASSERT(memcmp(packet + offset, FIELD1_DATA, FIELD1_SIZE) == 0);
    offset += FIELD1_SIZE;
    CU_ASSERT(memcmp(packet + offset, FIELD2_DATA, FIELD2_SIZE) == 0);
    offset += FIELD2_SIZE;
    CU_ASSERT(memcmp(packet + offset, FIELD3_DATA, FIELD3_SIZE) == 0);
    offset += FIELD3_SIZE;
    CU_ASSERT(memcmp(packet + offset, FIELD4_DATA, FIELD4_SIZE) == 0);

    free(packet);
}

void hpb_protocol_test_receiving(Protocol *prtcl)
{

}
