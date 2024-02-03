#ifndef MKITS_MCKITS_CORE_MCKITS_MRANDOM_H_
#define MKITS_MCKITS_CORE_MCKITS_MRANDOM_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Generate random seed.
*/
void mckits_random_seed();

/*
@brief: Generate random string.
@param buf[out]: memory buffer used to store random string.
@param size[in]: memory buffer size.
@notes:
  - Random string size will be `size - 1`, the last element will be '\0'.
  - Each character is upper and lower case letters or numbers.
*/
void mckits_random_str(char* buf, size_t size);

/*
@brief: Generate random byte array.
@param buf[out]: memory buffer used to store random byte.
@param size[in]: memory buffer size.
@notes: Each byte is between [0, 255]
*/
void mckits_random_bytes(uint8_t* buf, size_t size);

/*
@brief: Generate random number in range [start, end).
@notes: start must be smaller than end.
*/
int mckits_random_num(int start, int end);

#ifdef __cplusplus
}
#endif

#endif
