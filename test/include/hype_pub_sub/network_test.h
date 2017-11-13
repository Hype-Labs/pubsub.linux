
#ifndef HPB_NETWORK_TEST_H_INCLUDED_
#define HPB_NETWORK_TEST_H_INCLUDED_

#include <CUnit/Basic.h>

#include "hype_pub_sub/network.h"

void hpb_network_test();
void hpb_network_test_get_service_manager_id(HpbNetwork *network);
void hpb_network_test_is_client_online(HpbNetwork *network);

#endif /* HPB_NETWORK_TEST_H_INCLUDED_ */
