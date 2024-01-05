#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "mckits_hash_fnv.h"

void test01() {
  {
    const char* data = "hello";
    size_t size = strlen(data);
    uint32_t expected = 3069866343;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }
}

void test02() {
  {
    const char* data = "7Uw";
    size_t size = strlen(data);
    uint32_t expected = 1439092512;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "Fb6";
    size_t size = strlen(data);
    uint32_t expected = 1161905997;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "JWM";
    size_t size = strlen(data);
    uint32_t expected = 406221573;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "slJ";
    size_t size = strlen(data);
    uint32_t expected = 493905650;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "iWI";
    size_t size = strlen(data);
    uint32_t expected = 143149766;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "xvGq";
    size_t size = strlen(data);
    uint32_t expected = 367709659;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "8hPI";
    size_t size = strlen(data);
    uint32_t expected = 3790667052;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "Atik";
    size_t size = strlen(data);
    uint32_t expected = 374406194;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "xVOK";
    size_t size = strlen(data);
    uint32_t expected = 3459911289;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "Yvyf";
    size_t size = strlen(data);
    uint32_t expected = 4125656649;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "wNszd";
    size_t size = strlen(data);
    uint32_t expected = 3664014463;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "YPBoR";
    size_t size = strlen(data);
    uint32_t expected = 510409291;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "2aplG";
    size_t size = strlen(data);
    uint32_t expected = 2647925545;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "W0rNP";
    size_t size = strlen(data);
    uint32_t expected = 901660480;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "H9aiO";
    size_t size = strlen(data);
    uint32_t expected = 3323868429;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "M3F0yt";
    size_t size = strlen(data);
    uint32_t expected = 3157309900;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "mnZQ1w";
    size_t size = strlen(data);
    uint32_t expected = 654791979;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "wiIzC9";
    size_t size = strlen(data);
    uint32_t expected = 2437556900;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "6IDy74";
    size_t size = strlen(data);
    uint32_t expected = 2858811290;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "nQ45B7";
    size_t size = strlen(data);
    uint32_t expected = 4052258566;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "dq9fCmH";
    size_t size = strlen(data);
    uint32_t expected = 2158757995;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "dAbk208";
    size_t size = strlen(data);
    uint32_t expected = 3278536261;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "9twNyA5";
    size_t size = strlen(data);
    uint32_t expected = 592875976;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "9rIUqiL";
    size_t size = strlen(data);
    uint32_t expected = 4144994788;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "0hnZRcH";
    size_t size = strlen(data);
    uint32_t expected = 3136207456;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "BCh5Dl8C";
    size_t size = strlen(data);
    uint32_t expected = 3116368370;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "ofokaX4U";
    size_t size = strlen(data);
    uint32_t expected = 1253740998;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "Bh3wLL2U";
    size_t size = strlen(data);
    uint32_t expected = 1234472762;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "i47TvLsZ";
    size_t size = strlen(data);
    uint32_t expected = 4024804226;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "qRtu88KJ";
    size_t size = strlen(data);
    uint32_t expected = 960453450;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "ovtOJsufx";
    size_t size = strlen(data);
    uint32_t expected = 637152639;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "TbLTCLP9Y";
    size_t size = strlen(data);
    uint32_t expected = 562026880;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "Ap8yddzVR";
    size_t size = strlen(data);
    uint32_t expected = 2031376887;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "5sjUSQhSQ";
    size_t size = strlen(data);
    uint32_t expected = 1994806238;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "RbE1UDv0m";
    size_t size = strlen(data);
    uint32_t expected = 883009071;
    uint32_t result = mckits_fnv_1_32((const uint8_t*)data, size);
    assert(result == expected);
  }
}

