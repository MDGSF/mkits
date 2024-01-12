#ifndef MKITS_MCKITS_MSTL_MCKITS_STRING_H_
#define MKITS_MCKITS_MSTL_MCKITS_STRING_H_

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

struct MckitsStr {
  size_t len;
  uint8_t* data;
};

struct MckitsStr mckits_str_init(const char* str);
struct MckitsStr mckits_str_initn(const char* str, size_t len);

#define mckits_str(str) \
  { sizeof(str) - 1, (uint8_t*)str }

#define mckits_null_str \
  { 0, NULL }

#define mckits_str_set(str, text) \
  (str)->len = sizeof(text) - 1;  \
  (str)->data = (uint8_t*)text

#define mckits_str_null(str) \
  (str)->len = 0;            \
  (str)->data = NULL

/*
@brief: Transform byte to lower.
*/
#define mckits_tolower(c) ((uint8_t)((c >= 'A' && c <= 'Z') ? (c | 0x20) : c))

/*
@brief: Transform byte to upper.
*/
#define mckits_toupper(c) ((uint8_t)((c >= 'a' && c <= 'z') ? (c & ~0x20) : c))

/*
@brief: Transform string to lower.
@param dst[out]: Pointer to dst memory buffer, used to store output string.
@param src[in]: Pointer to src memory buffer.
@param n[in]: n bytes will to transform to lower.
*/
void mckits_strlow(uint8_t* dst, const uint8_t* src, size_t n);

/*
@brief: Transform string to upper.
@param dst[out]: Pointer to dst memory buffer, used to store output string.
@param src[in]: Pointer to src memory buffer.
@param n[in]: n bytes will to transform to upper.
*/
void mckits_strupper(uint8_t* dst, const uint8_t* src, size_t n);

/*
@brief: Compare the strings s1 with s2.
@libc: int strcmp(const char *s1, const char *s2);
*/
#define mckits_strcmp(s1, s2) strcmp((const char*)s1, (const char*)s2)

/*
@brief: Compare at most n bytes of the strings s1 and s2.
@libc: int strncmp(const char *s1, const char *s2, size_t n);
*/
#define mckits_strncmp(s1, s2, n) strncmp((const char*)s1, (const char*)s2, n)

/*
@brief: Return the length of the string s.
@libc: size_t strlen(const char *s);
*/
#define mckits_strlen(s) strlen((const char*)s)

/*
@brief: Return the length of the string s, at most process n bytes.
  if strlen(s) >= n, return n.
  else, return strlen(s)
*/
size_t mckits_strnlen(uint8_t* s, size_t n);

/*
@brief: Find the first occurrence of the substring needle in the string
haystack, returning a pointer to the found substring.
@libc: char *strstr(const char *haystack, const char *needle);
*/
#define mckits_strstr(s1, s2) strstr((const char*)s1, (const char*)s2)

/*
@brief: The strchr() function returns a pointer to the first occurrence of the
character c in the string s, or NULL if the character is not found.
@libc: char *strchr(const char *s, int c);
*/
#define mckits_strchr(s, c) strchr((const char*)s, c)

/*
@brief: Returns a pointer to the first occurrence of the character c from
start to end, or NULL if the character is not found.
*/
uint8_t* mckits_strlchr(uint8_t* start, uint8_t* end, uint8_t c);

/*
@brief: Fill memory with zero.
@libc: void *memset(void *s, int c, size_t n);
*/
#define mckits_memzero(buf, n) (void)memset(buf, 0, n)

/*
@brief: Fill memory with a constant byte.
@libc: void *memset(void *s, int c, size_t n);
*/
#define mckits_memset(buf, c, n) (void)memset(buf, c, n)

/*
@brief: copy memory area
@libc: void *memcpy(void *dest, const void *src, size_t n);
*/
#define mckits_memcpy(dst, src, n) (void)memcpy(dst, src, n)
#define mckits_cpymem(dst, src, n) (((uint8_t*)memcpy(dst, src, n)) + (n))

/*
@brief: Copy memory area, the same as `mckits_cpymem()` function.
@return pointer to dst.
*/
uint8_t* mckits_copy(uint8_t* dst, uint8_t* src, size_t n);

/*
@brief: copy memory area
@libc: void *memmove(void *dest, const void *src, size_t n);
*/
#define mckits_memmove(dst, src, n) (void)memmove(dst, src, n)
#define mckits_movemem(dst, src, n) (((uint8_t*)memmove(dst, src, n)) + (n))

/*
@brief: compare memory areas
@libc: int memcmp(const void *s1, const void *s2, size_t n);
*/
#define mckits_memcmp(s1, s2, n) memcmp(s1, s2, n)

/*
@brief: Copy src to dst. dst will always have null-terminated.
@return pointer to dst
*/
uint8_t* mckits_cpystrn(uint8_t* dst, uint8_t* src, size_t n);

#ifdef __cplusplus
}
#endif

#endif
