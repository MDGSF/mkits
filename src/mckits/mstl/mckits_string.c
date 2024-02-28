#include "mckits/mstl/mckits_string.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "mckits/mlibc/mckits_malloc.h"

void mckits_string_init(struct MckitsString* mstring, const char* data) {
  if (data == NULL) {
    mstring->cap = 0;
    mstring->len = 0;
    mstring->data = NULL;
    return;
  }

  size_t len = mckits_strlen(data);
  uint8_t* ptr = (uint8_t*)mckits_malloc(len + 1);

  mstring->len = len;
  mstring->cap = len + 1;
  mstring->data = ptr;
  mckits_memcpy(ptr, data, len + 1);
}

void mckits_string_init_from_bytes(struct MckitsString* mstring,
                                   const uint8_t* data, size_t size) {
  if (data == NULL || size <= 0) {
    mstring->cap = 0;
    mstring->len = 0;
    mstring->data = NULL;
    return;
  }

  uint8_t* ptr = (uint8_t*)mckits_malloc(size + 1);

  mstring->len = size;
  mstring->cap = size + 1;
  mstring->data = ptr;
  mckits_memcpy(ptr, data, size);
  ptr[size] = '\0';
}

struct MckitsString* mckits_string_new(const char* data) {
  struct MckitsString* mstring =
      (struct MckitsString*)mckits_malloc(sizeof(struct MckitsString));
  mckits_string_init(mstring, data);
  return mstring;
}

struct MckitsString* mckits_string_from_bytes(const uint8_t* data,
                                              size_t size) {
  struct MckitsString* mstring =
      (struct MckitsString*)mckits_malloc(sizeof(struct MckitsString));
  mckits_string_init_from_bytes(mstring, data, size);
  return mstring;
}

void mckits_string_drop(struct MckitsString* mstring) {
  mckits_string_drop_data(mstring);
  free(mstring);
}

void mckits_string_drop_data(struct MckitsString* mstring) {
  if (mstring->data != NULL) {
    mstring->cap = 0;
    mstring->len = 0;
    free(mstring->data);
    mstring->data = NULL;
  }
}

void mckits_string_clear(struct MckitsString* mstring) { mstring->len = 0; }

void mckits_string_to_lower(struct MckitsString* mstring) {
  for (size_t i = 0; i < mstring->len; ++i) {
    mstring->data[i] = mckits_tolower(mstring->data[i]);
  }
}

void mckits_string_to_upper(struct MckitsString* mstring) {
  for (size_t i = 0; i < mstring->len; ++i) {
    mstring->data[i] = mckits_toupper(mstring->data[i]);
  }
}

struct MckitsString* mckits_string_clone(struct MckitsString* mstring) {
  return mckits_string_new((const char*)mstring->data);
}

struct MckitsStr mckits_string_view(struct MckitsString* mstring) {
  return mckits_str_initn((const char*)mstring->data, mstring->len);
}

void mckits_string_trim(struct MckitsString* mstring, const char* chars) {
  char m[256] = {0};
  size_t chars_length = strlen(chars);
  for (size_t i = 0; i < chars_length; ++i) {
    uint8_t c = (uint8_t)chars[i];
    m[c] = 1;
  }

  // trim left
  size_t left = 0;
  while (left < mstring->len) {
    uint8_t c = mstring->data[left];
    if (m[c]) {
      ++left;
    } else {
      break;
    }
  }

  if (left > 0) {
    for (size_t i = 0, j = left; j < mstring->len; ++i, ++j) {
      mstring->data[i] = mstring->data[j];
    }
    mstring->len -= left;
    mstring->data[mstring->len] = '\0';
  }

  // trim right
  int64_t right = (int64_t)mstring->len - 1;
  while (right > 0) {
    uint8_t c = mstring->data[right];
    if (m[c]) {
      --right;
    } else {
      break;
    }
  }
  mstring->len = right + 1;
  mstring->data[mstring->len] = '\0';
}

int mckits_string_start_with(struct MckitsString* mstring, const char* substr) {
  size_t substr_length = strlen(substr);
  if (substr_length > mstring->len) {
    return 0;
  }

  for (size_t i = 0; i < substr_length; ++i) {
    if ((uint8_t)substr[i] != mstring->data[i]) {
      return 0;
    }
  }

  return 1;
}

