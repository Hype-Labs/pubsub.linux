
#include "hype_pub_sub/service_manager.h"

ServiceManager *hpb_service_manager_create(byte service_key[SHA1_BLOCK_SIZE])
{
    ServiceManager *servMan = (ServiceManager*) malloc(sizeof(ServiceManager));
    memcpy(servMan->service_key, service_key, SHA1_BLOCK_SIZE * sizeof(byte));

    servMan->subscribers = hpb_list_clients_create();

    return servMan;
}

int hpb_service_manager_add_subscriber(ServiceManager *serv_man, byte client_id[])
{
    if(serv_man == NULL)
        return -1;

    hpb_list_clients_add(serv_man->subscribers, client_id);
    return 0;
}

int hpb_service_manager_remove_subscriber(ServiceManager *serv_man, byte client_id[])
{
    if(serv_man == NULL)
        return -1;

    hpb_list_clients_remove(serv_man->subscribers, client_id);
    return 0;
}

void hpb_service_manager_destroy(ServiceManager **serv_man)
{
    if((*serv_man) == NULL)
        return;

    hpb_list_clients_destroy(&((*serv_man)->subscribers));
    free(*serv_man);
    (*serv_man) = NULL;
}
