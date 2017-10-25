
#include "binary_utils.h"


byte* binary_utils_xor(byte *byte_array1, byte *byte_array2, size_t byte_array_size)
{
    byte* str_xor = (byte*) malloc(byte_array_size * sizeof(byte));
    for(int i=0; i < byte_array_size; i++)
        str_xor[i] = byte_array1[i] ^ byte_array2[i];
    return str_xor;
}


char *binary_utils_to_binary_str(byte *byte_array, size_t byte_array_size)
{
    size_t str_size = byte_array_size*8 + byte_array_size*2 + 1;
    char *bin_str = (char*) malloc(str_size * sizeof(byte));

    for(int i=0; i < byte_array_size; i++)
    {
        byte b = byte_array[i];
        bin_str[i*10] = ((b & 0x80) == 0x80)? '1': '0';
        bin_str[i*10+1] = ((b & 0x40) == 0x40)? '1': '0';
        bin_str[i*10+2] = ((b & 0x20) == 0x20)? '1': '0';
        bin_str[i*10+3] = ((b & 0x10) == 0x10)? '1': '0';
        bin_str[i*10+4] = ' ';
        bin_str[i*10+5] = ((b & 0x08) == 0x08)? '1': '0';
        bin_str[i*10+6] = ((b & 0x04) == 0x04)? '1': '0';
        bin_str[i*10+7] = ((b & 0x02) == 0x02)? '1': '0';
        bin_str[i*10+8] = ((b & 0x01) == 0x01)? '1': '0';
        bin_str[i*10+9] = ' ';
    }

    bin_str[str_size-1] = '\0';

    return bin_str;

}

