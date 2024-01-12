#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "mckits_string.h"

void test01() {
  const char* data = "hello";
  struct MckitsStr str = mckits_str_init(data);
  assert(str.len == mckits_strlen(data));
  assert(mckits_strcmp(str.data, data) == 0);
}

void test02() {
  const char* data = "hello";
  struct MckitsStr str = mckits_str_initn(data, strlen(data));
  assert(strlen(data) == mckits_strlen(data));
  assert(str.len == mckits_strlen(data));
  assert(mckits_strcmp(str.data, data) == 0);
}

void test03() {
  const char* data = "hello";
  // struct MckitsStr str = mckits_str(data);  // invalid usage
  struct MckitsStr str = mckits_str("hello");  // can only use str literal
  assert(str.len == mckits_strlen(data));
  assert(mckits_strcmp(str.data, data) == 0);
}

void test04() {
  struct MckitsStr str = mckits_null_str;
  assert(str.len == 0);
  assert(str.data == NULL);
}

void test05() {
  struct MckitsStr str = mckits_null_str;
  assert(str.len == 0);
  assert(str.data == NULL);

  mckits_str_set(&str, "hello");  // can only use str literal

  const char* data = "hello";
  assert(str.len == mckits_strlen(data));
  assert(mckits_strcmp(str.data, data) == 0);

  mckits_str_null(&str);
  assert(str.len == 0);
  assert(str.data == NULL);
}

void test06() {
  assert(mckits_tolower('a') == 'a');
  assert(mckits_tolower('A') == 'a');
  assert(mckits_toupper('a') == 'A');
  assert(mckits_toupper('A') == 'A');
}

void test07() {
  struct MckitsStr str = mckits_str("HeLLo");
  char dst[1024] = {0};
  mckits_strlow((uint8_t*)dst, str.data, str.len);
  assert(strlen(dst) == str.len);
  assert(strcmp(dst, "hello") == 0);
  assert(mckits_strcmp(dst, "hello") == 0);
  assert(mckits_strncmp(dst, "hello", str.len) == 0);
}

void test08() {
  struct MckitsStr str = mckits_str("HeLLo");
  char dst[1024] = {0};
  mckits_strupper((uint8_t*)dst, str.data, str.len);
  assert(strlen(dst) == str.len);
  assert(strcmp(dst, "HELLO") == 0);
  assert(mckits_strcmp(dst, "HELLO") == 0);
  assert(mckits_strncmp(dst, "HELLO", str.len) == 0);
}

void test09() {
  struct MckitsStr str = mckits_str("hello");
  assert(mckits_strlen(str.data) == strlen("hello"));
  assert(mckits_strnlen(str.data, 8) == 5);
  assert(mckits_strnlen(str.data, 5) == 5);
  assert(mckits_strnlen(str.data, 2) == 2);
}

int main() {
  test01();
  test02();
  test03();
  test04();
  test05();
  test06();
  test07();
  test08();
  test09();
  return 0;
}
