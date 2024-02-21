#include "mckits/mstl/mckits_strconv.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "mckits/mlibc/mckits_malloc.h"

int mckits_char_string_to_int(const char* str) { return atoi(str); }

void mckits_int_to_char_string(int num, char* str, size_t size) {
  snprintf(str, size, "%d", num);
}

char* mckits_int_to_char_string_heap(int num) {
  int len = snprintf(NULL, 0, "%d", num);
  char* ptr = (char*)mckits_malloc(len + 1);
  sprintf(ptr, "%d", num);
  return ptr;
}

int64_t mckits_char_string_to_int64(const char* str) {
  return (int64_t)atoll(str);
}

void mckits_int64_to_char_string(int64_t num, char* str, size_t size) {
  snprintf(str, size, "%" PRId64, num);
}

char* mckits_int64_to_char_string_heap(int64_t num) {
  int len = snprintf(NULL, 0, "%" PRId64, num);
  char* ptr = (char*)mckits_malloc(len + 1);
  sprintf(ptr, "%" PRId64, num);
  return ptr;
}

float mckits_char_string_to_float(const char* str) { return strtof(str, NULL); }

double mckits_char_string_to_double(const char* str) {
  return strtod(str, NULL);
}
