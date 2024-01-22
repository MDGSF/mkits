#include "mckits_strconv.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int mckits_char_string_to_int(const char* str) { return atoi(str); }

void mckits_int_to_char_string(int num, char* str, size_t size) {
  snprintf(str, size, "%d", num);
}

int64_t mckits_char_string_to_int64(const char* str) {
  return (int64_t)atoll(str);
}

void mckits_int64_to_char_string(int64_t num, char* str, size_t size) {
  snprintf(str, size, "%" PRId64, num);
}
