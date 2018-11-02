
#include <CUnit/Basic.h>

#include "linked_list_test.h"
#include "binary_utils_test.h"
#include "string_utils_test.h"
#include "hype_pub_sub_test.h"
#include "hpb_client_test.h"
#include "hpb_service_manager_test.h"
#include "hpb_subscription_test.h"
#include "hpb_network_test.h"
#include "hpb_protocol_test.h"
#include "hpb_clients_list_test.h"
#include "hpb_service_managers_list_test.h"
#include "hpb_subscriptions_list_test.h"


int main()
{
   CU_pSuite pSuite = NULL;

   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   pSuite = CU_add_suite("HypePubSub TestSuite", NULL, NULL);

   if (pSuite == NULL)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   if (
       (CU_add_test(pSuite, "Test LinkedList module", linked_list_test) == NULL) ||
       (CU_add_test(pSuite, "Test BinaryUtils module", binary_utils_test) == NULL) ||
       (CU_add_test(pSuite, "Test StringUtils module", string_utils_test) == NULL) ||
       (CU_add_test(pSuite, "Test HypePubSub module", hpb_test) == NULL) ||
       (CU_add_test(pSuite, "Test HpbClient module", hpb_client_test) == NULL) ||
       (CU_add_test(pSuite, "Test HpbServiceManager module", hpb_service_manager_test) == NULL) ||
       (CU_add_test(pSuite, "Test HpbSubscription module", hpb_subscription_test) == NULL) ||
       (CU_add_test(pSuite, "Test HpbNetwork module", hpb_network_test) == NULL) ||
       (CU_add_test(pSuite, "Test HpbProtocol module", hpb_protocol_test) == NULL) ||
       (CU_add_test(pSuite, "Test HpbClientsList module", hpb_list_clients_test) == NULL) ||
       (CU_add_test(pSuite, "Test HpbServiceManagersList module", hpb_list_service_managers_test) == NULL) ||
       (CU_add_test(pSuite, "Test HpbSubscriptionsList module", hpb_list_subscriptions_test) == NULL)
      )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
