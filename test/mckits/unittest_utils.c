#include <assert.h>

#include "mckits/mlibc/mckits_mlibc_utils.h"

void test01() {
  int ret = 0;
  int array[] = {1, 3, 5, 2, 9, 9, 7};
  size_t size = sizeof(array) / sizeof(int);
  ret = found_int_array(0, array, size);
  assert(ret == 0);
  for (int i = 0; i < size; ++i) {
    ret = found_int_array(array[i], array, size);
    assert(ret == 1);
  }
}

void test02() {
  assert(mckits_fequal(1.0f, 1.0f) == 1);
  assert(mckits_fequal(1.1f, 1.1f) == 1);
  assert(mckits_fequal(1.0f, 1.1f) == 0);
}

void test03() {
  assert(mckits_dequal(1.0, 1.0) == 1);
  assert(mckits_dequal(1.1, 1.1) == 1);
  assert(mckits_dequal(1.0, 1.1) == 0);
}

int main() {
  test01();
  test02();
  test03();
  return 0;
}
