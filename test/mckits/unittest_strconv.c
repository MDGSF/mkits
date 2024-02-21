#include <assert.h>
#include <string.h>

#include "mckits/mlibc/mckits_mlibc_utils.h"
#include "mckits/mstl/mckits_strconv.h"

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

void test04() {
  int num = 123;
  char* str = mckits_int_to_char_string_heap(num);
  assert(strcmp(str, "123") == 0);
  free(str);
}

void test05() {
  int64_t num = 123;
  char* str = mckits_int64_to_char_string_heap(num);
  assert(strcmp(str, "123") == 0);
  free(str);
}

void test06() {
  float num = mckits_char_string_to_float("123.456");
  assert(1 == mckits_fequal(num, 123.456));
}

void test07() {
  double num = mckits_char_string_to_double("123.456");
  assert(1 == mckits_dequal(num, 123.456));
}

int main() {
  test01();
  test02();
  test03();
  test04();
  test05();
  test06();
  test07();
  return 0;
}
