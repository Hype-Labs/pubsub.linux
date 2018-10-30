
#ifndef HPB_TEST_H_INCLUDED_
#define HPB_TEST_H_INCLUDED_

#include <CUnit/Basic.h>

#include "hype_pub_sub/hype_pub_sub.h"

void hpb_test();

void hpb_test_issue_subscribe_req();
void hpb_test_issue_unsubscribe_req();
void hpb_test_issue_publish_req();

void hpb_test_process_subscribe_and_unsubscribe();
void hpb_test_process_publish_req();
void hpb_test_process_info_req();

#endif /* HPB_TEST_H_INCLUDED_ */
