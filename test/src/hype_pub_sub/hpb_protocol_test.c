#include "hpb_protocol_test.h"

static int CLIENT_HYPE_ID_SIZE = 12;

void hpb_protocol_test()
{
    hpb_destroy(); // Clears the hpb singleton to run the tests from a clean state

    hpb_protocol_test_build_subscribe_msg();
    hpb_protocol_test_build_unsubscribe_msg();
    hpb_protocol_test_build_publish_msg();
    hpb_protocol_test_build_info_msg();
    hpb_protocol_test_receiving_msg();
}

void hpb_protocol_test_build_subscribe_msg()
{
    HLByte *packet;
    size_t packet_size;
    HLByte SERVICE_KEY1[] = "\x9a\xc1\xb0\x41\x5e\x0a\x97\x73\x8c\x57\xe7\xe6\x3f\x68\x50\xab\x21\xe4\x7e\xb4";
    HLByte SERVICE_KEY2[] = "\xe4\x9a\xa7\x79\x2c\xf4\xfd\x09\x6c\x10\x3f\x4b\xa4\x63\xe2\x7b\x91\x60\x9e\x6b";

    packet_size = hpb_protocol_build_subscribe_msg(SERVICE_KEY1, &packet);
    CU_ASSERT_EQUAL(packet_size, 21)
    CU_ASSERT(packet[0] == (HLByte) SUBSCRIBE_SERVICE);
    CU_ASSERT(memcmp(packet + MESSAGE_TYPE_BYTE_SIZE, SERVICE_KEY1, SHA1_BLOCK_SIZE) == 0);
    free(packet);

    packet_size = hpb_protocol_build_subscribe_msg(SERVICE_KEY2, &packet);
    CU_ASSERT_EQUAL(packet_size, 21)
    CU_ASSERT(packet[0] == (HLByte) SUBSCRIBE_SERVICE);
    CU_ASSERT(memcmp(packet + MESSAGE_TYPE_BYTE_SIZE, SERVICE_KEY2, SHA1_BLOCK_SIZE) == 0);
    free(packet);
}

void hpb_protocol_test_build_unsubscribe_msg()
{
    HLByte *packet;
    size_t packet_size;
    HLByte SERVICE_KEY1[] = "\x05\xeb\x63\x7c\xbd\x3f\x33\x69\x1d\x74\x3c\x2a\x39\xaf\xee\xda\x5e\xc9\x45\xad";
    HLByte SERVICE_KEY2[] = "\xf6\xcb\x6d\x9d\xb0\x98\x91\x9b\x2d\x39\x55\x11\x41\xc5\xcb\xe7\x67\xb5\x06\xd6";

    packet_size = hpb_protocol_build_unsubscribe_msg(SERVICE_KEY1, &packet);
    CU_ASSERT_EQUAL(packet_size, 21)
    CU_ASSERT(packet[0] == (HLByte) UNSUBSCRIBE_SERVICE);
    CU_ASSERT(memcmp(packet + MESSAGE_TYPE_BYTE_SIZE, SERVICE_KEY1, SHA1_BLOCK_SIZE) == 0);
    free(packet);

    packet_size = hpb_protocol_build_unsubscribe_msg(SERVICE_KEY2, &packet);
    CU_ASSERT_EQUAL(packet_size, 21)
    CU_ASSERT(packet[0] == (HLByte) UNSUBSCRIBE_SERVICE);
    CU_ASSERT(memcmp(packet + MESSAGE_TYPE_BYTE_SIZE, SERVICE_KEY2, SHA1_BLOCK_SIZE) == 0);
    free(packet);
}

void hpb_protocol_test_build_publish_msg()
{
    HLByte *packet;
    size_t packet_size;
    int offset = 0;
    HLByte SERVICE_KEY1[] = "\x05\xeb\x63\x7c\xbd\x3f\x33\x69\x1d\x74\x3c\x2a\x39\xaf\xee\xda\x5e\xc9\x45\xad";
    HLByte MSG1[] = "HelloHypeWorld";
    size_t MSG1_SIZE = 14;
    HLByte SERVICE_KEY2[] = "\xf6\xcb\x6d\x9d\xb0\x98\x91\x9b\x2d\x39\x55\x11\x41\xc5\xcb\xe7\x67\xb5\x06\xd6";
    HLByte MSG2[] = "HypePubSubApp";
    size_t MSG2_SIZE = 13;

    packet_size = hpb_protocol_build_publish_msg(SERVICE_KEY1, (char*) MSG1, MSG1_SIZE, &packet);
    CU_ASSERT_EQUAL(packet_size, 35)
    CU_ASSERT(packet[0] == (HLByte) PUBLISH);
    offset = MESSAGE_TYPE_BYTE_SIZE;
    CU_ASSERT(memcmp(packet + offset, SERVICE_KEY1, SHA1_BLOCK_SIZE) == 0);
    offset += SHA1_BLOCK_SIZE;
    CU_ASSERT(memcmp(packet + offset, MSG1, MSG1_SIZE) == 0);
    free(packet);

    packet_size = hpb_protocol_build_publish_msg(SERVICE_KEY2, (char*) MSG2, MSG2_SIZE, &packet);
    CU_ASSERT_EQUAL(packet_size, 34)
    CU_ASSERT(packet[0] == (HLByte) PUBLISH);
    offset = MESSAGE_TYPE_BYTE_SIZE;
    CU_ASSERT(memcmp(packet + offset, SERVICE_KEY2, SHA1_BLOCK_SIZE) == 0);
    offset += SHA1_BLOCK_SIZE;
    CU_ASSERT(memcmp(packet + offset, MSG2, MSG2_SIZE) == 0);
    free(packet);
}

