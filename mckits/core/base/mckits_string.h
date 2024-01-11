#ifndef MKITS_MCKITS_CORE_MCKITS_STRING_H_
#define MKITS_MCKITS_CORE_MCKITS_STRING_H_

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

#ifdef __cplusplus
}
#endif

#endif
