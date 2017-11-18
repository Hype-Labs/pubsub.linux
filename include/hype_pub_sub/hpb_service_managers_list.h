
#ifndef HPB_LIST_SERVICE_MANAGERS_H_INCLUDED_
#define HPB_LIST_SERVICE_MANAGERS_H_INCLUDED_

#include "linked_list.h"
#include "hpb_service_manager.h"
#include "hpb_constants.h"


typedef LinkedListNode HpbServiceManagersListNode;
typedef LinkedList HpbServiceManagersList;

/**
 * @brief Allocates space for a linked list of HpbServiceManager elements.
 * @return Returns a pointer to the created linked list or NULL if the space could not be allocated.
 */
HpbServiceManagersList *hpb_list_service_managers_create();

/**
 * @brief Adds an HpbServiceManager to a HpbServiceManagersList.
 * @param list_serv_man List in which the HpbServiceManager should be added.
 * @param service_key Service key of the HpbServiceManager to be added.
 * @return Returns a pointer to the added HpbServiceManager.
 */
HpbServiceManager *hpb_list_service_managers_add(HpbServiceManagersList *list_serv_man, HLByte service_key[SHA1_BLOCK_SIZE]);

/**
 * @brief Removes an HpbServiceManager from a HpbServiceManagersList.
 * @param list_serv_man List from which the HpbServiceManager should be removed.
 * @param service_key Service key of the HpbServiceManager to be removed.
 * @return Returns >=0 if the HpbServiceManager was removed and <0 otherwise.
 */
int hpb_list_service_managers_remove(HpbServiceManagersList *list_serv_man, HLByte service_key[SHA1_BLOCK_SIZE]);

/**
 * @brief Deallocates the space previously allocated for a linked list of HpbServiceManager elements
 * @param list_serv_man Pointer to the pointer of the HpbServiceManager linked list to be deallocated.
 */
void hpb_list_service_managers_destroy(HpbServiceManagersList **list_serv_man);

/**
 * @brief Finds a given HpbServiceManager in a linked list.
 * @param list_serv_man List in which the HpbServiceManager should be searched.
 * @param service_key Service key of the HpbServiceManager to be searched.
 * @return Returns a pointer to the HpbServiceManager if the search is successful or NULL otherwise.
 */
HpbServiceManager *hpb_list_service_managers_find(HpbServiceManagersList *list_serv_man, HLByte service_key[]);

/**
 * @brief Callback to identify a HpbServiceManager in the linked list.
 * @param service_manager HpbServiceManager to be analyzed.
 * @param key Key to which the HpbServiceManager should be compared.
 * @return Returns true if the specified key corresponds to the key of the specified HpbServiceManager.
 */
static bool linked_list_callback_is_service_manager_key(void *service_manager, void *key);

/**
 * @brief Callback to deallocate the space reserved for a HpbServiceManager of the linked list.
 * @param service_manager Pointer to the pointer of the HpbServiceManager to be deallocated.
 */
static void linked_list_callback_free_service_manager(void **service_manager);

#endif /* HPB_LIST_SERVICE_MANAGERS_H_INCLUDED_ */
