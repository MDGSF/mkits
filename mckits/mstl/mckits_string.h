#ifndef MKITS_MCKITS_MSTL_MCKITS_STRING_H_
#define MKITS_MCKITS_MSTL_MCKITS_STRING_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct MckitsStr {
  size_t len;
  uint8_t* data;
};

#define mckits_string(str) \
  { sizeof(str) - 1, (uint8_t*)str }

#define mckits_null_string \
  { 0, NULL }

#define mckits_str_set(str, text) \
  (str)->len = sizeof(text) - 1;  \
  (str)->data = (uint8_t*)text

#define mckits_str_null(str) \
  (str)->len = 0;            \
  (str)->data = NULL

#define mckits_tolower(c) ((uint8_t)((c >= 'A' && c <= 'Z') ? (c | 0x20) : c))
#define mckits_toupper(c) ((uint8_t)((c >= 'a' && c <= 'z') ? (c & ~0x20) : c))

void mckits_strlow(uint8_t* dst, uint8_t* src, size_t n);

#ifdef __cplusplus
}
#endif

#endif