void test03() {
  {
    const char* data = "0Mj";
    size_t size = strlen(data);
    uint32_t expected = 2389757892;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "Kx0";
    size_t size = strlen(data);
    uint32_t expected = 136438194;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "zMQ";
    size_t size = strlen(data);
    uint32_t expected = 3032983139;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "EPD";
    size_t size = strlen(data);
    uint32_t expected = 4215834332;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "bvq";
    size_t size = strlen(data);
    uint32_t expected = 1843150792;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "GtfM";
    size_t size = strlen(data);
    uint32_t expected = 1233583399;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "FNrg";
    size_t size = strlen(data);
    uint32_t expected = 2761589798;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "WvYj";
    size_t size = strlen(data);
    uint32_t expected = 1505431427;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "hHTD";
    size_t size = strlen(data);
    uint32_t expected = 276272973;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "Sb2b";
    size_t size = strlen(data);
    uint32_t expected = 4244287996;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "7QAym";
    size_t size = strlen(data);
    uint32_t expected = 2963457286;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "zjmB3";
    size_t size = strlen(data);
    uint32_t expected = 1760026183;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "14NIg";
    size_t size = strlen(data);
    uint32_t expected = 3507830594;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "yz0T0";
    size_t size = strlen(data);
    uint32_t expected = 2806960378;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "2QEOt";
    size_t size = strlen(data);
    uint32_t expected = 753446984;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "XisvKr";
    size_t size = strlen(data);
    uint32_t expected = 1064844594;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "jHjzgE";
    size_t size = strlen(data);
    uint32_t expected = 2041556535;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "0CZ9U4";
    size_t size = strlen(data);
    uint32_t expected = 246495824;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "Qhhslw";
    size_t size = strlen(data);
    uint32_t expected = 1319739900;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "Azbr16";
    size_t size = strlen(data);
    uint32_t expected = 2293995561;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "h61Bmpj";
    size_t size = strlen(data);
    uint32_t expected = 2391872201;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "341KU2y";
    size_t size = strlen(data);
    uint32_t expected = 123532552;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "PLMuxHm";
    size_t size = strlen(data);
    uint32_t expected = 2096889882;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "6xkdriE";
    size_t size = strlen(data);
    uint32_t expected = 2849891532;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "TqkG5ir";
    size_t size = strlen(data);
    uint32_t expected = 1845818592;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "REhQz01v";
    size_t size = strlen(data);
    uint32_t expected = 543615114;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "e4XWguhm";
    size_t size = strlen(data);
    uint32_t expected = 2584957838;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "YJdSfeeU";
    size_t size = strlen(data);
    uint32_t expected = 914896820;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "NXYWUSXY";
    size_t size = strlen(data);
    uint32_t expected = 3311016536;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "xbdDN1E1";
    size_t size = strlen(data);
    uint32_t expected = 2376040488;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "aBUhTVEFd";
    size_t size = strlen(data);
    uint32_t expected = 2583136802;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "uqSlrPytO";
    size_t size = strlen(data);
    uint32_t expected = 2498489868;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "7kF0SNVIO";
    size_t size = strlen(data);
    uint32_t expected = 3086342922;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "s7CUZdEZj";
    size_t size = strlen(data);
    uint32_t expected = 3185245636;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "qc4RXKy3m";
    size_t size = strlen(data);
    uint32_t expected = 2134372501;
    uint32_t result = mckits_fnv_1a_32((const uint8_t*)data, size);
    assert(result == expected);
  }
}

void test04() {
  {
    const char* data = "y0j";
    size_t size = strlen(data);
    uint64_t expected = 15603684186092385964ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "yts";
    size_t size = strlen(data);
    uint64_t expected = 15603758952883104289ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "MXf";
    size_t size = strlen(data);
    uint64_t expected = 15584596664230427628ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "X0c";
    size_t size = strlen(data);
    uint64_t expected = 15573995173113298444ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "sRt";
    size_t size = strlen(data);
    uint64_t expected = 15609355467069562902ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "ybA3";
    size_t size = strlen(data);
    uint64_t expected = 6964896531999972816ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "P8EO";
    size_t size = strlen(data);
    uint64_t expected = 10912487420933779841ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "ttwz";
    size_t size = strlen(data);
    uint64_t expected = 10076306631318134466ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "GAlP";
    size_t size = strlen(data);
    uint64_t expected = 16523174311935102485ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "iHyK";
    size_t size = strlen(data);
    uint64_t expected = 16807992905976500014ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "vnAv1";
    size_t size = strlen(data);
    uint64_t expected = 569969336418857653ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "LLgAm";
    size_t size = strlen(data);
    uint64_t expected = 1724395276941031462ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "NzGp3";
    size_t size = strlen(data);
    uint64_t expected = 11855670276635636351ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "Jqqbc";
    size_t size = strlen(data);
    uint64_t expected = 4439865822230060714ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "qtTyU";
    size_t size = strlen(data);
    uint64_t expected = 639158485788400796ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "jrSPWP";
    size_t size = strlen(data);
    uint64_t expected = 14273615403506595705ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "VQj75c";
    size_t size = strlen(data);
    uint64_t expected = 13067825558700591743ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "heLofI";
    size_t size = strlen(data);
    uint64_t expected = 5872925971296936812ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "e5MZSk";
    size_t size = strlen(data);
    uint64_t expected = 6203278904881265440ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "CDiDjS";
    size_t size = strlen(data);
    uint64_t expected = 1331798637137140438ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "iuoxfDK";
    size_t size = strlen(data);
    uint64_t expected = 1496642185388191123ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "YP0T70u";
    size_t size = strlen(data);
    uint64_t expected = 12231701712941573272ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "wKrFFAq";
    size_t size = strlen(data);
    uint64_t expected = 5059802230116267065ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "sIEj8N9";
    size_t size = strlen(data);
    uint64_t expected = 14486342471185638055ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "3J7fpNA";
    size_t size = strlen(data);
    uint64_t expected = 1469928972044513684ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "RkVZPgb5";
    size_t size = strlen(data);
    uint64_t expected = 14694777646417978204ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "FYj8ghR8";
    size_t size = strlen(data);
    uint64_t expected = 14318224343118019339ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "PqgXTjh0";
    size_t size = strlen(data);
    uint64_t expected = 4533577468679723327ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "ocePFcrq";
    size_t size = strlen(data);
    uint64_t expected = 16643812727509397294ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "gXLsl7ej";
    size_t size = strlen(data);
    uint64_t expected = 5783718714567512361ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "riedzC8fF";
    size_t size = strlen(data);
    uint64_t expected = 578917328444421644ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "s2Kn0btxs";
    size_t size = strlen(data);
    uint64_t expected = 16472559975879750986ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "blsymEUgk";
    size_t size = strlen(data);
    uint64_t expected = 4468529851607164336ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "KmnGDEK38";
    size_t size = strlen(data);
    uint64_t expected = 5576346016300016577ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "vdjftzC1S";
    size_t size = strlen(data);
    uint64_t expected = 5830413296690942228ULL;
    uint64_t result = mckits_fnv_1_64((const uint8_t*)data, size);
    assert(result == expected);
  }
}