void hpb_protocol_test_build_info_msg()
{
    HLByte *packet;
    size_t packet_size;
    int offset = 0;
    HLByte SERVICE_KEY1[] = "\x05\xeb\x63\x7c\xbd\x3f\x33\x69\x1d\x74\x3c\x2a\x39\xaf\xee\xda\x5e\xc9\x45\xad";
    HLByte MSG1[] = "Info-HelloHypeWorld";
    size_t MSG1_SIZE = 19;
    HLByte SERVICE_KEY2[] = "\xf6\xcb\x6d\x9d\xb0\x98\x91\x9b\x2d\x39\x55\x11\x41\xc5\xcb\xe7\x67\xb5\x06\xd6";
    HLByte MSG2[] = "Info-HypePubSubApp";
    size_t MSG2_SIZE = 18;

    packet_size = hpb_protocol_build_info_msg(SERVICE_KEY1, (char*) MSG1, MSG1_SIZE, &packet);
    CU_ASSERT_EQUAL(packet_size, 40)
    CU_ASSERT(packet[0] == (HLByte) INFO);
    offset = MESSAGE_TYPE_BYTE_SIZE;
    CU_ASSERT(memcmp(packet + offset, SERVICE_KEY1, SHA1_BLOCK_SIZE) == 0);
    offset += SHA1_BLOCK_SIZE;
    CU_ASSERT(memcmp(packet + offset, MSG1, MSG1_SIZE) == 0);
    free(packet);

    packet_size = hpb_protocol_build_info_msg(SERVICE_KEY2, (char*) MSG2, MSG2_SIZE, &packet);
    CU_ASSERT_EQUAL(packet_size, 39)
    CU_ASSERT(packet[0] == (HLByte) INFO);
    offset = MESSAGE_TYPE_BYTE_SIZE;
    CU_ASSERT(memcmp(packet + offset, SERVICE_KEY2, SHA1_BLOCK_SIZE) == 0);
    offset += SHA1_BLOCK_SIZE;
    CU_ASSERT(memcmp(packet + offset, MSG2, MSG2_SIZE) == 0);
    free(packet);
}


void hpb_protocol_test_receiving_msg()
{
    HLByte *packet;
    size_t packet_size;
    HLByte SERVICE_KEY[] = "\x9a\xc1\xb0\x41\x5e\x0a\x97\x73\x8c\x57\xe7\xe6\x3f\x68\x50\xab\x21\xe4\x7e\xb4";
    HLByte MSG[] = "HelloHypeWorld";
    size_t MSG_SIZE = 14;
    HypeBuffer *client1_buffer_id = hype_buffer_create_from("\x85\xa9\xd4\xc4\xde\xd2\x87\x75\x0f\xc0\xed\x32", 12);
    HypeInstance *instance1 = hype_instance_create(client1_buffer_id, NULL, false);

    packet_size = hpb_protocol_build_subscribe_msg(SERVICE_KEY, &packet);
    CU_ASSERT(hpb_protocol_receive_msg(instance1, packet, packet_size) == SUBSCRIBE_SERVICE);
    free(packet);

    packet_size = hpb_protocol_build_unsubscribe_msg(SERVICE_KEY, &packet);
    CU_ASSERT(hpb_protocol_receive_msg(instance1, packet, packet_size) == UNSUBSCRIBE_SERVICE);
    free(packet);

    packet_size = hpb_protocol_build_publish_msg(SERVICE_KEY, (char*) MSG, MSG_SIZE, &packet);
    CU_ASSERT(hpb_protocol_receive_msg(instance1, packet, packet_size) == PUBLISH);
    free(packet);

    packet_size = hpb_protocol_build_info_msg(SERVICE_KEY, MSG, MSG_SIZE, &packet);
    CU_ASSERT(hpb_protocol_receive_msg(instance1, packet, packet_size) == INFO);
    free(packet);

    hype_instance_release(instance1);
    hype_buffer_release(client1_buffer_id);
}
