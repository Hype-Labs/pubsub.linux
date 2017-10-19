
#include "hype_pub_sub/protocol.h"

ProtocolManager *hype_pub_sub_protocol_manager_create(HypePubSub *pub_sub)
{
    return NULL;
}

int hype_pub_sub_protocol_manager_send_subscribe_msg(char service_key[], char dest_network_id[])
{
    return 0;
}

int hype_pub_sub_protocol_manager_send_unsubscribe_msg(char service_key[], char dest_network_id[])
{
    return 0;
}

int hype_pub_sub_protocol_manager_send_publish_msg(char service_key[], char dest_network_id[], char *msg)
{
    return 0;
}

int hype_pub_sub_protocol_manager_send_change_service_manager_msg(char service_key[], char dest_network_id[], char **subscribers_ids[])
{
    return 0;
}

int hype_pub_sub_protocol_manager_send_info_msg(ProtocolManager *protocol, char dest_network_id[], char *string)
{
    return 0;
}

int hype_pub_sub_protocol_manager_receive_msg(ProtocolManager *protocol, char origin_network_id[])
{
    return 0;
}

int hype_pub_sub_protocol_manager_receive_subscribe_msg(ProtocolManager *protocol, char *msg)
{
    return 0;
}

int hype_pub_sub_protocol_manager_receive_unsubscribe_msg(ProtocolManager *protocol, char *msg)
{
    return 0;
}

int hype_pub_sub_protocol_manager_receive_publish_msg(ProtocolManager *protocol, char *msg)
{
    return 0;
}

int hype_pub_sub_protocol_manager_receive_change_service_manager_msg(ProtocolManager *protocol, char *msg)
{
    return 0;
}

int hype_pub_sub_protocol_manager_receive_info_msg(ProtocolManager *protocol, char *msg)
{
    return 0;
}

MessageType hype_pub_sub_protocol_manager_get_message_type(char *msg)
{
    return 0;
}
