#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "mckits/mstl/encoding/mckits_encoding_hex.h"

void test01() {
  {
    const char* src = "Pe9";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "506539";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "n9w";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "6e3977";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "IqM";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "49714d";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "XVM";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "58564d";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "RY2";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "525932";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "WTN1";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "57544e31";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "fzes";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "667a6573";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "1Fzn";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "31467a6e";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "0ze4";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "307a6534";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "GDnx";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "47446e78";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "RIyH7";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "5249794837";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "Yh8lM";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "5968386c4d";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "H0eWI";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "4830655749";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "uuZqZ";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "75755a715a";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "aOc8o";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "614f63386f";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "g0l8kx";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "67306c386b78";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "lmVXEp";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "6c6d56584570";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "9hUZxC";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "3968555a7843";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "S1lLGj";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "53316c4c476a";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "hUdEqA";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "685564457141";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "i8gNW5l";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "6938674e57356c";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "FI2gNdh";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "464932674e6468";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "G7ZralE";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "47375a72616c45";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "dd7vGe4";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "64643776476534";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "5pdD5e6";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "35706444356536";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "hHvaIzps";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "68487661497a7073";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "d49nEPn8";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "6434396e45506e38";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "Kp1IwTMP";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "4b70314977544d50";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "UZPxPkGP";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "555a5078506b4750";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "renjEPMY";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "72656e6a45504d59";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "mxgN8nPyt";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "6d78674e386e507974";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "dUx9XGgpq";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "645578395847677071";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "7eWgibQnj";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "376557676962516e6a";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "UsEt9vEqQ";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "557345743976457151";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }

  {
    const char* src = "aUqgfiJee";
    size_t src_size = strlen(src);
    char dst[1024] = {0};
    const char* expected = "6155716766694a6565";
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(strcmp(dst, expected) == 0);
  }
}

void test02() {
  {
    const char* src = "Nan";
    size_t src_size = strlen(src);
    char dst[6] = {0};
    char src02[3] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "cqq";
    size_t src_size = strlen(src);
    char dst[6] = {0};
    char src02[3] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "HJt";
    size_t src_size = strlen(src);
    char dst[6] = {0};
    char src02[3] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "Y13";
    size_t src_size = strlen(src);
    char dst[6] = {0};
    char src02[3] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "kGX";
    size_t src_size = strlen(src);
    char dst[6] = {0};
    char src02[3] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "95HQ";
    size_t src_size = strlen(src);
    char dst[8] = {0};
    char src02[4] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "chM4";
    size_t src_size = strlen(src);
    char dst[8] = {0};
    char src02[4] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "i7Lp";
    size_t src_size = strlen(src);
    char dst[8] = {0};
    char src02[4] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "RaW3";
    size_t src_size = strlen(src);
    char dst[8] = {0};
    char src02[4] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "L2PN";
    size_t src_size = strlen(src);
    char dst[8] = {0};
    char src02[4] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "UUqKu";
    size_t src_size = strlen(src);
    char dst[10] = {0};
    char src02[5] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "vFrZU";
    size_t src_size = strlen(src);
    char dst[10] = {0};
    char src02[5] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "mSKdo";
    size_t src_size = strlen(src);
    char dst[10] = {0};
    char src02[5] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "ElUvl";
    size_t src_size = strlen(src);
    char dst[10] = {0};
    char src02[5] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "UJDri";
    size_t src_size = strlen(src);
    char dst[10] = {0};
    char src02[5] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "oRydOm";
    size_t src_size = strlen(src);
    char dst[12] = {0};
    char src02[6] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "RpHwXO";
    size_t src_size = strlen(src);
    char dst[12] = {0};
    char src02[6] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "M1lDiU";
    size_t src_size = strlen(src);
    char dst[12] = {0};
    char src02[6] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "9xKQ3G";
    size_t src_size = strlen(src);
    char dst[12] = {0};
    char src02[6] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "e2qZbh";
    size_t src_size = strlen(src);
    char dst[12] = {0};
    char src02[6] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "yJ3OA9N";
    size_t src_size = strlen(src);
    char dst[14] = {0};
    char src02[7] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "3BO7j66";
    size_t src_size = strlen(src);
    char dst[14] = {0};
    char src02[7] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "3dRkGtt";
    size_t src_size = strlen(src);
    char dst[14] = {0};
    char src02[7] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "AgcRW1p";
    size_t src_size = strlen(src);
    char dst[14] = {0};
    char src02[7] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "w77g3Wc";
    size_t src_size = strlen(src);
    char dst[14] = {0};
    char src02[7] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "68HTrIfu";
    size_t src_size = strlen(src);
    char dst[16] = {0};
    char src02[8] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "BN1e6bM6";
    size_t src_size = strlen(src);
    char dst[16] = {0};
    char src02[8] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "FCmekT7s";
    size_t src_size = strlen(src);
    char dst[16] = {0};
    char src02[8] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "u6TjGemS";
    size_t src_size = strlen(src);
    char dst[16] = {0};
    char src02[8] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "Hxz3EzSl";
    size_t src_size = strlen(src);
    char dst[16] = {0};
    char src02[8] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "EggX2UrGf";
    size_t src_size = strlen(src);
    char dst[18] = {0};
    char src02[9] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "DvZC96yuc";
    size_t src_size = strlen(src);
    char dst[18] = {0};
    char src02[9] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "rPuDIUWbn";
    size_t src_size = strlen(src);
    char dst[18] = {0};
    char src02[9] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "5NnW8Wvdm";
    size_t src_size = strlen(src);
    char dst[18] = {0};
    char src02[9] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }

  {
    const char* src = "fq5eY6PTy";
    size_t src_size = strlen(src);
    char dst[18] = {0};
    char src02[9] = {0};
    mckits_hex_encode((uint8_t*)dst, (const uint8_t*)src, src_size);
    assert(0 == mckits_hex_decode((uint8_t*)src02, (const uint8_t*)dst,
                                  src_size * 2));
    for (int i = 0; i < src_size; ++i) {
      assert(src[i] == src02[i]);
    }
  }
}

int main() {
  test01();
  test02();
  return 0;
}
