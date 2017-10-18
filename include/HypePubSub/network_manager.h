#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"

/**
 * @brief
 */
typedef struct NetworkManager
{
    char ownClientId[HYPE_ID_BYTE_SIZE]; /**< Hype ID of this client. */
    char ** networkClientIds[HYPE_ID_BYTE_SIZE]; /**< Hype ID of the clients of the network. */
} NetworkManager;

/**
 * @brief createNetworkManager
 * @return
 */
NetworkManager* createNetworkManager();

/**
 * @brief getServiceManagerId
 * @param serviceKey
 * @return
 */
char* getServiceManagerId(char serviceKey[SHA1_KEY_BYTE_SIZE]); // TODO: Check return type

/**
 * @brief updateNetworkClients
 * @return
 */
int updateNetworkClients();

/**
 * @brief isClientOnline
 * @param clientId
 * @return
 */
bool isClientOnline(char clientId[HYPE_ID_BYTE_SIZE]);

/**
 * @brief getOwnClientId
 * @return
 */
char* getOwnClientId(); // TODO: Check return type
