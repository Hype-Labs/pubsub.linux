
#ifndef SHARED_BINARY_UTILS_H_INCLUDED_
#define SHARED_BINARY_UTILS_H_INCLUDED_

#include <stdlib.h>
#include <stdio.h>

typedef unsigned char byte;

byte* binary_utils_xor(byte *byte_array1, byte *byte_array2, size_t byte_array_size);

int binary_utils_get_higher_binary_string(byte *byte_array1, byte *byte_array2, size_t byte_array_size);

char* binary_utils_to_binary_char_array(byte *byte_array, size_t byte_array_size);

char *binary_utils_get_formatted_binary_str(byte *byte_array, size_t byte_array_size);

void binary_utils_print_hex_array(unsigned char* array, size_t len);

#endif /* SHARED_BINARY_UTILS_H_INCLUDED_ */
