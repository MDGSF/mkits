#include <assert.h>
#include <string.h>

#include "mckits_strconv.h"

void test01() {
  const char* str01 = "123";
  int num = mckits_char_string_to_int(str01);

  char str02[16] = {0};
  size_t str02_size = sizeof(str02);
  mckits_int_to_char_string(num, str02, str02_size);
  assert(strcmp(str02, str01) == 0);
}

void test02() {
  const char* str01 = "-123";
  int num = mckits_char_string_to_int(str01);

  char str02[16] = {0};
  size_t str02_size = sizeof(str02);
  mckits_int_to_char_string(num, str02, str02_size);
  assert(strcmp(str02, str01) == 0);
}

void test03() {
  const char* str01 = "-123";
  int64_t num = mckits_char_string_to_int64(str01);

  char str02[16] = {0};
  size_t str02_size = sizeof(str02);
  mckits_int64_to_char_string(num, str02, str02_size);
  assert(strcmp(str02, str01) == 0);
}

int main() {
  test01();
  test02();
  test03();
  return 0;
}
