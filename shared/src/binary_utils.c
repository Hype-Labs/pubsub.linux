
#include "binary_utils.h"


byte* binary_utils_xor(byte *byte_array1, byte *byte_array2, size_t byte_array_size)
{
    byte* str_xor = (byte*) malloc(byte_array_size * sizeof(byte));
    for(int i=0; i < byte_array_size; i++)
        str_xor[i] = byte_array1[i] ^ byte_array2[i];
    return str_xor;
}

int binary_utils_get_higher_binary_string(byte *byte_array1, byte *byte_array2, size_t byte_array_size)
{
    char *bin_str1 = binary_utils_to_binary_char_array(byte_array1, byte_array_size);
    char *bin_str2 = binary_utils_to_binary_char_array(byte_array2, byte_array_size);

    for(int i=0; i<byte_array_size; i++)
    {
        char digit_str1 = bin_str1[i];
        char digit_str2 = bin_str2[i];

        if(digit_str1 == digit_str2) // Search for the first difference in the binary digits
            continue;

        free(bin_str1);
        free(bin_str2);

        // When facing a bit difference the binary string
        // which has the bit '1' is the higher one
        if(digit_str1 == '1')
            return 1; // The first string has a higher value
        else
            return 2; // The second string has a higher value
    }

    return 0;
}

char *binary_utils_to_binary_char_array(byte *byte_array, size_t byte_array_size)
{
    // 8 binary chars per byte
    size_t str_size = byte_array_size*8;
    char *bin_str = (char*) malloc(str_size * sizeof(byte));

    for(int i=0; i < byte_array_size; i++)
    {
        byte b = byte_array[i];
        bin_str[i*8]   = ((b & 0x80) == 0x80)? '1': '0';
        bin_str[i*8+1] = ((b & 0x40) == 0x40)? '1': '0';
        bin_str[i*8+2] = ((b & 0x20) == 0x20)? '1': '0';
        bin_str[i*8+3] = ((b & 0x10) == 0x10)? '1': '0';
        bin_str[i*8+4] = ((b & 0x08) == 0x08)? '1': '0';
        bin_str[i*8+5] = ((b & 0x04) == 0x04)? '1': '0';
        bin_str[i*8+6] = ((b & 0x02) == 0x02)? '1': '0';
        bin_str[i*8+7] = ((b & 0x01) == 0x01)? '1': '0';
    }

    return bin_str;
}

char *binary_utils_get_formatted_binary_str(byte *byte_array, size_t byte_array_size)
{
    // Size:
    // 8 binary chars per byte
    // 2 spaces per byte
    // 1 \0 to terminate string
    size_t formatted_str_size = byte_array_size*8 + byte_array_size*2 + 1;
    char *formatted_str = (char*) malloc(formatted_str_size * sizeof(char));

    char * bin_array = binary_utils_to_binary_char_array(byte_array, byte_array_size);

    int j=0;
    for(int i=0; i < byte_array_size*8; i++)
    {
        if(i%4 == 0 && i != 0)
            formatted_str[j++] = ' '; // Adds a space at every 4 bits

        formatted_str[j++] = bin_array[i];
    }

    formatted_str[formatted_str_size-1] = '\0'; // Adds the string terminator
    free(bin_array);
    return formatted_str;
}

