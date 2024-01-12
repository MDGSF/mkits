#include "mckits_string.h"

struct MckitsStr mckits_str_init(const char* str) {
  struct MckitsStr ret = {0, (uint8_t*)str};
  if (str != NULL) {
    ret.len = strlen(str);
  }
  return ret;
}

struct MckitsStr mckits_str_initn(const char* str, size_t len) {
  struct MckitsStr ret = {len, (uint8_t*)str};
  return ret;
}

void mckits_strlow(uint8_t* dst, const uint8_t* src, size_t n) {
  while (n > 0) {
    *dst = mckits_tolower(*src);
    dst++;
    src++;
    n--;
  }
}

void mckits_strupper(uint8_t* dst, const uint8_t* src, size_t n) {
  while (n > 0) {
    *dst = mckits_toupper(*src);
    dst++;
    src++;
    n--;
  }
}

size_t mckits_strnlen(uint8_t* s, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    if (s[i] == '\0') {
      return i;
    }
  }
  return n;
}

uint8_t* mckits_strlchr(uint8_t* start, uint8_t* end, uint8_t c) {
  uint8_t* p = start;
  while (p < end) {
    if (*p == c) {
      return p;
    }
    p++;
  }
  return NULL;
}

uint8_t* mckits_copy(uint8_t* dst, uint8_t* src, size_t n) {
  while (n > 0) {
    *dst++ = *src++;
    n--;
  }
  return dst;
}

uint8_t* mckits_cpystrn(uint8_t* dst, uint8_t* src, size_t n) {
  if (n == 0) {
    return dst;
  }

  while (--n) {
    *dst = *src;

    if (*dst == '\0') {
      return dst;
    }

    dst++;
    src++;
  }

  *dst = '\0';

  return dst;
}
