
#ifndef HYPE_PUB_SUB_SERVICE_MANAGER_H_INCLUDED_
#define HYPE_PUB_SUB_SERVICE_MANAGER_H_INCLUDED_

#include <stdbool.h>
#include <stdlib.h>

#include "constants.h"
#include "../external/include/sha/sha1.h"

/**
 * @brief
 */
typedef struct ServiceManager_
{
    char service_key[SHA1_KEY_BYTE_SIZE]; /**< Key of the managed service. */
    char ** subscribers[HYPE_ID_BYTE_SIZE]; /**< Subscribers of the service. */
    size_t n_subscribers;
} ServiceManager;

/**
 * @brief hype_pub_sub_service_manager_create
 * @param service_key
 * @return
 */
ServiceManager* hype_pub_sub_service_manager_create(char service_key[SHA1_KEY_BYTE_SIZE]);

/**
 * @brief hype_pub_sub_service_manager_add_subscriber
 * @param serv_man
 * @param subscriber_id
 * @return
 */
int hype_pub_sub_service_manager_add_subscriber(ServiceManager* serv_man, char subscriber_id[HYPE_ID_BYTE_SIZE]);

/**
 * @brief hype_pub_sub_service_manager_remove_subscriber
 * @param serv_man
 * @param subscriber_id
 * @return
 */
int hype_pub_sub_service_manager_remove_subscriber(ServiceManager* serv_man, char subscriber_id[HYPE_ID_BYTE_SIZE]);

/**
 * @brief hype_pub_sub_service_manager_is_subscriber
 * @param serv_man
 * @param subscriber_id
 * @return
 */
bool hype_pub_sub_service_manager_is_subscriber(ServiceManager* serv_man, char subscriber_id[HYPE_ID_BYTE_SIZE]);

#endif /* HYPE_PUB_SUB_SERVICE_MANAGER_H_INCLUDED_ */
