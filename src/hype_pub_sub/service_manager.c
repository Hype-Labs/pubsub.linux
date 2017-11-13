
#include "hype_pub_sub/service_manager.h"

HpbServiceManager *hpb_service_manager_create(HLByte service_key[SHA1_BLOCK_SIZE])
{
    HpbServiceManager *servMan = (HpbServiceManager*) malloc(sizeof(HpbServiceManager));
    memcpy(servMan->service_key, service_key, SHA1_BLOCK_SIZE * sizeof(HLByte));

    servMan->subscribers = hpb_list_clients_create();

    return servMan;
}

int hpb_service_manager_add_subscriber(HpbServiceManager *serv_man, HLByte client_id[])
{
    if(serv_man == NULL)
        return -1;

    hpb_list_clients_add(serv_man->subscribers, client_id);
    return 0;
}

int hpb_service_manager_remove_subscriber(HpbServiceManager *serv_man, HLByte client_id[])
{
    if(serv_man == NULL)
        return -1;

    hpb_list_clients_remove(serv_man->subscribers, client_id);
    return 0;
}

void hpb_service_manager_destroy(HpbServiceManager **serv_man)
{
    if((*serv_man) == NULL)
        return;

    hpb_list_clients_destroy(&((*serv_man)->subscribers));
    free(*serv_man);
    (*serv_man) = NULL;
}
