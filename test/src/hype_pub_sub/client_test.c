
#include "client_test.h"

void hpb_client_test()
{
    HLByte CLIENT1_ID[] = "\x85\xa9\xd4\xc4\xde\xd2\x87\x75\x0f\xc0\xed\x32";
    HLByte CLIENT2_ID[] = "\x66\xd8\xf2\x20\x6a\x56\xdb\xe9\x91\x23\x3b\xc2";
    HLByte CLIENT3_ID[] = "\xe7\x79\x34\x6c\x66\x9c\x17\xf4\x34\xc8\xce\x0e";

    HpbClient *cl1 = hpb_client_create(CLIENT1_ID);
    HpbClient *cl2 = hpb_client_create(CLIENT2_ID);
    HpbClient *cl3 = hpb_client_create(CLIENT3_ID);

    // Test struct creation
    CU_ASSERT_PTR_NOT_NULL_FATAL(cl1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(cl2);
    CU_ASSERT_PTR_NOT_NULL_FATAL(cl3);

    // Validate the IDs and keys of the structs created
    CU_ASSERT_NSTRING_EQUAL(cl1->id, "\x85\xa9\xd4\xc4\xde\xd2\x87\x75\x0f\xc0\xed\x32", HPB_ID_BYTE_SIZE);
    CU_ASSERT_NSTRING_EQUAL(cl2->id, "\x66\xd8\xf2\x20\x6a\x56\xdb\xe9\x91\x23\x3b\xc2", HPB_ID_BYTE_SIZE);
    CU_ASSERT_NSTRING_EQUAL(cl3->id, "\xe7\x79\x34\x6c\x66\x9c\x17\xf4\x34\xc8\xce\x0e", HPB_ID_BYTE_SIZE);
    CU_ASSERT_NSTRING_EQUAL(cl1->key, "\x05\xeb\x63\x7c\xbd\x3f\x33\x69\x1d\x74\x3c\x2a\x39\xaf\xee\xda\x5e\xc9\x45\xad", SHA1_BLOCK_SIZE);
    CU_ASSERT_NSTRING_EQUAL(cl2->key, "\xf6\xcb\x6d\x9d\xb0\x98\x91\x9b\x2d\x39\x55\x11\x41\xc5\xcb\xe7\x67\xb5\x06\xd6", SHA1_BLOCK_SIZE);
    CU_ASSERT_NSTRING_EQUAL(cl3->key, "\xe4\x9a\xa7\x79\x2c\xf4\xfd\x09\x6c\x10\x3f\x4b\xa4\x63\xe2\x7b\x91\x60\x9e\x6b", SHA1_BLOCK_SIZE);

    // Test hpb_client_is_id_equal() method
    HpbClient *cl4 = hpb_client_create(CLIENT1_ID);
    CU_ASSERT_PTR_NOT_NULL_FATAL(cl4);
    CU_ASSERT_FALSE(hpb_client_is_id_equal(cl1->id, cl2->id));
    CU_ASSERT_TRUE(hpb_client_is_id_equal(cl1->id, cl4->id));

    // Test struct destruction
    hpb_client_destroy(&cl1);
    hpb_client_destroy(&cl2);
    hpb_client_destroy(&cl3);
    hpb_client_destroy(&cl4);
    CU_ASSERT_PTR_NULL(cl1);
    CU_ASSERT_PTR_NULL(cl2);
    CU_ASSERT_PTR_NULL(cl3);
    CU_ASSERT_PTR_NULL(cl4);
}
