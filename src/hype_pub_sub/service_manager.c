
#include "hype_pub_sub/service_manager.h"

ServiceManager *hype_pub_sub_service_manager_create(byte service_key[SHA1_BLOCK_SIZE])
{
    ServiceManager* servMan = (ServiceManager*) malloc(sizeof(ServiceManager));
    memcpy(servMan->service_key, service_key, SHA1_BLOCK_SIZE * sizeof(byte));

    servMan->subscribers = hype_pub_sub_list_subscribers_create();

    return servMan;
}

int hype_pub_sub_service_manager_add_subscriber(ServiceManager *serv_man, byte subscriber_id[HYPE_ID_BYTE_SIZE])
{
    if(serv_man == NULL)
        return -1;

    hype_pub_sub_list_subscribers_add(serv_man->subscribers, subscriber_id);
    return 0;
}

int hype_pub_sub_service_manager_remove_subscriber(ServiceManager *serv_man, byte subscriber_id[HYPE_ID_BYTE_SIZE])
{
    if(serv_man == NULL)
        return -1;

    hype_pub_sub_list_subscribers_remove(&(serv_man->subscribers), subscriber_id);
    return 0;
}

void hype_pub_sub_service_manager_destroy(ServiceManager *serv_man)
{
    if(serv_man == NULL)
        return;

    hype_pub_sub_list_subscribers_destroy(serv_man->subscribers);
    free(serv_man);
}