void test05() {
  {
    const char* data = "pgy";
    size_t size = strlen(data);
    uint64_t expected = 8626188897726367315ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "yS3";
    size_t size = strlen(data);
    uint64_t expected = 13020119937388673442ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "wmq";
    size_t size = strlen(data);
    uint64_t expected = 6826293860382597520ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "fP7";
    size_t size = strlen(data);
    uint64_t expected = 15859933069992025652ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "orS";
    size_t size = strlen(data);
    uint64_t expected = 1872301284275517365ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "UnoD";
    size_t size = strlen(data);
    uint64_t expected = 10317101266522733425ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "jbaG";
    size_t size = strlen(data);
    uint64_t expected = 12789693932360848761ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "izsF";
    size_t size = strlen(data);
    uint64_t expected = 11740538732203819095ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "HOPm";
    size_t size = strlen(data);
    uint64_t expected = 9082371598174412735ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "Q7Nd";
    size_t size = strlen(data);
    uint64_t expected = 3348270271803669835ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "pnKj7";
    size_t size = strlen(data);
    uint64_t expected = 15862920597368066979ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "OgMIi";
    size_t size = strlen(data);
    uint64_t expected = 3315220267339868968ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "jGlEi";
    size_t size = strlen(data);
    uint64_t expected = 11107024353909319376ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "s7tct";
    size_t size = strlen(data);
    uint64_t expected = 12685660002676116310ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "UhRda";
    size_t size = strlen(data);
    uint64_t expected = 7081817528263889677ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "T6aYV9";
    size_t size = strlen(data);
    uint64_t expected = 5869298056187930268ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "P4MDEP";
    size_t size = strlen(data);
    uint64_t expected = 15854712088308426301ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "CjUsFu";
    size_t size = strlen(data);
    uint64_t expected = 16049063646609943297ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "JRGaQQ";
    size_t size = strlen(data);
    uint64_t expected = 2785465354494635279ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "IXjZyt";
    size_t size = strlen(data);
    uint64_t expected = 10967497628440866205ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "zpFulcd";
    size_t size = strlen(data);
    uint64_t expected = 14708211572464215853ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "tKqLTzk";
    size_t size = strlen(data);
    uint64_t expected = 13871258775113775184ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "QxY7b3o";
    size_t size = strlen(data);
    uint64_t expected = 8194959557201727720ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "MSx1cbb";
    size_t size = strlen(data);
    uint64_t expected = 9165160853964471607ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "KTHXqt6";
    size_t size = strlen(data);
    uint64_t expected = 1456499581041929371ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "Pqw4sAiu";
    size_t size = strlen(data);
    uint64_t expected = 7082457660846294683ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "nqWpMZt9";
    size_t size = strlen(data);
    uint64_t expected = 8420048303649610763ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "tJFMr6aK";
    size_t size = strlen(data);
    uint64_t expected = 9921540690492318506ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "oOgqe69K";
    size_t size = strlen(data);
    uint64_t expected = 7665463063043141600ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "oFCeqHCB";
    size_t size = strlen(data);
    uint64_t expected = 4370565075641143704ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "TlBmogyA2";
    size_t size = strlen(data);
    uint64_t expected = 9541754594675172586ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "xzFesCaxo";
    size_t size = strlen(data);
    uint64_t expected = 6462236817314371546ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "0NLoJvIF5";
    size_t size = strlen(data);
    uint64_t expected = 7848313374543876172ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "Hb45uZYjH";
    size_t size = strlen(data);
    uint64_t expected = 855504967095750060ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }

  {
    const char* data = "6KNs6y1iY";
    size_t size = strlen(data);
    uint64_t expected = 1910673701417116129ULL;
    uint64_t result = mckits_fnv_1a_64((const uint8_t*)data, size);
    assert(result == expected);
  }
}

int main() {
  test01();
  test02();
  test03();
  test04();
  test05();
  return 0;
}
