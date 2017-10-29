
#ifndef HPB_SERVICE_MANAGER_H_INCLUDED_
#define HPB_SERVICE_MANAGER_H_INCLUDED_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "list_clients.h"
#include "constants.h"
#include "sha/sha1.h"

/**
 * @brief
 */
typedef struct ServiceManager_
{
    byte service_key[SHA1_BLOCK_SIZE]; /**< Key of the managed service. */
    ListClients *subscribers; /**< Linked list with the subscribers of the service. */
} ServiceManager;

ServiceManager *hpb_service_manager_create(byte service_key[SHA1_BLOCK_SIZE]);

int hpb_service_manager_add_subscriber(ServiceManager *serv_man, byte client_id[]);

int hpb_service_manager_remove_subscriber(ServiceManager *serv_man, byte client_id[]);

void hpb_service_manager_destroy(ServiceManager **serv_man);

#endif /* HPB_SERVICE_MANAGER_H_INCLUDED_ */
