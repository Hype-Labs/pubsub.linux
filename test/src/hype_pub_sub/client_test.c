
#include "client_test.h"

void hype_pub_sub_client_test()
{
    byte CLIENT1_ID[] = "\x85\xa9\xd4\xc4\xde\xd2\x87\x75\x0f\xc0\xed\x32";
    byte CLIENT2_ID[] = "\x66\xd8\xf2\x20\x6a\x56\xdb\xe9\x91\x23\x3b\xc2";
    byte CLIENT3_ID[] = "\xe7\x79\x34\x6c\x66\x9c\x17\xf4\x34\xc8\xce\x0e";

    Client *cl1 = hype_pub_sub_client_create(CLIENT1_ID);
    Client *cl2 = hype_pub_sub_client_create(CLIENT2_ID);
    Client *cl3 = hype_pub_sub_client_create(CLIENT3_ID);

    CU_ASSERT_NSTRING_EQUAL(cl1->id, "\x85\xa9\xd4\xc4\xde\xd2\x87\x75\x0f\xc0\xed\x32", HYPE_CONSTANTS_ID_BYTE_SIZE);
    CU_ASSERT_NSTRING_EQUAL(cl2->id, "\x66\xd8\xf2\x20\x6a\x56\xdb\xe9\x91\x23\x3b\xc2", HYPE_CONSTANTS_ID_BYTE_SIZE);
    CU_ASSERT_NSTRING_EQUAL(cl3->id, "\xe7\x79\x34\x6c\x66\x9c\x17\xf4\x34\xc8\xce\x0e", HYPE_CONSTANTS_ID_BYTE_SIZE);

    /*
    CU_ASSERT_NSTRING_EQUAL(cl1->key, "\x05\x2c\x5f\x25\xd0\xee\x44\x4c\x1a\xad\xcc\x48\x02\x89\xc8\x02\xb9\xf0\x78\x89", SHA1_BLOCK_SIZE);
    CU_ASSERT_NSTRING_EQUAL(cl1->key, "\xd3\xff\x03\x3e\x44\x9e\xd4\x2f\xd7\x7c\xf3\x37\x45\x6b\xb4\x2d\xa4\x10\x9b\xb0", SHA1_BLOCK_SIZE);

    for(int i=0; i<SHA1_BLOCK_SIZE;i++)
    {
        printf("%x\n", cl1->key[i]);
    }

    //CU_ASSERT_NSTRING_EQUAL(cl2->key, "", SHA1_BLOCK_SIZE);
    //CU_ASSERT_NSTRING_EQUAL(cl3->key, "", SHA1_BLOCK_SIZE);
    */

    Client *cl4 = hype_pub_sub_client_create(CLIENT1_ID);
    CU_ASSERT_FALSE(hype_pub_sub_client_is_id_equal(cl1->id, cl2->id));
    CU_ASSERT_TRUE(hype_pub_sub_client_is_id_equal(cl1->id, cl4->id));

    hype_pub_sub_client_destroy(&cl1);
    hype_pub_sub_client_destroy(&cl2);
    hype_pub_sub_client_destroy(&cl3);
    CU_ASSERT_PTR_NULL(cl1);
    CU_ASSERT_PTR_NULL(cl2);
    CU_ASSERT_PTR_NULL(cl3);
}
