
#ifndef HPB_SERVICE_MANAGER_H_INCLUDED_
#define HPB_SERVICE_MANAGER_H_INCLUDED_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "hpb_clients_list.h"
#include "hpb_constants.h"
#include "sha/sha1.h"

/**
 * @brief This struct represents a service managed by this HypePubSub application.
 * Each HpbServiceManager associates a given service with a list of subscribers.
 */
typedef struct HpbServiceManager_
{
    HLByte service_key[SHA1_BLOCK_SIZE]; /**< Key of the managed service. */
    HpbClientsList *subscribers; /**< Linked list with the subscribers of the service. */
} HpbServiceManager;

/**
 * @brief Allocates space for a HpbServiceManager struct.
 * @param service_key Service key of the HpbServiceManager to be created.
 * @return Returns a pointer to the created struct or NULL if the space could not be allocated.
 */
HpbServiceManager *hpb_service_manager_create(HLByte service_key[SHA1_BLOCK_SIZE]);

/**
 * @brief Adds a subscriber to a given HpbServiceManager.
 * @param serv_man HpbServiceManager to which the subscriber should be added.
 * @param client_id ID of the subscriber.
 * @return Returns 0 in case of success and -1 otherwise.
 */
int hpb_service_manager_add_subscriber(HpbServiceManager *serv_man, HypeInstance * instance);

/**
 * @brief Removes a subscriber from a given HpbServiceManager.
 * @param serv_man HpbServiceManager from which the subscriber should be removed.
 * @param client_id ID of the subscriber.
 * @return Returns 0 in case of success and -1 otherwise.
 */
int hpb_service_manager_remove_subscriber(HpbServiceManager *serv_man, HypeInstance * instance);

/**
 * @brief Deallocates the space previously allocated for the given HpbServiceManager struct.
 * @param serv_man Pointer to the pointer of the HpbServiceManager struct to be deallocated.
 */
void hpb_service_manager_destroy(HpbServiceManager **serv_man);

#endif /* HPB_SERVICE_MANAGER_H_INCLUDED_ */
