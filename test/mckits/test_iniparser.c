#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mckits/core/encoding/mckits_encoding_iniparser.h"

void test01() {
  struct MckitsIniParser* iniparser =
      mckits_iniparser_new(MCKITS_INIPARSER_DEFAULT_DELIMITERS,
                           MCKITS_INIPARSER_DEFAULT_COMMENT_PREFIXS);

  {
    char* data = mckits_iniparser_to_cstring(iniparser);
    assert(data == NULL);
  }

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

  {
    char* data = mckits_iniparser_to_cstring(iniparser);
    assert(data != NULL);
    printf("%ld\n", strlen(data));
    printf("%s\n", data);
    free(data);
  }

  mckits_iniparser_drop(iniparser);
}

int main() {
  test01();
  return 0;
}
