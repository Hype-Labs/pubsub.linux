
#ifndef HPB_PROTOCOL_TEST_H_INCLUDED_
#define HPB_PROTOCOL_TEST_H_INCLUDED_

#include <CUnit/Basic.h>

#include "hype_pub_sub/protocol.h"

void hpb_protocol_test();

void hpb_protocol_test_sending();
void hpb_protocol_test_sending_subscribe();
void hpb_protocol_test_sending_unsubscribe();
void hpb_protocol_test_sending_publish();
void hpb_protocol_test_sending_info();
void hpb_protocol_test_sending_build_packet();

void hpb_protocol_test_receiving(HpbProtocol *prtcl);
void hpb_protocol_test_get_message_type();

#endif /* HPB_PROTOCOL_TEST_H_INCLUDED_ */
