#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "mckits/mstl/mckits_string.h"

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

void test10() {
  struct MckitsStr str = mckits_str("hello world");
  const char* p = mckits_strstr(str.data, "world");
  assert(mckits_strlen(p) == 5);
  assert(mckits_strcmp(p, "world") == 0);

  const char* p2 = mckits_strstr(str.data, "now");
  assert(p2 == NULL);
}

void test11() {
  struct MckitsStr str = mckits_str("hello");
  const char* p = mckits_strchr(str.data, 'e');
  assert(mckits_strlen(p) == 4);
  assert(mckits_strcmp(p, "ello") == 0);

  const char* p2 = mckits_strchr(str.data, 'z');
  assert(p2 == NULL);
}

void test12() {
  struct MckitsStr str = mckits_str("hello world");
  uint8_t* start = str.data + 1;
  uint8_t* end = str.data + 7;
  uint8_t* p = mckits_strlchr(start, end, 'e');
  assert(mckits_strlen(p) == 10);
  assert(mckits_strcmp(p, "ello world") == 0);

  uint8_t* p2 = mckits_strlchr(start, end, 'd');
  assert(p2 == NULL);
}

void test13() {
  char src[] = "hello";
  char dst[1024] = {0};
  uint8_t* p1 = mckits_copy((uint8_t*)dst, (uint8_t*)src, strlen(src) + 1);
  uint8_t* p2 = (uint8_t*)(dst + strlen(src) + 1);
  assert(p1 == p2);
  assert(mckits_strlen(dst) == 5);
  assert(mckits_strcmp(dst, "hello") == 0);
}

void test14() {
  struct MckitsStr str = mckits_str("hello");
  uint8_t dst[1024];
  uint8_t* p1 = mckits_cpystrn(dst, str.data, str.len + 1);
  uint8_t* p2 = (uint8_t*)(dst + str.len);
  assert(p1 == p2);
  assert(mckits_strlen(dst) == 5);
  assert(mckits_strcmp(dst, "hello") == 0);
}

void test15() {
  struct MckitsStr str = mckits_str("hello");
  uint8_t dst[1024];
  uint8_t* p1 = mckits_cpystrn(dst, str.data, 0);
  assert(p1 == dst);
}

void test16() {
  struct MckitsStr s1 = mckits_str("hello");
  struct MckitsStr s2 = mckits_str("HeLLo");
  assert(0 == mckits_strcasecmp(s1.data, s2.data));
  assert(0 == mckits_strncasecmp(s1.data, s2.data, s1.len));
}

void test17() {
  const char* s = "hello";
  struct MckitsStr str = mckits_str_init(s);
  assert(str.len == 5);
  assert(mckits_strcmp(str.data, s) == 0);

  struct MckitsStr str2 = mckits_str_initn(s, strlen(s));
  assert(str2.len == 5);
  assert(mckits_strcmp(str2.data, s) == 0);
}

void test18() {
  struct MckitsStr str = mckits_str_init("hello");
  uint8_t* pdst = mckits_pstrdup(&str);
  if (pdst == NULL) {
    printf("mckits_pstrdup return NULL\n");
    return;
  }

  assert(mckits_strlen(pdst) == 5);
  assert(mckits_strcmp(pdst, "hello") == 0);
  free(pdst);
}

void test19() {
  struct MckitsStr src = mckits_str_init("hello");
  struct MckitsString dst = mckits_strdup(src);
  assert(src.len == dst.len);
  assert(mckits_strcmp(src.data, dst.data) == 0);
  mckits_string_drop_data(&dst);
}

void test20() {
  struct MckitsString mstring;
  mckits_string_init(&mstring, "hello");
  assert(mstring.cap == 6);
  assert(mstring.len == 5);
  assert(mstring.data != NULL);
  assert(mckits_strcmp(mstring.data, "hello") == 0);
  mckits_string_drop_data(&mstring);
}

void test21() {
  struct MckitsString mstring;
  mckits_string_init(&mstring, NULL);
  assert(mstring.cap == 0);
  assert(mstring.len == 0);
  assert(mstring.data == NULL);
  mckits_string_drop_data(&mstring);
}

void test22() {
  struct MckitsString mstring;
  mckits_string_init(&mstring, "");
  assert(mstring.cap == 1);
  assert(mstring.len == 0);
  assert(mstring.data != NULL);
  assert(mckits_strcmp(mstring.data, "") == 0);
  mckits_string_drop_data(&mstring);
}

void test23() {
  struct MckitsString* mstring = mckits_string_new("hello");
  assert(mstring->cap == 6);
  assert(mstring->len == 5);
  assert(mstring->data != NULL);
  assert(mckits_strcmp(mstring->data, "hello") == 0);
  mckits_string_drop(mstring);
}

void test24() {
  struct MckitsString* mstring = mckits_string_new("hello");
  struct MckitsString* mstring2 = mckits_string_clone(mstring);
  assert(mstring->cap == 6);
  assert(mstring->len == 5);
  assert(mstring->data != NULL);
  assert(mckits_strcmp(mstring->data, "hello") == 0);
  assert(mstring2->cap == 6);
  assert(mstring2->len == 5);
  assert(mstring2->data != NULL);
  assert(mckits_strcmp(mstring2->data, "hello") == 0);
  mckits_string_drop(mstring);
  mckits_string_drop(mstring2);
}

