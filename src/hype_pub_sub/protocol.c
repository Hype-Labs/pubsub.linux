
#include "hype_pub_sub/protocol.h"


#include "stdio.h"
void print_packet(unsigned char* array, size_t len)
{
    printf("ProtocolPacket:\n");
    for(int i=0; i<len; i++)
        printf("%.2x", array[i]);

    printf("\n");
}

Protocol *hype_pub_sub_protocol_create(HypePubSub *pub_sub)
{
    Protocol *prot = (Protocol *) malloc(sizeof(Protocol));
    prot->application = pub_sub;
    return prot;
}

int hype_pub_sub_protocol_send_subscribe_msg(byte service_key[], byte dest_network_id[])
{
    size_t packet_byte_size = MESSAGE_TYPE_BYTE_SIZE + SHA1_BLOCK_SIZE;
    byte* packet = (byte*) malloc(packet_byte_size * sizeof(char));
    byte msg_type = (byte) SUBSCRIBE_SERVICE;
    memmove(packet, &msg_type, MESSAGE_TYPE_BYTE_SIZE); // set message type
    memmove(packet+MESSAGE_TYPE_BYTE_SIZE, service_key, SHA1_BLOCK_SIZE); // set service key

    print_packet(packet, packet_byte_size);
    // TODO: msg memory must freed
    return 0;
}

int hype_pub_sub_protocol_send_unsubscribe_msg(byte service_key[], byte dest_network_id[])
{
    size_t packet_byte_size = MESSAGE_TYPE_BYTE_SIZE + SHA1_BLOCK_SIZE;
    byte* packet = (byte*) malloc(packet_byte_size * sizeof(char));
    byte msg_type = (byte) UNSUBSCRIBE_SERVICE;
    memmove(packet, &msg_type, MESSAGE_TYPE_BYTE_SIZE); // set message type
    memmove(packet+MESSAGE_TYPE_BYTE_SIZE, service_key, SHA1_BLOCK_SIZE); // set service key

    print_packet(packet, packet_byte_size);
    // TODO: msg memory must freed
    return 0;
}

int hype_pub_sub_protocol_send_publish_msg(byte service_key[], byte dest_network_id[], char *msg, size_t msg_length)
{
    size_t packet_byte_size = MESSAGE_TYPE_BYTE_SIZE + SHA1_BLOCK_SIZE + msg_length;
    byte* packet = (byte*) malloc(packet_byte_size * sizeof(char));
    byte msg_type = (byte) PUBLISH;
    memmove(packet, &msg_type, MESSAGE_TYPE_BYTE_SIZE); // set message type
    memmove(packet+MESSAGE_TYPE_BYTE_SIZE, service_key, SHA1_BLOCK_SIZE); // set service key
    memmove(packet+MESSAGE_TYPE_BYTE_SIZE+SHA1_BLOCK_SIZE, msg, msg_length); // set message

    print_packet(packet, packet_byte_size);
    // TODO: msg memory must freed
    return 0;
}

int hype_pub_sub_protocol_send_info_msg(byte service_key[], byte dest_network_id[], char *msg, size_t msg_length)
{
    size_t packet_byte_size = MESSAGE_TYPE_BYTE_SIZE + SHA1_BLOCK_SIZE + msg_length;
    byte* packet = (byte*) malloc(packet_byte_size * sizeof(char));
    byte msg_type = (byte) INFO;
    memmove(packet, &msg_type, MESSAGE_TYPE_BYTE_SIZE); // set message type
    memmove(packet+MESSAGE_TYPE_BYTE_SIZE, service_key, SHA1_BLOCK_SIZE); // set service key
    memmove(packet+MESSAGE_TYPE_BYTE_SIZE+SHA1_BLOCK_SIZE, msg, msg_length); // set message

    print_packet(packet, packet_byte_size);
    // TODO: msg memory must freed
    return 0;
}

int hype_pub_sub_protocol_receive_msg(Protocol *protocol, byte origin_network_id[], char *msg, size_t msg_length)
{
    return 0;
}

int hype_pub_sub_protocol_receive_subscribe_msg(Protocol *protocol, char *msg)
{
    return 0;
}

int hype_pub_sub_protocol_receive_unsubscribe_msg(Protocol *protocol, char *msg)
{
    return 0;
}

int hype_pub_sub_protocol_receive_publish_msg(Protocol *protocol, char *msg)
{
    return 0;
}

int hype_pub_sub_protocol_receive_change_service_manager_msg(Protocol *protocol, char *msg)
{
    return 0;
}

int hype_pub_sub_protocol_receive_info_msg(Protocol *protocol, char *msg, size_t msg_length)
{
    return 0;
}

MessageType hype_pub_sub_protocol_get_message_type(char *msg)
{
    if(msg[0] == (byte) SUBSCRIBE_SERVICE)
        return SUBSCRIBE_SERVICE;
    else if(msg[0] == (byte) UNSUBSCRIBE_SERVICE)
        return UNSUBSCRIBE_SERVICE;
    else if(msg[0] == (byte) PUBLISH)
        return PUBLISH;
    else if(msg[0] == (byte) INFO)
        return INFO;
    else
        return 0; // This should never happen
}

void hype_pub_sub_protocol_destroy(Protocol *protocol)
{
    free(protocol);
}
