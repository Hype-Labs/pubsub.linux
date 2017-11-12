
#ifndef HPB_CMD_INTERFACE_H_INCLUDED_
#define HPB_CMD_INTERFACE_H_INCLUDED_

#include <stdio.h>

#include "hype_pub_sub.h"

#define HPB_CMD_INTERFACE_SUBSCRIBE "-subs"
#define HPB_CMD_INTERFACE_UNSUBSCRIBE "-unsubs"
#define HPB_CMD_INTERFACE_PUBLISH "-pub"
#define HPB_CMD_INTERFACE_PRINT_OWN_ID "-id"
#define HPB_CMD_INTERFACE_PRINT_HYPE_DEVICES "-hype_devices"
#define HPB_CMD_INTERFACE_PRINT_MANAGED_SERVICES "-managed_services"
#define HPB_CMD_INTERFACE_PRINT_SUBSCRIPTIONS "-subscriptions"
#define HPB_CMD_INTERFACE_PRINT_SERVICE_MANAGER "-service_manager"
#define HPB_CMD_INTERFACE_HELP "-h"
#define HPB_CMD_INTERFACE_QUIT "-q"

void hpb_cmd_interface_subscribe(HypePubSub *hpb);

void hpb_cmd_interface_unsubscribe(HypePubSub *hpb);

void hpb_cmd_interface_publish(HypePubSub *hpb);

void hpb_cmd_interface_print_own_id(HypePubSub *hpb);

void hpb_cmd_interface_print_hype_devices(HypePubSub *hpb);

void hpb_cmd_interface_print_managed_services(HypePubSub *hpb);

void hpb_cmd_interface_print_subscriptions(HypePubSub *hpb);

void hpb_cmd_interface_print_service_manager(HypePubSub *hpb);

void hpb_cmd_interface_print_helper();

void hpb_cmd_interface_print_invalid_option();

void hpb_cmd_interface_print_header();

#endif /* HPB_CMD_INTERFACE_H_INCLUDED_ */
