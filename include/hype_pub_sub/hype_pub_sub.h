
#ifndef HPB_H_INCLUDED_
#define HPB_H_INCLUDED_

#include <stdlib.h>
#include <stdio.h>

#include "hpb_service_managers_list.h"
#include "hpb_subscriptions_list.h"
#include "hpb_network.h"
#include "hpb_protocol.h"

/**
 * @brief This struct represents a HypePubSub application.
 */
typedef struct HypePubSub_
{
    HpbSubscriptionsList *own_subscriptions; /**< List of subscriptions of this HypePubSub application. */
    HpbServiceManagersList *managed_services; /**< List of services managed by this HypePubSub application. */
    HpbNetwork *network; /**< Pointer to the network manager of this HypePubSub application. */
    struct HpbProtocol_ *protocol; /**< Pointer to the protocol manager of this HypePubSub application. */
} HypePubSub;

/**
 * @brief Allocates space for a HypePubSub struct.
 * @return Returns a pointer to the created struct or NULL if the space could not be allocated.
 */
HypePubSub *hpb_create();

/**
 * @brief Obtains the Hype client responsible for a given service through the network manager
 *        and it uses the protocol manager to send a subscribe request to that Hype client.
 * @param hpb Pointer to the HypePubSub application.
 * @param service_name Name of the service to be subscribed.
 * @return Return 0 in case of success and -1 otherwise.
 */
int hpb_issue_subscribe_req(HypePubSub *hpb, char *service_name);

/**
 * @brief Obtains the Hype client responsible for a given service through the network manager
 *        and it uses the protocol manager to send a unsubscribe request to that Hype client.
 * @param hpb Pointer to the HypePubSub application.
 * @param service_name Name of the service to be unsubscribed.
 * @return Return 0 in case of success and -1 otherwise.
 */
int hpb_issue_unsubscribe_req(HypePubSub *hpb, char *service_name);

/**
 * @brief Obtains the Hype client responsible for a given service through the network manager
 *        and it uses the protocol manager to send a publish request to that Hype client.
 * @param hpb Pointer to the HypePubSub application.
 * @param service_name Name of the service in which to publish.
 * @param msg Pointer to the message to be published.
 * @param msg_length Lenght of the message to be published
 * @return Return 0 in case of success and -1 otherwise.
 */
int hpb_issue_publish_req(HypePubSub *hpb, char *service_name, char *msg, size_t msg_length);

/**
 * @brief Processes a subscribe request to a given service. It adds the ID of the Hype client that sent the
 *        request to the list of the subscribers of the specified service. If the service does not exist in
 *        the list of managed services, it is added.
 * @param hpb Pointer to the HypePubSub application.
 * @param service_key Key of the service to be subscribed.
 * @param requester_client_id Hype ID of the client that sent the subscribe message.
 * @return Returns 0 in case of success and < 0 otherwise.
 */
int hpb_process_subscribe_req(HypePubSub *hpb, HLByte service_key[], HLByte requester_client_id[]);

/**
 * @brief Processes an unsubscribe request to a given service. It removes the ID of the Hype client that sent
 *        the request from the list of the subscribers of the specified service. If the service does not exist
 *        in the list of managed services, nothing is done.
 * @param hpb Pointer to the HypePubSub application.
 * @param service_key Key of the service to be unsubscribed.
 * @param requester_client_id Hype ID of the client that sent the unsubscribe message.
 * @return Returns 0 in case of success and < 0 otherwise.
 */
int hpb_process_unsubscribe_req(HypePubSub *hpb, HLByte service_key[], HLByte requester_client_id[]);

/**
 * @brief Processes a publish request to a given service. It sends the message to all the subscribers of the
 *        specified service. If the service does not exist in the list of managed services nothing is done.
 * @param hpb Pointer to the HypePubSub application.
 * @param service_key Key of the service in which to publish.
 * @param msg Message to be sent.
 * @param msg_length Length of the message to be sent.
 * @return Returns 0 in case of success and < 0 otherwise.
 */
int hpb_process_publish_req(HypePubSub *hpb, HLByte service_key[], char *msg, size_t msg_length);

/**
 * @brief Process an info message received.
 * @param hpb Pointer to the HypePubSub application.
 * @param service_key Key of the service to which the message belongs.
 * @param msg Message received.
 * @param msg_length Length of the received message.
 * @return Returns 0 in case of success and < 0 otherwise.
 */
int hpb_process_info_msg(HypePubSub *hpb, HLByte service_key[], char *msg, size_t msg_length);

static int hpb_update_managed_services(HypePubSub *hpb);

/**
 * @brief When a new Hype instance is found or lost we have to review the list of subscriptions to analyze if
 *        the service will be managed by a new Hype client.
 * @param hpb Pointer to the HypePubSub application.
 * @return Returns -1 if the HypePubSub application is NULL and 0 otherwise.
 */
static int hpb_update_own_subscriptions(HypePubSub *hpb);

/**
 * @brief Deallocates the space previously allocated for the HypePubSub struct
 * @param hpb Pointer to the pointer of the HypePubSub struct to be deallocated.
 */
void hpb_destroy(HypePubSub **hpb);



// TODO: Review this later. Currently it seems that these methods are replaced by the hpb_update_subscriptions() and hpb_update_managed_services() methods
// int hpb_process_change_service_manager_req(HypePubSub *pub_sub, byte service_key[SHA1_BLOCK_SIZE], byte new_manager_id[HYPE_ID_BYTE_SIZE], byte** subscribers_id[HYPE_ID_BYTE_SIZE]);
// static int hpb_issue_change_service_manager_req(HypePubSub *pub_sub, byte service_key[SHA1_BLOCK_SIZE], byte new_manager_id[HYPE_ID_BYTE_SIZE], byte** subscribers_id[HYPE_ID_BYTE_SIZE]);


#endif /* HPB_H_INCLUDED_ */
