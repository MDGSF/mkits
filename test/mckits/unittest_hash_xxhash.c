#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "mckits/mstl/hash/mckits_hash_xxhash.h"

void test01() {
  {
    const char* buf = "PK";
    size_t size = strlen(buf);
    uint64_t expected = 3191504414677133098U;
    uint64_t result = mckits_hash_xxhash3((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "ht";
    size_t size = strlen(buf);
    uint64_t expected = 15733998587082594279U;
    uint64_t result = mckits_hash_xxhash3((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "Mm";
    size_t size = strlen(buf);
    uint64_t expected = 16464988609024278850U;
    uint64_t result = mckits_hash_xxhash3((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "18n";
    size_t size = strlen(buf);
    uint64_t expected = 14880416429365758830U;
    uint64_t result = mckits_hash_xxhash3((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "L9K";
    size_t size = strlen(buf);
    uint64_t expected = 15291570257867040153U;
    uint64_t result = mckits_hash_xxhash3((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "8eM";
    size_t size = strlen(buf);
    uint64_t expected = 8221917683895099477U;
    uint64_t result = mckits_hash_xxhash3((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "Gn7C";
    size_t size = strlen(buf);
    uint64_t expected = 18216327666997020097U;
    uint64_t result = mckits_hash_xxhash3((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "ctT9";
    size_t size = strlen(buf);
    uint64_t expected = 13436891101824691664U;
    uint64_t result = mckits_hash_xxhash3((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "wKSB";
    size_t size = strlen(buf);
    uint64_t expected = 12148518256363013953U;
    uint64_t result = mckits_hash_xxhash3((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "FebW3";
    size_t size = strlen(buf);
    uint64_t expected = 4042295766384336435U;
    uint64_t result = mckits_hash_xxhash3((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "7VI5u";
    size_t size = strlen(buf);
    uint64_t expected = 10104091658959041257U;
    uint64_t result = mckits_hash_xxhash3((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "1yhc3";
    size_t size = strlen(buf);
    uint64_t expected = 12013036818543618209U;
    uint64_t result = mckits_hash_xxhash3((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "avuaOb";
    size_t size = strlen(buf);
    uint64_t expected = 16705972109204663675U;
    uint64_t result = mckits_hash_xxhash3((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "vyJcXy";
    size_t size = strlen(buf);
    uint64_t expected = 18435529287901850244U;
    uint64_t result = mckits_hash_xxhash3((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "ZzsRwp";
    size_t size = strlen(buf);
    uint64_t expected = 5501500313270351378U;
    uint64_t result = mckits_hash_xxhash3((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "5iUzahE";
    size_t size = strlen(buf);
    uint64_t expected = 943088228797350894U;
    uint64_t result = mckits_hash_xxhash3((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "aYatja7";
    size_t size = strlen(buf);
    uint64_t expected = 9000660577566002571U;
    uint64_t result = mckits_hash_xxhash3((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "aqGHss6";
    size_t size = strlen(buf);
    uint64_t expected = 15080060807288059879U;
    uint64_t result = mckits_hash_xxhash3((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "hteYQrpJ";
    size_t size = strlen(buf);
    uint64_t expected = 1510721050321781855U;
    uint64_t result = mckits_hash_xxhash3((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "76AcBAan";
    size_t size = strlen(buf);
    uint64_t expected = 4598886285152060999U;
    uint64_t result = mckits_hash_xxhash3((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "tuBoDzF9";
    size_t size = strlen(buf);
    uint64_t expected = 11963780312868513173U;
    uint64_t result = mckits_hash_xxhash3((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }
}

int main() {
  test01();
  return 0;
}
