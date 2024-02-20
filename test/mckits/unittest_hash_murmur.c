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

void test03() {
  {
    const char* buf = "PK";
    size_t size = strlen(buf);
    uint64_t expected = 2345346153638906767U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "ht";
    size_t size = strlen(buf);
    uint64_t expected = 16112909033462085004U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "Mm";
    size_t size = strlen(buf);
    uint64_t expected = 2574044070079658673U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "18n";
    size_t size = strlen(buf);
    uint64_t expected = 16416814790386535713U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "L9K";
    size_t size = strlen(buf);
    uint64_t expected = 5192417922169328651U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "8eM";
    size_t size = strlen(buf);
    uint64_t expected = 2078027833624984822U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "Gn7C";
    size_t size = strlen(buf);
    uint64_t expected = 11171730994133304974U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "ctT9";
    size_t size = strlen(buf);
    uint64_t expected = 14893122486580386398U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "wKSB";
    size_t size = strlen(buf);
    uint64_t expected = 3892649871985085802U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "FebW3";
    size_t size = strlen(buf);
    uint64_t expected = 1488277408052929218U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "7VI5u";
    size_t size = strlen(buf);
    uint64_t expected = 4692842216379828625U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "1yhc3";
    size_t size = strlen(buf);
    uint64_t expected = 16243285086645330395U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "avuaOb";
    size_t size = strlen(buf);
    uint64_t expected = 15140447688343270682U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "vyJcXy";
    size_t size = strlen(buf);
    uint64_t expected = 10933358006561857983U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "ZzsRwp";
    size_t size = strlen(buf);
    uint64_t expected = 6596796569276157574U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "5iUzahE";
    size_t size = strlen(buf);
    uint64_t expected = 11747938283453917192U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "aYatja7";
    size_t size = strlen(buf);
    uint64_t expected = 10937366432533091206U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "aqGHss6";
    size_t size = strlen(buf);
    uint64_t expected = 15333397223865714992U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "hteYQrpJ";
    size_t size = strlen(buf);
    uint64_t expected = 12035905656404735791U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "76AcBAan";
    size_t size = strlen(buf);
    uint64_t expected = 6402416686302079953U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "tuBoDzF9";
    size_t size = strlen(buf);
    uint64_t expected = 3352066961858476874U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "Vp1HviLhW";
    size_t size = strlen(buf);
    uint64_t expected = 15248284472242233943U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "uvrsqRsRf";
    size_t size = strlen(buf);
    uint64_t expected = 14772929122634775727U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "4GMp61Qtu";
    size_t size = strlen(buf);
    uint64_t expected = 9511791033936837679U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "od3fLomkv8";
    size_t size = strlen(buf);
    uint64_t expected = 10965355414274105014U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "Ous6I7opdF";
    size_t size = strlen(buf);
    uint64_t expected = 7711227772586154677U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "JiuD7aXpOb";
    size_t size = strlen(buf);
    uint64_t expected = 3921100448698614907U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "Hf3TrccpfQH";
    size_t size = strlen(buf);
    uint64_t expected = 4249339762771887401U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "KfvXswsA4yS";
    size_t size = strlen(buf);
    uint64_t expected = 7032274386614214939U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "tTiIvi10nSJ";
    size_t size = strlen(buf);
    uint64_t expected = 4908164387491191097U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "UJPYonkWqDHH";
    size_t size = strlen(buf);
    uint64_t expected = 494611197798639591U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "05UmNfGuocPw";
    size_t size = strlen(buf);
    uint64_t expected = 9261653920315653295U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "FHKc9uKOgYZq";
    size_t size = strlen(buf);
    uint64_t expected = 5312718604635368150U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "eSgLI4EqghvKC";
    size_t size = strlen(buf);
    uint64_t expected = 1946758393455512343U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "Nf3ELyeLxzlaD";
    size_t size = strlen(buf);
    uint64_t expected = 10297029665873565655U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "XUG1CKA8E4oKa";
    size_t size = strlen(buf);
    uint64_t expected = 13697342112219367408U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "jAfWF6qetvQOSZ";
    size_t size = strlen(buf);
    uint64_t expected = 17710006133485759356U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "lVA3pptZQrtID1";
    size_t size = strlen(buf);
    uint64_t expected = 13043265479221888673U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "9a6cUA6bEpui4c";
    size_t size = strlen(buf);
    uint64_t expected = 2862792721904086077U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "GlT6d8mwV0Mewd3";
    size_t size = strlen(buf);
    uint64_t expected = 1463587075445208730U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "c4XeMn9NSo50i5W";
    size_t size = strlen(buf);
    uint64_t expected = 11331141571340232809U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "hDJkzTEkJgm4igX";
    size_t size = strlen(buf);
    uint64_t expected = 18087756804895020705U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "8InKWmmCAhqHddki";
    size_t size = strlen(buf);
    uint64_t expected = 9311434322774877904U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "Rq6BUeaZr47xPfto";
    size_t size = strlen(buf);
    uint64_t expected = 4247469328796314101U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "38CdA1lQymRGumnK";
    size_t size = strlen(buf);
    uint64_t expected = 7069567752894027902U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "OskNhBFeWlkfxA7t3";
    size_t size = strlen(buf);
    uint64_t expected = 15854614242364869821U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "TUjxgvfMNpXnvCGFd";
    size_t size = strlen(buf);
    uint64_t expected = 16085154412417757640U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "5IQRRYVeoQxfOeZYC";
    size_t size = strlen(buf);
    uint64_t expected = 5644093509852089744U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "hFFVUt6fTCIWeDuSjc";
    size_t size = strlen(buf);
    uint64_t expected = 4220309491132275385U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "2eSIAYmCL82Fgx8Zfp";
    size_t size = strlen(buf);
    uint64_t expected = 537853431216085355U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf = "i6mPSoib4pbyhdgNB2";
    size_t size = strlen(buf);
    uint64_t expected = 13829317459469663750U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf =
        "4CWW70i3PlhzudJ9WXfVRvWfAXjcpc0jEK3zBbqenxBFBaClVH6A0QDpBNrQNfXfPPCeQS"
        "j1gIuFJWQssKTiomvPXMuARfDvU5z";
    size_t size = strlen(buf);
    uint64_t expected = 17704991803909562127U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf =
        "MIoQfJlOtZ4LxNSJ0dmLOGctMDOuzeTbK8PPH0r0NmAaXiHLjTnXophYSTifV2ew0T9vHp"
        "jkzJimPPYZzbKNoPB4zHakzcEnWCG";
    size_t size = strlen(buf);
    uint64_t expected = 7021836894439518283U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }

  {
    const char* buf =
        "RQCgnKs1oeOLfoot4NmrkmzIm4V6wsob6Qfhox8ACMbFZpXT09abjzJvrssLIGKCkPKwdG"
        "XDhY86cTN2SL118ynoRDZp9AShdqD";
    size_t size = strlen(buf);
    uint64_t expected = 3933551818082817239U;
    uint64_t result = mckits_murmur3_64_86_128((const uint8_t*)buf, size, 0);
    assert(expected == result);
  }
}

int main() {
  test01();
  test02();
  test03();
  return 0;
}
