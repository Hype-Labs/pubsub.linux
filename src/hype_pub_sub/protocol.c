
#include "hype_pub_sub/protocol.h"

Protocol *hype_pub_sub_protocol_create(HypePubSub *pub_sub)
{
    Protocol *prot = (Protocol *) malloc(sizeof(Protocol));
    return prot;
}

int hype_pub_sub_protocol_send_subscribe_msg(byte service_key[], byte dest_network_id[])
{
    return 0;
}

int hype_pub_sub_protocol_send_unsubscribe_msg(byte service_key[], byte dest_network_id[])
{
    return 0;
}

int hype_pub_sub_protocol_send_publish_msg(byte service_key[], byte dest_network_id[], char *msg, size_t msg_length)
{
    return 0;
}

int hype_pub_sub_protocol_send_change_service_manager_msg(byte service_key[], byte dest_network_id[], byte **subscribers_ids[])
{
    return 0;
}

int hype_pub_sub_protocol_send_info_msg(Protocol *protocol, byte dest_network_id[], char *msg, size_t msg_length)
{
    return 0;
}

int hype_pub_sub_protocol_receive_msg(Protocol *protocol, byte origin_network_id[])
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
    return 0;
}

void hype_pub_sub_protocol_destroy(Protocol *protocol)
{
    free(protocol);
}
