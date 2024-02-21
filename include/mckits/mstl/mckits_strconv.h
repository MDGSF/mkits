#ifndef MKITS_INCLUDE_MCKITS_MSTL_MCKITS_STRCONV_H_
#define MKITS_INCLUDE_MCKITS_MSTL_MCKITS_STRCONV_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Convert a string to int.
@example:
  int num = mckits_char_string_to_int("123");
*/
int mckits_char_string_to_int(const char* str);

/*
@brief: Convert int to string.
@param num[in]: number will be converted to string.
@param str[out]: memory buffer used to store converted string.
@param size[in]: memory buffer size.
@example:
  int num = 123;
  char str[1024] = {0};
  mckits_int_to_char_string(num, str, 1024);
*/
void mckits_int_to_char_string(int num, char* str, size_t size);

/*
@brief: Convert int to string.
@param num[in]: number will be converted to string.
@return: pointer to heap memory buffer, need free manually.
@example:
  int num = 123;
  char* str = mckits_int_to_char_string_heap(num);
  // use str here
  free(str);
*/
char* mckits_int_to_char_string_heap(int num);

/*
@brief: Convert a string to int64_t.
@example:
  int64_t num = mckits_char_string_to_int64("123");
*/
int64_t mckits_char_string_to_int64(const char* str);

/*
@brief: Convert int64_t to string.
@param num[in]: number will be converted to string.
@param str[out]: memory buffer used to store converted string.
@param size[in]: memory buffer size.
@example:
  int64_t num = 123;
  char str[1024] = {0};
  mckits_int64_to_char_string(num, str, 1024);
*/
void mckits_int64_to_char_string(int64_t num, char* str, size_t size);

/*
@brief: Convert int64_t to string.
@param num[in]: number will be converted to string.
@return: pointer to heap memory buffer, need free manually.
@example:
  int64_t num = 123;
  char* str = mckits_int64_to_char_string_heap(num);
  // use str here
  free(str);
*/
char* mckits_int64_to_char_string_heap(int64_t num);

/*
@brief: Convert a string to float.
@example:
  float num = mckits_char_string_to_float("123.456");
*/
float mckits_char_string_to_float(const char* str);
double mckits_char_string_to_double(const char* str);

#ifdef __cplusplus
}
#endif

#endif  // MKITS_INCLUDE_MCKITS_CORE_MCKITS_STRCONV_H_
