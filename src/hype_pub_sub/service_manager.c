
#include "hype_pub_sub/service_manager.h"

ServiceManager *hype_pub_sub_service_manager_create(byte service_key[SHA1_BLOCK_SIZE])
{
    ServiceManager* servMan = (ServiceManager*) malloc(sizeof(ServiceManager));
    memcpy(servMan->service_key, service_key, SHA1_BLOCK_SIZE * sizeof(byte));

    return servMan;
}

int hype_pub_sub_service_manager_add_subscriber(ServiceManager *serv_man, byte subscriber_id[])
{
    return 0;
}

int hype_pub_sub_service_manager_remove_subscriber(ServiceManager *serv_man, byte subscriber_id[])
{
    return 0;
}

bool hype_pub_sub_service_manager_is_subscriber(ServiceManager *serv_man, byte subscriber_id[])
{
    return 0;
}
