#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mckits/core/encoding/mckits_encoding_iniparser.h"
#include "mckits/mlibc/mckits_mlibc_utils.h"

void test01() {
  struct MckitsIniParser* iniparser =
      mckits_iniparser_new(MCKITS_INIPARSER_DEFAULT_DELIMITERS,
                           MCKITS_INIPARSER_DEFAULT_COMMENT_PREFIXS);

  {
    char* data = mckits_iniparser_to_cstring(iniparser);
    assert(data == NULL);
  }

  const char* data =
      "[section1]\n"
      "name=John\n"
      "age=18\n"
      "\n"
      "[section2]\n"
      "book_name=harry potter\n"
      "price=28\n";

  int ret = mckits_iniparser_from_cstring(iniparser, data);
  assert(ret == 0);

  assert(1 == mckits_iniparser_has_section(iniparser, "section1"));
  assert(1 == mckits_iniparser_has_section(iniparser, "section2"));
  assert(0 == mckits_iniparser_has_section(iniparser, "section3"));

  assert(1 == mckits_iniparser_has_entry(iniparser, "section1", "name"));
  assert(1 == mckits_iniparser_has_entry(iniparser, "section1", "age"));
  assert(1 == mckits_iniparser_has_entry(iniparser, "section2", "book_name"));
  assert(1 == mckits_iniparser_has_entry(iniparser, "section2", "price"));
  assert(0 == mckits_iniparser_has_entry(iniparser, "section3", "price"));
  assert(0 == mckits_iniparser_has_entry(iniparser, "section1", "nono"));

  {
    char* value = NULL;
    assert(0 == mckits_iniparser_get(iniparser, "section1", "name", &value));
    assert(strcmp(value, "John") == 0);
  }
  {
    char* value = NULL;
    assert(0 == mckits_iniparser_get(iniparser, "section1", "age", &value));
    assert(strcmp(value, "18") == 0);
  }
  {
    char* value = NULL;
    assert(0 ==
           mckits_iniparser_get(iniparser, "section2", "book_name", &value));
    assert(strcmp(value, "harry potter") == 0);
  }
  {
    char* value = NULL;
    assert(0 == mckits_iniparser_get(iniparser, "section2", "price", &value));
    assert(strcmp(value, "28") == 0);
  }

  {
    char* value = NULL;
    assert(-1 == mckits_iniparser_get(iniparser, "section3", "price", &value));
  }
  {
    char* value = NULL;
    assert(-1 == mckits_iniparser_get(iniparser, "section1", "price", &value));
  }

  {
    int value = 0;
    assert(0 == mckits_iniparser_get_int(iniparser, "section1", "age", &value));
    assert(value == 18);
  }
  {
    int value = 0;
    assert(0 ==
           mckits_iniparser_get_int(iniparser, "section2", "price", &value));
    assert(value == 28);
  }

  {
    float value = 0;
    assert(0 ==
           mckits_iniparser_get_float(iniparser, "section1", "age", &value));
    assert(mckits_fequal(value, 18.0f));
  }
  {
    float value = 0;
    assert(0 ==
           mckits_iniparser_get_float(iniparser, "section2", "price", &value));
    assert(mckits_fequal(value, 28.0f));
  }

  mckits_iniparser_drop(iniparser);
}

void test02() {
  struct MckitsIniParser* iniparser =
      mckits_iniparser_new(MCKITS_INIPARSER_DEFAULT_DELIMITERS,
                           MCKITS_INIPARSER_DEFAULT_COMMENT_PREFIXS);
  mckits_iniparser_drop(iniparser);
}

void test03() {
  struct MckitsIniParser* iniparser =
      mckits_iniparser_new(MCKITS_INIPARSER_DEFAULT_DELIMITERS,
                           MCKITS_INIPARSER_DEFAULT_COMMENT_PREFIXS);

  mckits_iniparser_set(iniparser, "section01", "e1", "v1");
  {
    char* value = NULL;
    assert(0 == mckits_iniparser_get(iniparser, "section01", "e1", &value));
    assert(strcmp(value, "v1") == 0);
  }

  mckits_iniparser_set(iniparser, "section01", "e1", "v2");
  {
    char* value = NULL;
    assert(0 == mckits_iniparser_get(iniparser, "section01", "e1", &value));
    assert(strcmp(value, "v2") == 0);
  }

  mckits_iniparser_set(iniparser, "section01", "e2", "v2");
  mckits_iniparser_set(iniparser, "section01", "e3", "v3");
  mckits_iniparser_set(iniparser, "section02", "d1", "z1");
  mckits_iniparser_set(iniparser, "section02", "d2", "z2");
  mckits_iniparser_set(iniparser, "section02", "d3", "z3");

  {
    char* value = NULL;
    assert(0 == mckits_iniparser_get(iniparser, "section01", "e1", &value));
    assert(strcmp(value, "v2") == 0);
  }
  {
    char* value = NULL;
    assert(0 == mckits_iniparser_get(iniparser, "section01", "e2", &value));
    assert(strcmp(value, "v2") == 0);
  }
  {
    char* value = NULL;
    assert(0 == mckits_iniparser_get(iniparser, "section01", "e3", &value));
    assert(strcmp(value, "v3") == 0);
  }
  {
    char* value = NULL;
    assert(0 == mckits_iniparser_get(iniparser, "section02", "d1", &value));
    assert(strcmp(value, "z1") == 0);
  }
  {
    char* value = NULL;
    assert(0 == mckits_iniparser_get(iniparser, "section02", "d2", &value));
    assert(strcmp(value, "z2") == 0);
  }
  {
    char* value = NULL;
    assert(0 == mckits_iniparser_get(iniparser, "section02", "d3", &value));
    assert(strcmp(value, "z3") == 0);
  }

  mckits_iniparser_remove_entry(iniparser, "section02", "d2");
  assert(0 == mckits_iniparser_has_entry(iniparser, "section2", "d2"));
  {
    char* value = NULL;
    assert(-1 == mckits_iniparser_get(iniparser, "section02", "d2", &value));
  }

  assert(1 == mckits_iniparser_has_section(iniparser, "section02"));
  mckits_iniparser_remove_section(iniparser, "section02");
  assert(0 == mckits_iniparser_has_section(iniparser, "section02"));

  mckits_iniparser_drop(iniparser);
}

