
#ifndef HPB_CMD_INTERFACE_H_INCLUDED_
#define HPB_CMD_INTERFACE_H_INCLUDED_

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

#include "cmd_args.h"
#include "hype_pub_sub.h"

#define HPB_CMD_INTERFACE_MAX_ARGS 30
#define HPB_CMD_INTERFACE_ARG_DELIM " "
#define HPB_CMD_INTERFACE_INIT_ARG "HypePubSub "

#define HPB_CMD_INTERFACE_SUBSCRIBE "subscribe"
#define HPB_CMD_INTERFACE_UNSUBSCRIBE "unsubscribe"
#define HPB_CMD_INTERFACE_PUBLISH "publish"
#define HPB_CMD_INTERFACE_PRINT_OWN_ID "print-own-id"
#define HPB_CMD_INTERFACE_PRINT_HYPE_DEVICES "print-hype-devices"
#define HPB_CMD_INTERFACE_PRINT_MANAGED_SERVICES "print-managed-services"
#define HPB_CMD_INTERFACE_PRINT_SUBSCRIPTIONS "print-subscriptions"
#define HPB_CMD_INTERFACE_HELP "help"
#define HPB_CMD_INTERFACE_QUIT "quit"

static struct option hpb_cmd_interface_long_options[] =
{
    {HPB_CMD_INTERFACE_SUBSCRIBE, required_argument, NULL, 's'},
    {HPB_CMD_INTERFACE_UNSUBSCRIBE, required_argument, NULL, 'u'},
    {HPB_CMD_INTERFACE_PUBLISH, required_argument, NULL, 'p'},
    {HPB_CMD_INTERFACE_PRINT_OWN_ID, no_argument, NULL, 'i'},
    {HPB_CMD_INTERFACE_PRINT_HYPE_DEVICES, no_argument, NULL, 'd'},
    {HPB_CMD_INTERFACE_PRINT_MANAGED_SERVICES, no_argument, NULL, 'm'},
    {HPB_CMD_INTERFACE_PRINT_SUBSCRIPTIONS, no_argument, NULL, 'n'},
    {HPB_CMD_INTERFACE_HELP, no_argument, NULL, 'h'},
    {HPB_CMD_INTERFACE_QUIT, no_argument, NULL, 'q'}
};

void hpb_cmd_interface_subscribe(HypePubSub *hpb, char* service_name);

void hpb_cmd_interface_unsubscribe(HypePubSub *hpb, char *service_name);

void hpb_cmd_interface_publish(HypePubSub *hpb, char* service_name);

void hpb_cmd_interface_print_own_id(HypePubSub *hpb);

void hpb_cmd_interface_print_hype_devices(HypePubSub *hpb);

void hpb_cmd_interface_print_managed_services(HypePubSub *hpb);

void hpb_cmd_interface_print_subscriptions(HypePubSub *hpb);

void hpb_cmd_interface_print_helper();

void hpb_cmd_interface_print_invalid_option();

void hpb_cmd_interface_print_header();

void hpb_cmd_interface_print_client_list(ListClients *lst_cl);

int hpb_cmd_interface_arg_split(char *result[], char *str_to_split, const char *delim);

#endif /* HPB_CMD_INTERFACE_H_INCLUDED_ */
