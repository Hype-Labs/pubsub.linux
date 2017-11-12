#include<stdio.h>
#include<string.h>

#include "hype_pub_sub/hype_pub_sub.h"
#include "hype_pub_sub/cmd_interface.h"

int main()
{
    HypePubSub *hpb = hpb_create();
    // Hype Start

    hpb_cmd_interface_print_header();
    while(true){
        char user_option[1000];
        scanf("%s", user_option);

        if(strcmp(user_option, HPB_CMD_INTERFACE_SUBSCRIBE) == 0)
            hpb_cmd_interface_subscribe(hpb);
        else if(strcmp(user_option, HPB_CMD_INTERFACE_UNSUBSCRIBE) == 0)
            hpb_cmd_interface_unsubscribe(hpb);
        else if(strcmp(user_option, HPB_CMD_INTERFACE_PUBLISH) == 0)
            hpb_cmd_interface_publish(hpb);
        else if(strcmp(user_option, HPB_CMD_INTERFACE_PRINT_OWN_ID) == 0)
            hpb_cmd_interface_print_own_id(hpb);
        else if(strcmp(user_option, HPB_CMD_INTERFACE_PRINT_HYPE_DEVICES) == 0)
            hpb_cmd_interface_print_hype_devices(hpb);
        else if(strcmp(user_option, HPB_CMD_INTERFACE_PRINT_MANAGED_SERVICES) == 0)
            hpb_cmd_interface_print_managed_services(hpb);
        else if(strcmp(user_option, HPB_CMD_INTERFACE_PRINT_SUBSCRIPTIONS) == 0)
            hpb_cmd_interface_print_subscriptions(hpb);
        else if(strcmp(user_option, HPB_CMD_INTERFACE_PRINT_SERVICE_MANAGER) == 0)
            hpb_cmd_interface_print_service_manager(hpb);
        else if(strcmp(user_option, HPB_CMD_INTERFACE_HELP) == 0)
            hpb_cmd_interface_print_helper();
        else if(strcmp(user_option, HPB_CMD_INTERFACE_QUIT) == 0)
            break;
        else
            hpb_cmd_interface_print_invalid_option();
    }

    // Hype Stop
    hpb_destroy(&hpb);
}
