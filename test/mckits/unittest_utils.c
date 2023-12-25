#include <assert.h>

#include "mckits_utils.h"

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

int main() {
  test01();
  return 0;
}
