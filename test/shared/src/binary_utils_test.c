
#include "binary_utils_test.h"

void binary_utils_test()
{
    binary_utils_test_xor();
}

void binary_utils_test_xor()
{
    byte * xor_result;

    byte bin_str1[] = {'\x12','\xfa','\x15'};
    byte bin_str2[] = {'\x45','\x21','\x33'};
    xor_result = binary_utils_xor(bin_str1, bin_str2, 3);
    CU_ASSERT_NSTRING_EQUAL(xor_result, "\x57\xdb\x26",3);
    free(xor_result);

    byte bin_str3[] = "\xe4\x66\x56\xb7\x5a\xb6\x36\x3d\x34\x9d\x11\xef\xd8\xe4\x4a\xdf\x06\xd3\x48\x4d";
    byte bin_str4[] = "\x7b\x39\xa7\xb6\x29\x29\xda\x8d\x23\x6c\xd4\x08\xe2\x5c\x9d\x17\xaa\x41\x7c\x89";
    xor_result = binary_utils_xor(bin_str3, bin_str4, 20);
    CU_ASSERT_NSTRING_EQUAL(xor_result, "\x9f\x5f\xf1\x01\x73\x9f\xec\xb0\x17\xf1\xc5\xe7\x3a\xb8\xd7\xc8\xac\x92\x34\xc4",20);
    free(xor_result);
}
