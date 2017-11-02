
#include "hype_pub_sub_test.h"

void hpb_test()
{
    HypePubSub *hpb = hpb_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(hpb);
    CU_ASSERT_PTR_NOT_NULL_FATAL(hpb->own_subscriptions);
    CU_ASSERT_PTR_NOT_NULL_FATAL(hpb->managed_services);
    CU_ASSERT_PTR_NOT_NULL_FATAL(hpb->network);
    CU_ASSERT_PTR_NOT_NULL_FATAL(hpb->protocol);


    hpb_destroy(&hpb);
    CU_ASSERT_PTR_NULL(hpb);

}