void test04() {
  struct MckitsIniParser* iniparser =
      mckits_iniparser_new(MCKITS_INIPARSER_DEFAULT_DELIMITERS,
                           MCKITS_INIPARSER_DEFAULT_COMMENT_PREFIXS);

  mckits_iniparser_set(iniparser, "section", "n1", "0");
  mckits_iniparser_set(iniparser, "section", "n2", "false");
  mckits_iniparser_set(iniparser, "section", "n3", "no");
  mckits_iniparser_set(iniparser, "section", "n4", "off");

  mckits_iniparser_set(iniparser, "section", "m1", "1");
  mckits_iniparser_set(iniparser, "section", "m2", "true");
  mckits_iniparser_set(iniparser, "section", "m3", "yes");
  mckits_iniparser_set(iniparser, "section", "m4", "on");

  {
    int value = 0;
    assert(0 ==
           mckits_iniparser_get_boolean(iniparser, "section", "n1", &value));
    assert(value == 0);
  }
  {
    int value = 0;
    assert(0 ==
           mckits_iniparser_get_boolean(iniparser, "section", "n2", &value));
    assert(value == 0);
  }
  {
    int value = 0;
    assert(0 ==
           mckits_iniparser_get_boolean(iniparser, "section", "n3", &value));
    assert(value == 0);
  }
  {
    int value = 0;
    assert(0 ==
           mckits_iniparser_get_boolean(iniparser, "section", "n4", &value));
    assert(value == 0);
  }

  {
    int value = 0;
    assert(0 ==
           mckits_iniparser_get_boolean(iniparser, "section", "m1", &value));
    assert(value == 1);
  }
  {
    int value = 0;
    assert(0 ==
           mckits_iniparser_get_boolean(iniparser, "section", "m2", &value));
    assert(value == 1);
  }
  {
    int value = 0;
    assert(0 ==
           mckits_iniparser_get_boolean(iniparser, "section", "m3", &value));
    assert(value == 1);
  }
  {
    int value = 0;
    assert(0 ==
           mckits_iniparser_get_boolean(iniparser, "section", "m4", &value));
    assert(value == 1);
  }

  {
    int value = 0;
    assert(-1 == mckits_iniparser_get_boolean(iniparser, "invalid_section",
                                              "m4", &value));
  }
  {
    int value = 0;
    assert(-1 == mckits_iniparser_get_boolean(iniparser, "section",
                                              "invalid_entry", &value));
  }
  {
    mckits_iniparser_set(iniparser, "section", "kk", "invalid_bool_value");

    int value = 0;
    assert(-2 ==
           mckits_iniparser_get_boolean(iniparser, "section", "kk", &value));
  }

  mckits_iniparser_drop(iniparser);
}

void test05() {
  struct MckitsIniParser* iniparser =
      mckits_iniparser_new(MCKITS_INIPARSER_DEFAULT_DELIMITERS,
                           MCKITS_INIPARSER_DEFAULT_COMMENT_PREFIXS);

  const char* data =
      "ip=127.0.0.1\n"
      "port=12306\n"
      "[section1]\n"
      "name=John\n"
      "age=18\n"
      "\n"
      "[section2]\n"
      "book_name=harry potter\n"
      "price=28\n";

  int ret = mckits_iniparser_from_cstring(iniparser, data);
  assert(ret == 0);

  assert(1 == mckits_iniparser_has_entry(
                  iniparser, MCKITS_INIPARSER_DEFAULT_SECTION, "ip"));
  assert(1 == mckits_iniparser_has_entry(
                  iniparser, MCKITS_INIPARSER_DEFAULT_SECTION, "port"));

  mckits_iniparser_drop(iniparser);
}

int main() {
  test01();
  test02();
  test03();
  test04();
  test05();
  return 0;
}
