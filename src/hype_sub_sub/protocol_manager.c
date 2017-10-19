
#include "HypePubSub/protocol_manager.h"

ProtocolManager *hype_pub_sub_protocol_manager_create(HypePubSub *pub_sub)
{
    return NULL;
}

int hype_pub_sub_protocol_manager_send_subscribe_packet(char service_key[], char dest_network_id[])
{
    return 0;
}

int hype_pub_sub_protocol_manager_send_unsubscribe_packet(char service_key[], char dest_network_id[])
{
    return 0;
}

int hype_pub_sub_protocol_manager_send_publish_packet(char service_key[], char dest_network_id[], char *msg)
{
    return 0;
}

int hype_pub_sub_protocol_manager_send_change_service_manager_packet(char service_key[], char dest_network_id[], char **subscribers_ids[])
{
    return 0;
}

int hype_pub_sub_protocol_manager_send_info_packet(ProtocolManager *protocol, char dest_network_id[], char *string)
{
    return 0;
}

int hype_pub_sub_protocol_manager_receive_msg(ProtocolManager *protocol, char origin_network_id[])
{
    return 0;
}

int hype_pub_sub_protocol_manager_receive_subscribe_packet(ProtocolManager *protocol, char *msg)
{
    return 0;
}

int hype_pub_sub_protocol_manager_receive_unsubscribe_packet(ProtocolManager *protocol, char *msg)
{
    return 0;
}

int hype_pub_sub_protocol_manager_receive_publish_packet(ProtocolManager *protocol, char *msg)
{
    return 0;
}

int hype_pub_sub_protocol_manager_receive_change_service_manager_packet(ProtocolManager *protocol, char *msg)
{
    return 0;
}

int hype_pub_sub_protocol_manager_receive_info_packet(ProtocolManager *protocol, char *msg)
{
    return 0;
}

MessageType hype_pub_sub_protocol_manager_get_message_type(char *msg)
{
    return 0;
}
