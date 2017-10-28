
#include "client_test.h"

void hype_pub_sub_client_test()
{
    byte CLIENT1_ID[] = {0x85, 0xa9, 0xd4, 0xc4, 0xde ,0xd2, 0x87 ,0x75, 0x0f, 0xc0, 0xed, 0x32};
    byte CLIENT2_ID[] = {0x66, 0xd8, 0xf2, 0x20, 0x6a, 0x56, 0xdb, 0xe9, 0x91, 0x23, 0x3b, 0xc2};
    byte CLIENT3_ID[] = {0xe7, 0x79, 0x34, 0x6c, 0x66, 0x9c, 0x17, 0xf4, 0x34, 0xc8, 0xce, 0x0e};

    Client *cl1 = hype_pub_sub_client_create(CLIENT1_ID);
    Client *cl2 = hype_pub_sub_client_create(CLIENT2_ID);
    Client *cl3 = hype_pub_sub_client_create(CLIENT3_ID);

    CU_ASSERT_PTR_NOT_NULL_FATAL(cl1);
    CU_ASSERT_PTR_NOT_NULL_FATAL(cl2);
    CU_ASSERT_PTR_NOT_NULL_FATAL(cl3);

    CU_ASSERT_NSTRING_EQUAL(cl1->id, "\x85\xa9\xd4\xc4\xde\xd2\x87\x75\x0f\xc0\xed\x32", HYPE_CONSTANTS_ID_BYTE_SIZE);
    CU_ASSERT_NSTRING_EQUAL(cl2->id, "\x66\xd8\xf2\x20\x6a\x56\xdb\xe9\x91\x23\x3b\xc2", HYPE_CONSTANTS_ID_BYTE_SIZE);
    CU_ASSERT_NSTRING_EQUAL(cl3->id, "\xe7\x79\x34\x6c\x66\x9c\x17\xf4\x34\xc8\xce\x0e", HYPE_CONSTANTS_ID_BYTE_SIZE);

    CU_ASSERT_NSTRING_EQUAL(cl1->key, "\x05\xeb\x63\x7c\xbd\x3f\x33\x69\x1d\x74\x3c\x2a\x39\xaf\xee\xda\x5e\xc9\x45\xad", SHA1_BLOCK_SIZE);
    CU_ASSERT_NSTRING_EQUAL(cl2->key, "\xf6\xcb\x6d\x9d\xb0\x98\x91\x9b\x2d\x39\x55\x11\x41\xc5\xcb\xe7\x67\xb5\x06\xd6", SHA1_BLOCK_SIZE);
    CU_ASSERT_NSTRING_EQUAL(cl3->key, "\xe4\x9a\xa7\x79\x2c\xf4\xfd\x09\x6c\x10\x3f\x4b\xa4\x63\xe2\x7b\x91\x60\x9e\x6b", SHA1_BLOCK_SIZE);

    Client *cl4 = hype_pub_sub_client_create(CLIENT1_ID);
    CU_ASSERT_PTR_NOT_NULL_FATAL(cl4);
    CU_ASSERT_FALSE(hype_pub_sub_client_is_id_equal(cl1->id, cl2->id));
    CU_ASSERT_TRUE(hype_pub_sub_client_is_id_equal(cl1->id, cl4->id));

    hype_pub_sub_client_destroy(&cl1);
    hype_pub_sub_client_destroy(&cl2);
    hype_pub_sub_client_destroy(&cl3);
    hype_pub_sub_client_destroy(&cl4);
    CU_ASSERT_PTR_NULL(cl1);
    CU_ASSERT_PTR_NULL(cl2);
    CU_ASSERT_PTR_NULL(cl3);
    CU_ASSERT_PTR_NULL(cl4);
}
