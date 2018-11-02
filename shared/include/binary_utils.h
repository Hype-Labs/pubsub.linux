
#ifndef SHARED_BINARY_UTILS_H_INCLUDED_
#define SHARED_BINARY_UTILS_H_INCLUDED_

#include <stdlib.h>
#include <stdio.h>

typedef unsigned char HLByte;

/**
 * @brief It executes the XOR operator between 2 byte arrays of the same size.
 * @param byte_array1 1st byte array.
 * @param byte_array2 2nd byte array.
 * @param byte_array_size Size of the byte arrays.
 * @return Returns a pointer to the byte array containing the XOR result.
 */
HLByte *binary_utils_xor(HLByte *byte_array1, HLByte *byte_array2, size_t byte_array_size);

/**
 * @brief Compares 2 binary arrays and calculates which one contains the higher integer value. 
 * The byte arrays are interpreted as BigEndian!
 * @param byte_array1 1st byte array.
 * @param byte_array2 2nd byte array.
 * @param byte_array_size Size of the byte arrays.
 * @return Returns 1 if the first array is higher, 2 if the second array is higher and 0 if the arrays are equal.
 */
int binary_utils_get_higher_byte_array(HLByte *byte_array1, HLByte *byte_array2, size_t byte_array_size);

/**
 * @brief Converts a byte array to its char array binary representation.
 * @param byte_array Byte array to be converted.
 * @param byte_array_size Size of the byte array.
 * @return Returns a pointer to the char array containing the conversion result.
 */
char *binary_utils_to_binary_char_array(HLByte *byte_array, size_t byte_array_size);

/**
 * @brief Converts a byte array to its a formatted string containing its binary representation.
 * @param byte_array Byte array to be converted.
 * @param byte_array_size Size of the byte array.
 * @return Returns a pointer to the string containing the conversion result.
 */
char *binary_utils_get_formatted_binary_str(HLByte *byte_array, size_t byte_array_size);

/**
 * @brief Prints a byte array in its hexadecimal form.
 * @param array Array to be printed
 * @param len Length of the array.
 */
void binary_utils_print_hex_array(HLByte *array, size_t len);

#endif /* SHARED_BINARY_UTILS_H_INCLUDED_ */
