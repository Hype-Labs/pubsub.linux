
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
    byte type = (byte) SUBSCRIBE_SERVICE;
    PacketField msg_type_field = {&type, MESSAGE_TYPE_BYTE_SIZE };
    PacketField ser_key_field = {service_key, SHA1_BLOCK_SIZE };
    size_t n_fields = 2;

    byte* packet = hype_pub_sub_protocol_build_packet(n_fields, &msg_type_field, &ser_key_field) ;

    print_packet(packet, MESSAGE_TYPE_BYTE_SIZE+SHA1_BLOCK_SIZE);
    // TODO: msg memory must freed
    return 0;
}

int hype_pub_sub_protocol_send_unsubscribe_msg(byte service_key[], byte dest_network_id[])
{
    byte type = (byte) UNSUBSCRIBE_SERVICE;
    PacketField msg_type_field = {&type, MESSAGE_TYPE_BYTE_SIZE };
    PacketField ser_key_field = {service_key, SHA1_BLOCK_SIZE };
    size_t n_fields = 2;

    byte* packet = hype_pub_sub_protocol_build_packet(n_fields, &msg_type_field, &ser_key_field) ;

    print_packet(packet, MESSAGE_TYPE_BYTE_SIZE+SHA1_BLOCK_SIZE);
    // TODO: msg memory must freed
    return 0;
}

int hype_pub_sub_protocol_send_publish_msg(byte service_key[], byte dest_network_id[], char *msg, size_t msg_length)
{
    byte type = (byte) PUBLISH;
    PacketField msg_type_field = {&type, MESSAGE_TYPE_BYTE_SIZE };
    PacketField ser_key_field = {service_key, SHA1_BLOCK_SIZE };
    PacketField msg_field = {(byte *) msg, msg_length };
    size_t n_fields = 3;

    byte* packet = hype_pub_sub_protocol_build_packet(n_fields, &msg_type_field, &ser_key_field, &msg_field) ;

    print_packet(packet, MESSAGE_TYPE_BYTE_SIZE+SHA1_BLOCK_SIZE+msg_length);
    // TODO: msg memory must freed
    return 0;
}

int hype_pub_sub_protocol_send_info_msg(byte service_key[], byte dest_network_id[], char *msg, size_t msg_length)
{
    byte type = (byte) INFO;
    PacketField msg_type_field = {&type, MESSAGE_TYPE_BYTE_SIZE };
    PacketField ser_key_field = {service_key, SHA1_BLOCK_SIZE };
    PacketField msg_field = {(byte *) msg, msg_length };
    size_t n_fields = 3;

    byte* packet = hype_pub_sub_protocol_build_packet(n_fields, &msg_type_field, &ser_key_field, &msg_field) ;

    print_packet(packet, MESSAGE_TYPE_BYTE_SIZE+SHA1_BLOCK_SIZE+msg_length);
    // TODO: msg memory must freed
    return 0;
}

byte* hype_pub_sub_protocol_build_packet(int n_fields, ...)
{
    if(n_fields <=0)
        return NULL;

    va_list p_fields;
    size_t p_size = 0;

    va_start(p_fields, n_fields);

    // Get full packet size
    for (int i = 0; i < n_fields; i++)
        p_size += va_arg(p_fields, PacketField*)->size;

    byte *packet = (byte*) malloc(p_size * sizeof(byte));

    va_start(p_fields, n_fields); // re-initialize the list to re-iterate

    // Build packet by joining the fields
    size_t bytes_written = 0;

    for (int i = 0; i < n_fields; i++)
    {
        PacketField *field = va_arg(p_fields, PacketField*);
        memmove(packet+bytes_written, field->data, field->size);
        bytes_written += field->size;
    }

    va_end(p_fields);
    return packet;
}

