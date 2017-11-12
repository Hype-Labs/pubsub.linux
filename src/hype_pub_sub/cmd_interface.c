
#include "hype_pub_sub/cmd_interface.h"

void hpb_cmd_interface_subscribe(HypePubSub *hpb)
{

}

void hpb_cmd_interface_unsubscribe(HypePubSub *hpb)
{

}

void hpb_cmd_interface_publish(HypePubSub *hpb)
{

}

void hpb_cmd_interface_print_own_id(HypePubSub *hpb)
{

}

void hpb_cmd_interface_print_hype_devices(HypePubSub *hpb)
{

}

void hpb_cmd_interface_print_managed_services(HypePubSub *hpb)
{

}

void hpb_cmd_interface_print_subscriptions(HypePubSub *hpb)
{

}

void hpb_cmd_interface_print_service_manager(HypePubSub *hpb)
{

}

void hpb_cmd_interface_print_helper()
{
    printf("The followings options are available:\n");
    printf("\t -> Subscribe service: %s\n" ,HPB_CMD_INTERFACE_SUBSCRIBE);
    printf("\t -> Unsubscribe service: %s\n" ,HPB_CMD_INTERFACE_UNSUBSCRIBE);
    printf("\t -> Publish: %s\n" ,HPB_CMD_INTERFACE_PUBLISH);
    printf("\t -> Print own ID: %s\n" ,HPB_CMD_INTERFACE_PRINT_OWN_ID);
    printf("\t -> Print Hype devices: %s\n" ,HPB_CMD_INTERFACE_PRINT_HYPE_DEVICES);
    printf("\t -> Print managed services: %s\n" ,HPB_CMD_INTERFACE_PRINT_MANAGED_SERVICES);
    printf("\t -> Print subscriptions: %s\n" ,HPB_CMD_INTERFACE_PRINT_SUBSCRIPTIONS);
    printf("\t -> Print service manager: %s\n" ,HPB_CMD_INTERFACE_PRINT_SERVICE_MANAGER);
    printf("\t -> Print helper: %s\n" ,HPB_CMD_INTERFACE_HELP);
    printf("\t -> Quit: %s\n" ,HPB_CMD_INTERFACE_QUIT);
}

void hpb_cmd_interface_print_invalid_option()
{
    printf("Invalid option\n");
}

void hpb_cmd_interface_print_header()
{
    printf("\n");
    printf("####################################\n");
    printf("##          HypePubSub            ##\n");
    printf("####################################\n");
    printf("\n");
}

