
#ifndef HPB_TEST_UTILS_H_INCLUDED_
#define HPB_TEST_UTILS_H_INCLUDED_

#include <binary_utils.h>
#include <hype_pub_sub/hpb_client.h>

#define HPB_UTILS_CLIENT_ID_TEST_SIZE 12

HypeInstance * hpb_test_utils_get_instance_from_id(HLByte *id, size_t size);

HpbClient * hpb_test_utils_get_client_from_id(HLByte *id, size_t size);

#endif /* HPB_TEST_UTILS_H_INCLUDED_ */
