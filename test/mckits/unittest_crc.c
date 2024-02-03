#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "mckits/mstl/hash/mckits_crc.h"

void test01() {
  {
    const char* data = "hello";
    size_t size = strlen(data);
    uint32_t expected = 536871123;
    uint32_t result = mckits_crc((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "world";
    size_t size = strlen(data);
    uint32_t expected = 3489661131;
    uint32_t result = mckits_crc((const uint8_t*)data, size);
    assert(result == expected);
  }
}

int main() {
  test01();
  return 0;
}
