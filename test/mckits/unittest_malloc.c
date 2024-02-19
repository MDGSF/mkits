#include "mckits/mlibc/mckits_malloc.h"

void test01() {
  void* p = mckits_malloc(128);
  mckits_free(p);
}

void test02() {
  void* p = mckits_calloc(10, 8);
  mckits_free(p);
}

void test03() {
  void* p = mckits_calloc(10, 8);
  p = mckits_realloc(p, 128);
  mckits_free(p);
}

int main() {
  test01();
  test02();
  test03();
  return 0;
}