int hype_pub_sub_protocol_receive_msg(Protocol *protocol, byte origin_network_id[], char *msg, size_t msg_length)
{
    if(msg_length <= 0)
        return -1;

    int m_type = hype_pub_sub_protocol_get_message_type(msg);

    switch (m_type)
    {
        case SUBSCRIBE_SERVICE:
            hype_pub_sub_protocol_receive_subscribe_msg(protocol, origin_network_id, msg, msg_length);
            break;
        case UNSUBSCRIBE_SERVICE:
            hype_pub_sub_protocol_receive_unsubscribe_msg(protocol, origin_network_id, msg, msg_length);
            break;
        case PUBLISH:
            hype_pub_sub_protocol_receive_publish_msg(protocol, origin_network_id, msg, msg_length);
            break;
        case INFO:
            hype_pub_sub_protocol_receive_info_msg(protocol, msg, msg_length);
            break;
        default:
            return -1; // Message type not recognized. Discard
            break;
    }

    return 0;
}

int hype_pub_sub_protocol_receive_subscribe_msg(Protocol *protocol, byte origin_network_id[], char *msg, size_t msg_length)
{
    if(msg_length != (MESSAGE_TYPE_BYTE_SIZE + SHA1_BLOCK_SIZE))
        return -1; // Invalid lenght for a subscribe message

    byte* service_key = (byte *) malloc(SHA1_BLOCK_SIZE * sizeof(char));
    memmove(service_key,msg+MESSAGE_TYPE_BYTE_SIZE, SHA1_BLOCK_SIZE);
    hype_pub_sub_process_subscribe_req(protocol->application, service_key, origin_network_id);
    return 0;
}

int hype_pub_sub_protocol_receive_unsubscribe_msg(Protocol *protocol, byte origin_network_id[], char *msg, size_t msg_length)
{
    if(msg_length != (MESSAGE_TYPE_BYTE_SIZE + SHA1_BLOCK_SIZE))
        return -1; // Invalid lenght for a unsubscribe message

    byte* service_key = (byte *) malloc(SHA1_BLOCK_SIZE * sizeof(char));
    memmove(service_key,msg+MESSAGE_TYPE_BYTE_SIZE, SHA1_BLOCK_SIZE);
    hype_pub_sub_process_unsubscribe_req(protocol->application, service_key, origin_network_id);
    return 0;
}

int hype_pub_sub_protocol_receive_publish_msg(Protocol *protocol, byte origin_network_id[], char *msg, size_t msg_length)
{
    if(msg_length <= (MESSAGE_TYPE_BYTE_SIZE + SHA1_BLOCK_SIZE))
        return -1; // Invalid lenght for a publish message

    byte* service_key = (byte *) malloc(SHA1_BLOCK_SIZE * sizeof(char));
    memmove(service_key,msg+MESSAGE_TYPE_BYTE_SIZE, SHA1_BLOCK_SIZE);
    size_t msg_content_size = msg_length - MESSAGE_TYPE_BYTE_SIZE - SHA1_BLOCK_SIZE;
    char * msg_content = (char *) malloc(msg_content_size* sizeof(char));
    memmove(msg_content, (msg + MESSAGE_TYPE_BYTE_SIZE + SHA1_BLOCK_SIZE), msg_content_size);
    hype_pub_sub_process_publish_req(protocol->application, service_key, msg_content, msg_content_size);
    return 0;
}

int hype_pub_sub_protocol_receive_info_msg(Protocol *protocol, char *msg, size_t msg_length)
{
    if(msg_length <= (MESSAGE_TYPE_BYTE_SIZE + SHA1_BLOCK_SIZE))
        return -1; // Invalid lenght for a info message

    byte* service_key = (byte *) malloc(SHA1_BLOCK_SIZE * sizeof(char));
    memmove(service_key,msg+MESSAGE_TYPE_BYTE_SIZE, SHA1_BLOCK_SIZE);
    size_t msg_content_size = msg_length - MESSAGE_TYPE_BYTE_SIZE - SHA1_BLOCK_SIZE + 1; // +1 to add \0
    char * msg_content = (char *) malloc(msg_content_size* sizeof(char));
    memmove(msg_content, (msg + MESSAGE_TYPE_BYTE_SIZE + SHA1_BLOCK_SIZE), msg_content_size);
    msg_content[msg_content_size-1] = '\0';
    hype_pub_sub_process_info_req(protocol->application, service_key, msg_content, msg_content_size);

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
        return -1; // This should never happen
}

void hype_pub_sub_protocol_destroy(Protocol *protocol)
{
    free(protocol);
}
