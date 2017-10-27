
#include <CUnit/Basic.h>

#include "linked_list_test.h"
#include "binary_utils_test.h"
#include "hype_pub_sub_test.h"
#include "client_test.h"
#include "service_manager_test.h"
#include "subscription_test.h"
#include "network_test.h"
#include "protocol_test.h"
#include "list_clients_test.h"
#include "list_service_managers_test.h"
#include "list_subscriptions_test.h"


int main()
{
   CU_pSuite pSuite = NULL;

   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   pSuite = CU_add_suite("HypePubSub_TestSuite", NULL, NULL);

   if (pSuite == NULL)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   if ((CU_add_test(pSuite, "Test LinkedList module", linked_list_test) == NULL) ||
       (CU_add_test(pSuite, "Test BinaryUtils module", binary_utils_test) == NULL) ||
       (CU_add_test(pSuite, "Test HypePubSub module", hype_pub_sub_test) == NULL) ||
       (CU_add_test(pSuite, "Test HypePubSub/Client module", hype_pub_sub_client_test) == NULL) ||
       (CU_add_test(pSuite, "Test HypePubSub/ServiceManager module", hype_pub_sub_service_manager_test) == NULL) ||
       (CU_add_test(pSuite, "Test HypePubSub/Subscription module", hype_pub_sub_subscription_test) == NULL) ||
       (CU_add_test(pSuite, "Test HypePubSub/Network module", hype_pub_sub_network_test) == NULL) ||
       (CU_add_test(pSuite, "Test HypePubSub/Protocol module", hype_pub_sub_protocol_test) == NULL) ||
       (CU_add_test(pSuite, "Test HypePubSub/ListClients module", hype_pub_sub_list_clients_test) == NULL) ||
       (CU_add_test(pSuite, "Test HypePubSub/ListServiceManagers module", hype_pub_sub_list_service_managers_test) == NULL) ||
       (CU_add_test(pSuite, "Test HypePubSub/ListSubscriptions module", hype_pub_sub_list_subscriptions_test) == NULL))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