int mckits_string_end_with(struct MckitsString* mstring, const char* substr) {
  size_t substr_length = strlen(substr);
  if (substr_length > mstring->len) {
    return 0;
  }

  int64_t i = (int64_t)substr_length - 1;
  int64_t j = (int64_t)mstring->len - 1;
  while (i >= 0) {
    if ((uint8_t)substr[i] != mstring->data[j]) {
      return 0;
    }
    --i;
    --j;
  }

  return 1;
}

static void mckits_string_grow_size(struct MckitsString* mstring,
                                    size_t grow_size) {
  if (mstring->data == NULL) {
    mstring->cap = grow_size + 1;
    mstring->len = 0;
    mstring->data = mckits_malloc(mstring->cap);
  } else if (mstring->len + 1 + grow_size > mstring->cap) {
    size_t new_capacity =
        2 * (grow_size > mstring->cap ? grow_size : mstring->cap);
    void* new_buffer = mckits_malloc(new_capacity);

    memcpy(new_buffer, mstring->data, mstring->len + 1);
    free(mstring->data);
    mstring->data = new_buffer;
    mstring->cap = new_capacity;
  }
}

void mckits_string_push_char(struct MckitsString* mstring, char c) {
  mckits_string_grow_size(mstring, 1);

  mstring->data[mstring->len++] = (uint8_t)c;
  mstring->data[mstring->len] = '\0';
}

void mckits_string_push_cstring(struct MckitsString* mstring,
                                const char* cstring) {
  size_t cstring_len = strlen(cstring);
  mckits_string_grow_size(mstring, cstring_len);

  memcpy(mstring->data + mstring->len, cstring, cstring_len);
  mstring->data[mstring->len + cstring_len] = '\0';
  mstring->len += cstring_len;
}

void mckits_string_push_mstr(struct MckitsString* mstring,
                             struct MckitsStr mstr) {
  mckits_string_grow_size(mstring, mstr.len);

  memcpy(mstring->data + mstring->len, mstr.data, mstr.len);
  mstring->data[mstring->len + mstr.len] = '\0';
  mstring->len += mstr.len;
}

void mckits_string_push_mstring(struct MckitsString* mstring,
                                const struct MckitsString* appended) {
  mckits_string_grow_size(mstring, appended->len);

  memcpy(mstring->data + mstring->len, appended->data, appended->len);
  mstring->data[mstring->len + appended->len] = '\0';
  mstring->len += appended->len;
}

char* mckits_string_take(struct MckitsString* mstring) {
  char* data = (char*)mstring->data;
  mstring->cap = 0;
  mstring->len = 0;
  mstring->data = NULL;
  return data;
}

struct MckitsString* mckits_string_from_int(int num) {
  struct MckitsString* mstring =
      (struct MckitsString*)mckits_malloc(sizeof(struct MckitsString));

  int len = snprintf(NULL, 0, "%d", num);
  uint8_t* ptr = (uint8_t*)mckits_malloc(len + 1);
  sprintf((char*)ptr, "%d", num);

  mstring->len = len;
  mstring->cap = len + 1;
  mstring->data = ptr;
  return mstring;
}

struct MckitsString* mckits_string_from_int64(int64_t num) {
  struct MckitsString* mstring =
      (struct MckitsString*)mckits_malloc(sizeof(struct MckitsString));

  int len = snprintf(NULL, 0, "%" PRId64, num);
  uint8_t* ptr = (uint8_t*)mckits_malloc(len + 1);
  sprintf((char*)ptr, "%" PRId64, num);

  mstring->len = len;
  mstring->cap = len + 1;
  mstring->data = ptr;
  return mstring;
}

int mckits_string_to_int(struct MckitsString* mstring) {
  return atoi((const char*)mstring->data);
}

int64_t mckits_string_to_int64(struct MckitsString* mstring) {
  return (int64_t)atoll((const char*)mstring->data);
}

int mckits_string_equal(const struct MckitsString* a,
                        const struct MckitsString* b) {
  return mckits_strcmp(a->data, b->data) == 0 ? 1 : 0;
}

int mckits_string_equal_str(const struct MckitsString* mstring,
                            const struct MckitsStr* mstr) {
  return mckits_strcmp(mstring->data, mstr->data) == 0 ? 1 : 0;
}

int mckits_string_equal_cstring(const struct MckitsString* mstring,
                                const char* cstr) {
  return mckits_strcmp(mstring->data, cstr) == 0 ? 1 : 0;
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
  uint8_t* dst = (uint8_t*)mckits_malloc(src->len + 1);
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
  for (;;) {
    int c1 = (int)*s1++;
    int c2 = (int)*s2++;

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
  while (n) {
    int c1 = (int)*s1++;
    int c2 = (int)*s2++;

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
