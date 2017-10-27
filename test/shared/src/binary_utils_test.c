
#include "binary_utils_test.h"

void binary_utils_test()
{
    binary_utils_test_xor();
    binary_utils_test_to_binary_char_array();
}

void binary_utils_test_xor()
{
    byte * xor_result;
    size_t lenght = 20;

    byte bin_str1[] = "XsE6s1lh8IDpavU1R8BU";
    byte bin_str2[] = "NIY6B9u4EbwsafkoG4nB";
    xor_result = binary_utils_xor(bin_str1, bin_str2, lenght);
    CU_ASSERT_NSTRING_EQUAL(xor_result, "\x16\x3a\x1c\x00\x31\x08\x19\x5c\x7d\x2b\x33\x03\x00\x10\x3e\x5e\x15\x0c\x2c\x17", lenght);
    free(xor_result);

    byte bin_str3[] = "\xe4\x66\x56\xb7\x5a\xb6\x36\x3d\x34\x9d\x11\xef\xd8\xe4\x4a\xdf\x06\xd3\x48\x4d";
    byte bin_str4[] = "\x7b\x39\xa7\xb6\x29\x29\xda\x8d\x23\x6c\xd4\x08\xe2\x5c\x9d\x17\xaa\x41\x7c\x89";
    xor_result = binary_utils_xor(bin_str3, bin_str4, lenght);
    CU_ASSERT_NSTRING_EQUAL(xor_result, "\x9f\x5f\xf1\x01\x73\x9f\xec\xb0\x17\xf1\xc5\xe7\x3a\xb8\xd7\xc8\xac\x92\x34\xc4", lenght);
    free(xor_result);
}


void binary_utils_test_to_binary_char_array()
{
    char *bin_array, *bin_str;
    size_t lenght = 20;

    byte bin_str1[] = "I5Uux0nMietAkP4Ec53t";
    byte bin_str2[] = "3z3ocTd9MYtmV1Nt0Lp3";

    bin_array = binary_utils_to_binary_char_array(bin_str1, lenght);
    CU_ASSERT_NSTRING_EQUAL(bin_array, "0100100100110101010101010111010101111000001100000110111001001101011010010110010101110100010000010110101101010000001101000100010101100011001101010011001101110100", lenght*8);
    free(bin_array);

    bin_array = binary_utils_to_binary_char_array(bin_str2, lenght);
    CU_ASSERT_NSTRING_EQUAL(bin_array, "0011001101111010001100110110111101100011010101000110010000111001010011010101100101110100011011010101011000110001010011100111010000110000010011000111000000110011", lenght*8);
    free(bin_array);

    bin_str = binary_utils_get_formatted_binary_str(bin_str2, lenght);
    CU_ASSERT_STRING_EQUAL(bin_str, "0011 0011 0111 1010 0011 0011 0110 1111 0110 0011 0101 0100 0110 0100 0011 1001 0100 1101 0101 1001 0111 0100 0110 1101 0101 0110 0011 0001 0100 1110 0111 0100 0011 0000 0100 1100 0111 0000 0011 0011\0");
    free(bin_str);
}





