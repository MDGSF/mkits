#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "mckits/mstl/hash/mckits_hash_sip.h"

void test01() {
  {
    const char* buf = "PK";
    size_t size = strlen(buf);
    uint64_t expected = 5961479118311130131U;
    uint64_t result = mckits_hash_sip((const uint8_t*)buf, size, 0, 0);
    assert(expected == result);
  }

  {
    const char* buf = "ht";
    size_t size = strlen(buf);
    uint64_t expected = 17213871749731334157U;
    uint64_t result = mckits_hash_sip((const uint8_t*)buf, size, 0, 0);
    assert(expected == result);
  }

  {
    const char* buf = "Mm";
    size_t size = strlen(buf);
    uint64_t expected = 15034430157673253290U;
    uint64_t result = mckits_hash_sip((const uint8_t*)buf, size, 0, 0);
    assert(expected == result);
  }

  {
    const char* buf = "18n";
    size_t size = strlen(buf);
    uint64_t expected = 10777626957567890229U;
    uint64_t result = mckits_hash_sip((const uint8_t*)buf, size, 0, 0);
    assert(expected == result);
  }

  {
    const char* buf = "L9K";
    size_t size = strlen(buf);
    uint64_t expected = 8759348507632324864U;
    uint64_t result = mckits_hash_sip((const uint8_t*)buf, size, 0, 0);
    assert(expected == result);
  }

  {
    const char* buf = "8eM";
    size_t size = strlen(buf);
    uint64_t expected = 2028241112786491606U;
    uint64_t result = mckits_hash_sip((const uint8_t*)buf, size, 0, 0);
    assert(expected == result);
  }

  {
    const char* buf = "Gn7C";
    size_t size = strlen(buf);
    uint64_t expected = 240583625710850300U;
    uint64_t result = mckits_hash_sip((const uint8_t*)buf, size, 0, 0);
    assert(expected == result);
  }

  {
    const char* buf = "ctT9";
    size_t size = strlen(buf);
    uint64_t expected = 2879265359842772017U;
    uint64_t result = mckits_hash_sip((const uint8_t*)buf, size, 0, 0);
    assert(expected == result);
  }

  {
    const char* buf = "wKSB";
    size_t size = strlen(buf);
    uint64_t expected = 2983334852904065969U;
    uint64_t result = mckits_hash_sip((const uint8_t*)buf, size, 0, 0);
    assert(expected == result);
  }

  {
    const char* buf = "FebW3";
    size_t size = strlen(buf);
    uint64_t expected = 4369222370349536962U;
    uint64_t result = mckits_hash_sip((const uint8_t*)buf, size, 0, 0);
    assert(expected == result);
  }

  {
    const char* buf = "7VI5u";
    size_t size = strlen(buf);
    uint64_t expected = 7583028974509484502U;
    uint64_t result = mckits_hash_sip((const uint8_t*)buf, size, 0, 0);
    assert(expected == result);
  }

  {
    const char* buf = "1yhc3";
    size_t size = strlen(buf);
    uint64_t expected = 15025524304391929194U;
    uint64_t result = mckits_hash_sip((const uint8_t*)buf, size, 0, 0);
    assert(expected == result);
  }

  {
    const char* buf = "avuaOb";
    size_t size = strlen(buf);
    uint64_t expected = 14170038239078517283U;
    uint64_t result = mckits_hash_sip((const uint8_t*)buf, size, 0, 0);
    assert(expected == result);
  }

  {
    const char* buf = "vyJcXy";
    size_t size = strlen(buf);
    uint64_t expected = 6216964034972035794U;
    uint64_t result = mckits_hash_sip((const uint8_t*)buf, size, 0, 0);
    assert(expected == result);
  }

  {
    const char* buf = "ZzsRwp";
    size_t size = strlen(buf);
    uint64_t expected = 12523562819383763175U;
    uint64_t result = mckits_hash_sip((const uint8_t*)buf, size, 0, 0);
    assert(expected == result);
  }

  {
    const char* buf = "5iUzahE";
    size_t size = strlen(buf);
    uint64_t expected = 13718620065040076214U;
    uint64_t result = mckits_hash_sip((const uint8_t*)buf, size, 0, 0);
    assert(expected == result);
  }

  {
    const char* buf = "aYatja7";
    size_t size = strlen(buf);
    uint64_t expected = 5390171741417230112U;
    uint64_t result = mckits_hash_sip((const uint8_t*)buf, size, 0, 0);
    assert(expected == result);
  }

  {
    const char* buf = "aqGHss6";
    size_t size = strlen(buf);
    uint64_t expected = 4239846835044524553U;
    uint64_t result = mckits_hash_sip((const uint8_t*)buf, size, 0, 0);
    assert(expected == result);
  }

  {
    const char* buf = "hteYQrpJ";
    size_t size = strlen(buf);
    uint64_t expected = 13262362113317529092U;
    uint64_t result = mckits_hash_sip((const uint8_t*)buf, size, 0, 0);
    assert(expected == result);
  }

  {
    const char* buf = "76AcBAan";
    size_t size = strlen(buf);
    uint64_t expected = 4701315353236703725U;
    uint64_t result = mckits_hash_sip((const uint8_t*)buf, size, 0, 0);
    assert(expected == result);
  }

  {
    const char* buf = "tuBoDzF9";
    size_t size = strlen(buf);
    uint64_t expected = 14724437281408184846U;
    uint64_t result = mckits_hash_sip((const uint8_t*)buf, size, 0, 0);
    assert(expected == result);
  }
}

int main() {
  test01();
  return 0;
}
