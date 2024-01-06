#include "mckits_mrandom.h"

#include <stdlib.h>
#include <time.h>

void mckits_random_seed() { srand(time(NULL)); }

void mckits_random_str(char* buf, size_t size) {
  static const char charset[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  const size_t charset_size = sizeof(charset) - 1;

  for (size_t i = 0; i < size; ++i) {
    buf[i] = charset[rand() % charset_size];
  }

  buf[size - 1] = '\0';
}

void mckits_random_bytes(uint8_t* buf, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    buf[i] = (uint8_t)mckits_random_num(0, 256);
  }
}

int mckits_random_num(int start, int end) {
  return start + rand() % (end - start);
}
