#ifndef MKITS_MCKITS_MCKITS_MRANDOM_H_
#define MKITS_MCKITS_MCKITS_MRANDOM_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void mckits_random_seed();

/*
@brief: Generate random string.
@param buf[out]: memory buffer used to store random string.
@param size[in]: memory buffer size.
@notes: Random string size will be `size - 1`, the last element will be '\0'.
*/
void mckits_random_str(void* buf, size_t size);

/*
@brief: Generate random number in range [start, end).
@notes: start must be smaller than end.
*/
int mckits_random_num(int start, int end);

#ifdef __cplusplus
}
#endif

#endif
