#include <stdio.h>
#include <string.h>

#include <CUnit/Basic.h>

#include "linked_list_test.h"
#include "binary_utils_test.h"


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

   if ((CU_add_test(pSuite, "Test the generic linked list", linked_list_test) == NULL) ||
       (CU_add_test(pSuite, "Test binary utils module", binary_utils_test) == NULL))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
