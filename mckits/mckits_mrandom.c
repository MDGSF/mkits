#include "mckits_mrandom.h"

#include <stdlib.h>
#include <time.h>

void mckits_random_seed() { srand(time(NULL)); }

void mckits_random_str(void* buf, size_t size) {
  char* buffer = (char*)buf;
  static const char charset[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  const size_t charset_size = sizeof(charset) - 1;

  for (size_t i = 0; i < size; i++) {
    buffer[i] = charset[rand() % charset_size];
  }

  buffer[size - 1] = '\0';
}

int mckits_random_num(int start, int end) {
  int num = start + rand() % (end - start);
  return num;
}

