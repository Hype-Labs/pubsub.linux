
#ifndef SHARED_BINARY_UTILS_H_INCLUDED_
#define SHARED_BINARY_UTILS_H_INCLUDED_

#include <stdlib.h>

typedef unsigned char byte;

byte* binary_utils_xor(byte *byte_array1, byte *byte_array2, size_t byte_array_size);

char* binary_utils_to_binary_char_array(byte *byte_array, size_t byte_array_size);

char *binary_utils_get_formatted_binary_str(byte *byte_array, size_t byte_array_size);

#endif /* SHARED_BINARY_UTILS_H_INCLUDED_ */
