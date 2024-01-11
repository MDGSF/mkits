#ifndef MKITS_MCKITS_CORE_MCKITS_STRCONV_H_
#define MKITS_MCKITS_CORE_MCKITS_STRCONV_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Convert a string to int.
*/
int mckits_string_to_int(const char* str);

/*
@brief: Convert int to string.
@param num[int]: number will be converted to string.
@param str[out]: memory buffer used to store converted string.
@param size[in]: memory buffer size.
*/
void mckits_int_to_string(int num, char* str, size_t size);

/*
@brief: Convert a string to int64_t.
*/
int64_t mckits_string_to_int64(const char* str);

/*
@brief: Convert int64_t to string.
@param num[int]: number will be converted to string.
@param str[out]: memory buffer used to store converted string.
@param size[in]: memory buffer size.
*/
void mckits_int64_to_string(int64_t num, char* str, size_t size);

#ifdef __cplusplus
}
#endif

#endif
