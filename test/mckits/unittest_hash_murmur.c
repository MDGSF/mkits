#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "mckits/mstl/hash/mckits_hash_murmur.h"

void test01() {
  {
    const char* buf = "PK";
    size_t size = strlen(buf);
    uint32_t expected = 2957225072U;
    uint32_t result = mckits_murmur2_32((const uint8_t*)buf, size);
    assert(expected == result);
  }

  {
    const char* buf = "ht";
    size_t size = strlen(buf);
    uint32_t expected = 322292916U;
    uint32_t result = mckits_murmur2_32((const uint8_t*)buf, size);
    assert(expected == result);
  }

  {
    const char* buf = "Mm";
    size_t size = strlen(buf);
    uint32_t expected = 545429686U;
    uint32_t result = mckits_murmur2_32((const uint8_t*)buf, size);
    assert(expected == result);
  }

  {
    const char* buf = "18n";
    size_t size = strlen(buf);
    uint32_t expected = 3004844273U;
    uint32_t result = mckits_murmur2_32((const uint8_t*)buf, size);
    assert(expected == result);
  }

  {
    const char* buf = "L9K";
    size_t size = strlen(buf);
    uint32_t expected = 4225517U;
    uint32_t result = mckits_murmur2_32((const uint8_t*)buf, size);
    assert(expected == result);
  }

  {
    const char* buf = "8eM";
    size_t size = strlen(buf);
    uint32_t expected = 2088002014U;
    uint32_t result = mckits_murmur2_32((const uint8_t*)buf, size);
    assert(expected == result);
  }

  {
    const char* buf = "Gn7C";
    size_t size = strlen(buf);
    uint32_t expected = 3725949234U;
    uint32_t result = mckits_murmur2_32((const uint8_t*)buf, size);
    assert(expected == result);
  }

  {
    const char* buf = "ctT9";
    size_t size = strlen(buf);
    uint32_t expected = 691843089U;
    uint32_t result = mckits_murmur2_32((const uint8_t*)buf, size);
    assert(expected == result);
  }

  {
    const char* buf = "wKSB";
    size_t size = strlen(buf);
    uint32_t expected = 3714920207U;
    uint32_t result = mckits_murmur2_32((const uint8_t*)buf, size);
    assert(expected == result);
  }

  {
    const char* buf = "FebW3";
    size_t size = strlen(buf);
    uint32_t expected = 2514511449U;
    uint32_t result = mckits_murmur2_32((const uint8_t*)buf, size);
    assert(expected == result);
  }

  {
    const char* buf = "7VI5u";
    size_t size = strlen(buf);
    uint32_t expected = 1947409437U;
    uint32_t result = mckits_murmur2_32((const uint8_t*)buf, size);
    assert(expected == result);
  }

  {
    const char* buf = "1yhc3";
    size_t size = strlen(buf);
    uint32_t expected = 2560029720U;
    uint32_t result = mckits_murmur2_32((const uint8_t*)buf, size);
    assert(expected == result);
  }

  {
    const char* buf = "avuaOb";
    size_t size = strlen(buf);
    uint32_t expected = 4033247514U;
    uint32_t result = mckits_murmur2_32((const uint8_t*)buf, size);
    assert(expected == result);
  }

  {
    const char* buf = "vyJcXy";
    size_t size = strlen(buf);
    uint32_t expected = 2082889609U;
    uint32_t result = mckits_murmur2_32((const uint8_t*)buf, size);
    assert(expected == result);
  }

  {
    const char* buf = "ZzsRwp";
    size_t size = strlen(buf);
    uint32_t expected = 1676931907U;
    uint32_t result = mckits_murmur2_32((const uint8_t*)buf, size);
    assert(expected == result);
  }

  {
    const char* buf = "5iUzahE";
    size_t size = strlen(buf);
    uint32_t expected = 2291821551U;
    uint32_t result = mckits_murmur2_32((const uint8_t*)buf, size);
    assert(expected == result);
  }

  {
    const char* buf = "aYatja7";
    size_t size = strlen(buf);
    uint32_t expected = 1804238223U;
    uint32_t result = mckits_murmur2_32((const uint8_t*)buf, size);
    assert(expected == result);
  }

  {
    const char* buf = "aqGHss6";
    size_t size = strlen(buf);
    uint32_t expected = 132156875U;
    uint32_t result = mckits_murmur2_32((const uint8_t*)buf, size);
    assert(expected == result);
  }

  {
    const char* buf = "hteYQrpJ";
    size_t size = strlen(buf);
    uint32_t expected = 1759435U;
    uint32_t result = mckits_murmur2_32((const uint8_t*)buf, size);
    assert(expected == result);
  }

  {
    const char* buf = "76AcBAan";
    size_t size = strlen(buf);
    uint32_t expected = 4233393582U;
    uint32_t result = mckits_murmur2_32((const uint8_t*)buf, size);
    assert(expected == result);
  }

  {
    const char* buf = "tuBoDzF9";
    size_t size = strlen(buf);
    uint32_t expected = 1631826472U;
    uint32_t result = mckits_murmur2_32((const uint8_t*)buf, size);
    assert(expected == result);
  }
}

