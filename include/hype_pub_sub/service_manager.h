
#ifndef HYPE_PUB_SUB_SERVICE_MANAGER_H_INCLUDED_
#define HYPE_PUB_SUB_SERVICE_MANAGER_H_INCLUDED_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "subscriber_list.h"
#include "constants.h"
#include "sha/sha1.h"

/**
 * @brief
 */
typedef struct ServiceManager_
{
    byte service_key[SHA1_BLOCK_SIZE]; /**< Key of the managed service. */
    LinkedListElement* subscribers; /**< Linked list with the subscribers of the service. */
} ServiceManager;

ServiceManager* hype_pub_sub_service_manager_create(byte service_key[SHA1_BLOCK_SIZE]);

int hype_pub_sub_service_manager_add_subscriber(ServiceManager* serv_man, byte subscriber_id[HYPE_ID_BYTE_SIZE]);

int hype_pub_sub_service_manager_remove_subscriber(ServiceManager* serv_man, byte subscriber_id[HYPE_ID_BYTE_SIZE]);

void hype_pub_sub_service_manager_destroy(ServiceManager* serv_man);

#endif /* HYPE_PUB_SUB_SERVICE_MANAGER_H_INCLUDED_ */
