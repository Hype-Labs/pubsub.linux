
#ifndef HPB_TEST_H_INCLUDED_
#define HPB_TEST_H_INCLUDED_

#include <CUnit/Basic.h>

#include "hype_pub_sub/hype_pub_sub.h"

void hpb_test();

void hpb_test_issue_subscribe_req(HypePubSub *hpb);
void hpb_test_issue_unsubscribe_req(HypePubSub *hpb);
void hpb_test_issue_publish_req(HypePubSub *hpb);

void hpb_test_process_subscribe_req(HypePubSub *hpb);
void hpb_test_process_unsubscribe_req(HypePubSub *hpb);
void hpb_test_process_publish_req(HypePubSub *hpb);
void hpb_test_process_info_req(HypePubSub *hpb);

#endif /* HPB_TEST_H_INCLUDED_ */
