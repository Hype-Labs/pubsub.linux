#include<stdio.h>
#include<string.h>

#include "hype_pub_sub/hype_pub_sub.h"
#include "hype_pub_sub/cmd_interface.h"

bool parse_user_arguments(int n_args, char *args[], HypePubSub *hpb);

int main()
{
    HypePubSub *hpb = hpb_create();
    // TODO: Hype Start

    hpb_cmd_interface_print_header();
    while(true)
    {
        printf("> ");
        size_t user_input_size = 1000;
        char user_input[user_input_size];
        fgets(user_input, user_input_size, stdin);

        // Remove \n read with getline()
        user_input[strcspn(user_input, "\n")] = '\0';

        // Simulate original 'argv' array which contains the name of the program to be executed in the first index.
        char sim_argv[user_input_size + strlen(HPB_CMD_INTERFACE_INIT_ARG)];
        strcpy(sim_argv, HPB_CMD_INTERFACE_INIT_ARG);
        strcat(sim_argv, user_input);

        char *args[HPB_CMD_INTERFACE_MAX_ARGS];
        int n_args = hpb_cmd_interface_arg_split(args, sim_argv, HPB_CMD_INTERFACE_ARG_DELIM);

        bool is_to_quit = parse_user_arguments(n_args, args, hpb);

        if(is_to_quit)
            break;
    }

    // TODO: Hype Stop
    hpb_destroy(&hpb);
}

bool parse_user_arguments(int n_args, char *args[], HypePubSub *hpb)
{
    int long_index =0;
    int opt = 0;
    optind = 0;

    while((opt = getopt_long_only(n_args, args,"", hpb_cmd_interface_long_options, &long_index)) != -1)
    {
        switch (opt)
        {
            case 's' :
                hpb_cmd_interface_subscribe(hpb, optarg);
                break;
            case 'u' :
                hpb_cmd_interface_unsubscribe(hpb, optarg);
                break;
            case 'p' :
                hpb_cmd_interface_publish(hpb, optarg);
                break;
            case 'i' :
                hpb_cmd_interface_print_own_id(hpb);
                break;
            case 'd' :
                hpb_cmd_interface_print_hype_devices(hpb);
                break;
            case 'm' :
                hpb_cmd_interface_print_managed_services(hpb);
                break;
            case 'n' :
                hpb_cmd_interface_print_subscriptions(hpb);
                break;
            case 'h' :
                hpb_cmd_interface_print_helper();
                break;
            case 'q' :
                return true;
            default:
                hpb_cmd_interface_print_helper();
        }
    }
    return false;
}
