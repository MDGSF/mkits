#include "mckits_string.h"

#include <stdlib.h>

struct MckitsString* mckits_string_init(struct MckitsString* mstring,
                                        const char* data) {
  if (data == NULL) {
    mstring->cap = 0;
    mstring->len = 0;
    mstring->data = NULL;
    return mstring;
  }

  size_t len = mckits_strlen(data);
  uint8_t* ptr = (uint8_t*)malloc(len + 1);
  if (ptr == NULL) {
    return NULL;
  }

  mstring->len = len;
  mstring->cap = len + 1;
  mstring->data = ptr;
  mckits_memcpy(ptr, data, len + 1);
  return mstring;
}

struct MckitsString* mckits_string_new(const char* data) {
  struct MckitsString* mstring =
      (struct MckitsString*)malloc(sizeof(struct MckitsString));
  if (mstring == NULL) {
    return NULL;
  }
  return mckits_string_init(mstring, data);
}

void mckits_string_drop(struct MckitsString* mstring) {
  mckits_string_drop_data(mstring);
  free(mstring);
}

void mckits_string_drop_data(struct MckitsString* mstring) {
  mstring->cap = 0;
  mstring->len = 0;
  free(mstring->data);
  mstring->data = NULL;
}

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

uint8_t* mckits_pstrdup(const struct MckitsStr* src) {
  uint8_t* dst = (uint8_t*)malloc(src->len + 1);
  if (dst == NULL) {
    return NULL;
  }
  mckits_memcpy(dst, src->data, src->len + 1);
  return dst;
}

struct MckitsString mckits_strdup(struct MckitsStr src) {
  struct MckitsString mstring;
  mckits_string_init(&mstring, (const char*)src.data);
  return mstring;
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

int mckits_strcasecmp(uint8_t* s1, uint8_t* s2) {
  int c1 = 0;
  int c2 = 0;

  for (;;) {
    c1 = (int)*s1++;
    c2 = (int)*s2++;

    c1 = (c1 >= 'A' && c1 <= 'Z') ? (c1 | 0x20) : c1;
    c2 = (c2 >= 'A' && c2 <= 'Z') ? (c2 | 0x20) : c2;

    if (c1 == c2) {
      if (c1) {
        continue;
      }

      return 0;
    }

    return c1 - c2;
  }
}

int mckits_strncasecmp(uint8_t* s1, uint8_t* s2, size_t n) {
  int c1 = 0;
  int c2 = 0;

  while (n) {
    c1 = (int)*s1++;
    c2 = (int)*s2++;

    c1 = (c1 >= 'A' && c1 <= 'Z') ? (c1 | 0x20) : c1;
    c2 = (c2 >= 'A' && c2 <= 'Z') ? (c2 | 0x20) : c2;

    if (c1 == c2) {
      if (c1) {
        n--;
        continue;
      }

      return 0;
    }

    return c1 - c2;
  }

  return 0;
}
