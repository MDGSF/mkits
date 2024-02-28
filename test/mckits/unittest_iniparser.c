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

int main() {
  test01();
  return 0;
}