void test02() {
  {
    const char* buf = "PK";
    size_t size = strlen(buf);
    uint32_t expected = 2928569346U;
    uint32_t result = mckits_murmur3_32((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "ht";
    size_t size = strlen(buf);
    uint32_t expected = 3083713904U;
    uint32_t result = mckits_murmur3_32((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "Mm";
    size_t size = strlen(buf);
    uint32_t expected = 1477349128U;
    uint32_t result = mckits_murmur3_32((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "18n";
    size_t size = strlen(buf);
    uint32_t expected = 3937804112U;
    uint32_t result = mckits_murmur3_32((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "L9K";
    size_t size = strlen(buf);
    uint32_t expected = 1818089488U;
    uint32_t result = mckits_murmur3_32((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "8eM";
    size_t size = strlen(buf);
    uint32_t expected = 3067106720U;
    uint32_t result = mckits_murmur3_32((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "Gn7C";
    size_t size = strlen(buf);
    uint32_t expected = 1188714510U;
    uint32_t result = mckits_murmur3_32((const uint8_t*)buf, size, 0);
    printf("result = %u, expected = %u\n", result, expected);
    assert(expected == result);
  }

  {
    const char* buf = "ctT9";
    size_t size = strlen(buf);
    uint32_t expected = 178597094U;
    uint32_t result = mckits_murmur3_32((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "wKSB";
    size_t size = strlen(buf);
    uint32_t expected = 1448343991U;
    uint32_t result = mckits_murmur3_32((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "FebW3";
    size_t size = strlen(buf);
    uint32_t expected = 2435914944U;
    uint32_t result = mckits_murmur3_32((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "7VI5u";
    size_t size = strlen(buf);
    uint32_t expected = 1022072143U;
    uint32_t result = mckits_murmur3_32((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "1yhc3";
    size_t size = strlen(buf);
    uint32_t expected = 2877822760U;
    uint32_t result = mckits_murmur3_32((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "avuaOb";
    size_t size = strlen(buf);
    uint32_t expected = 3656140270U;
    uint32_t result = mckits_murmur3_32((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "vyJcXy";
    size_t size = strlen(buf);
    uint32_t expected = 2808191557U;
    uint32_t result = mckits_murmur3_32((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "ZzsRwp";
    size_t size = strlen(buf);
    uint32_t expected = 884897662U;
    uint32_t result = mckits_murmur3_32((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "5iUzahE";
    size_t size = strlen(buf);
    uint32_t expected = 3737352207U;
    uint32_t result = mckits_murmur3_32((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "aYatja7";
    size_t size = strlen(buf);
    uint32_t expected = 4266019058U;
    uint32_t result = mckits_murmur3_32((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "aqGHss6";
    size_t size = strlen(buf);
    uint32_t expected = 1214462530U;
    uint32_t result = mckits_murmur3_32((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "hteYQrpJ";
    size_t size = strlen(buf);
    uint32_t expected = 4267752310U;
    uint32_t result = mckits_murmur3_32((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "76AcBAan";
    size_t size = strlen(buf);
    uint32_t expected = 1251258832U;
    uint32_t result = mckits_murmur3_32((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "tuBoDzF9";
    size_t size = strlen(buf);
    uint32_t expected = 3608746661U;
    uint32_t result = mckits_murmur3_32((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }
}

int main() {
  test01();
  test02();
  return 0;
}
