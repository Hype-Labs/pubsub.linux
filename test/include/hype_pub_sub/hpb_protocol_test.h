
#ifndef HPB_PROTOCOL_TEST_H_INCLUDED_
#define HPB_PROTOCOL_TEST_H_INCLUDED_

#include <CUnit/Basic.h>

#include "hype_pub_sub/hpb_protocol.h"

void hpb_protocol_test();

void hpb_protocol_test_build_subscribe_msg();
void hpb_protocol_test_build_unsubscribe_msg();
void hpb_protocol_test_build_publish_msg();
void hpb_protocol_test_build_info_msg();
void hpb_protocol_test_receiving_msg();

#endif /* HPB_PROTOCOL_TEST_H_INCLUDED_ */