void test25() {
  struct MckitsString* mstring = mckits_string_new("hello");
  assert(mstring->cap == 6);
  assert(mstring->len == 5);
  assert(mstring->data != NULL);
  assert(mckits_strcmp(mstring->data, "hello") == 0);

  struct MckitsStr str = mckits_string_view(mstring);
  assert(str.len == 5);
  assert(str.data == mstring->data);
  assert(mckits_strcmp(str.data, "hello") == 0);

  mckits_string_drop(mstring);
}

void test26() {
  struct MckitsString* mstring = mckits_string_new("HeLLo World");
  assert(mstring->cap == 12);
  assert(mstring->len == 11);
  assert(mstring->data != NULL);
  assert(mckits_strcmp(mstring->data, "HeLLo World") == 0);

  mckits_string_to_lower(mstring);
  assert(mstring->cap == 12);
  assert(mstring->len == 11);
  assert(mstring->data != NULL);
  assert(mckits_strcmp(mstring->data, "hello world") == 0);

  mckits_string_drop(mstring);
}

void test27() {
  struct MckitsString* mstring = mckits_string_new("HeLLo World");
  assert(mstring->cap == 12);
  assert(mstring->len == 11);
  assert(mstring->data != NULL);
  assert(mckits_strcmp(mstring->data, "HeLLo World") == 0);

  mckits_string_to_upper(mstring);
  assert(mstring->cap == 12);
  assert(mstring->len == 11);
  assert(mstring->data != NULL);
  assert(mckits_strcmp(mstring->data, "HELLO WORLD") == 0);

  mckits_string_drop(mstring);
}

void test28() {
  const char* data = "  HeLLo World   ";
  size_t data_length = strlen(data);
  struct MckitsString* mstring = mckits_string_new(data);
  assert(mstring->cap == data_length + 1);
  assert(mstring->len == data_length);
  assert(mstring->data != NULL);
  assert(mckits_strcmp(mstring->data, data) == 0);

  mckits_string_trim(mstring, " \r\n\t");

  assert(mstring->cap == data_length + 1);
  assert(mstring->len == 11);
  assert(mstring->data != NULL);
  assert(mckits_strcmp(mstring->data, "HeLLo World") == 0);

  mckits_string_drop(mstring);
}

void test29() {
  struct MckitsString* mstring = mckits_string_new("hello");
  assert(mstring->cap == 6);
  assert(mstring->len == 5);
  assert(mstring->data != NULL);
  assert(mckits_strcmp(mstring->data, "hello") == 0);

  assert(1 == mckits_string_start_with(mstring, "h"));
  assert(1 == mckits_string_start_with(mstring, "he"));
  assert(1 == mckits_string_start_with(mstring, "hel"));
  assert(1 == mckits_string_start_with(mstring, "hell"));
  assert(1 == mckits_string_start_with(mstring, "hello"));

  assert(0 == mckits_string_start_with(mstring, "hello world"));
  assert(0 == mckits_string_start_with(mstring, "world"));

  mckits_string_drop(mstring);
}

void test30() {
  struct MckitsString* mstring = mckits_string_new("hello");
  assert(mstring->cap == 6);
  assert(mstring->len == 5);
  assert(mstring->data != NULL);
  assert(mckits_strcmp(mstring->data, "hello") == 0);

  assert(1 == mckits_string_end_with(mstring, "o"));
  assert(1 == mckits_string_end_with(mstring, "lo"));
  assert(1 == mckits_string_end_with(mstring, "llo"));
  assert(1 == mckits_string_end_with(mstring, "ello"));
  assert(1 == mckits_string_end_with(mstring, "hello"));

  assert(0 == mckits_string_end_with(mstring, "hello world"));
  assert(0 == mckits_string_end_with(mstring, "world"));

  mckits_string_drop(mstring);
}

void test31() {
  int num = 123;
  struct MckitsString* mstring = mckits_string_from_int(num);
  assert(mckits_strcmp(mstring->data, "123") == 0);
  mckits_string_drop(mstring);
}

void test32() {
  int num = -123;
  struct MckitsString* mstring = mckits_string_from_int(num);
  assert(mckits_strcmp(mstring->data, "-123") == 0);
  mckits_string_drop(mstring);
}

void test33() {
  int64_t num = 123;
  struct MckitsString* mstring = mckits_string_from_int64(num);
  assert(mckits_strcmp(mstring->data, "123") == 0);
  mckits_string_drop(mstring);
}

void test34() {
  int64_t num = -123;
  struct MckitsString* mstring = mckits_string_from_int64(num);
  assert(mckits_strcmp(mstring->data, "-123") == 0);
  mckits_string_drop(mstring);
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
  test10();
  test11();
  test12();
  test13();
  test14();
  test15();
  test16();
  test17();
  test18();
  test19();
  test20();
  test21();
  test22();
  test23();
  test24();
  test25();
  test26();
  test27();
  test28();
  test29();
  test30();
  test31();
  test32();
  test33();
  test34();
  return 0;
}
