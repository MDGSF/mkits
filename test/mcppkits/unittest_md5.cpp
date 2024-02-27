#include <cassert>
#include <cstring>
#include <iostream>
#include <set>

#include "mcppkits/mcppkits_md5.h"

void test01() {
  {
    const char* buf = "PK";
    size_t size = strlen(buf);
    std::string expected = "d71bdd22c8bb93b8d287dce6f46aed25";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf = "ht";
    size_t size = strlen(buf);
    std::string expected = "eb5e48e74123cacc52761302ea4a7d22";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf = "Mmr18n2";
    size_t size = strlen(buf);
    std::string expected = "762a0c82b9debd7b6d87a2157d7736ef";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf = "9K88eMl";
    size_t size = strlen(buf);
    std::string expected = "e4b51d8b3faab410edce954c6bb0c6f1";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf = "n7CcctT9RwKS";
    size_t size = strlen(buf);
    std::string expected = "fafce475bab93777472744d551987708";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf = "1FebW397VI5u";
    size_t size = strlen(buf);
    std::string expected = "c3c480f51f5b3cc1136f5059be797568";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf = "1yhc3uavuaOb9vyJc";
    size_t size = strlen(buf);
    std::string expected = "aa67afceaa71fd47d308cd3994207a02";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf = "yHZzsRwpC5iUzahEc";
    size_t size = strlen(buf);
    std::string expected = "f536620aab9871b370dc02cead29687d";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf = "Yatja7kaqGHss6YhteYQrp";
    size_t size = strlen(buf);
    std::string expected = "8bfa8ef0c4911ab769694f0ced8ed0b4";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf = "A76AcBAanBtuBoDzF97Vp1";
    size_t size = strlen(buf);
    std::string expected = "59414fc7643de39ca2be93634c4f2f19";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf = "viLhW3uvrsqRsRft4GMp61QtuNo";
    size_t size = strlen(buf);
    std::string expected = "39e6fd9c0e370e69f88f261466faf346";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf = "3fLomkv8dOus6I7opdFhJiuD7aX";
    size_t size = strlen(buf);
    std::string expected = "c6296179d6973df5ae6146252204ebe7";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf = "ObsHf3TrccpfQHyKfvXswsA4ySxtTiIv";
    size_t size = strlen(buf);
    std::string expected = "6fdc354a38f7b23accfef81667878608";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf = "10nSJCUJPYonkWqDHH005UmNfGuocPw3";
    size_t size = strlen(buf);
    std::string expected = "d318cdec23d0fcb6919fdb6fefda4cdf";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf = "HKc9uKOgYZqIeSgLI4EqghvKCHNf3ELyeLxzl";
    size_t size = strlen(buf);
    std::string expected = "53537a2de3e6a3400cba55227c7e3488";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf = "D7XUG1CKA8E4oKaHjAfWF6qetvQOSZOlVA3pp";
    size_t size = strlen(buf);
    std::string expected = "76e61983459ebd9fa942543f3134c1fa";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf = "ZQrtID1G9a6cUA6bEpui4c8GlT6d8mwV0Mewd33c4X";
    size_t size = strlen(buf);
    std::string expected = "f978c7b6d40d732e1488d2f248d93a68";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf = "Mn9NSo50i5WPhDJkzTEkJgm4igXk8InKWmmCAhqHdd";
    size_t size = strlen(buf);
    std::string expected = "14555b4305810cbbf59d04fe0605c557";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf = "iGRq6BUeaZr47xPftos38CdA1lQymRGumnKgOskNhBFeWlk";
    size_t size = strlen(buf);
    std::string expected = "53fae224dabb6ad42dc0974666379d7b";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf = "xA7t3aTUjxgvfMNpXnvCGFdL5IQRRYVeoQxfOeZYC3hFFVU";
    size_t size = strlen(buf);
    std::string expected = "3ae0dea8bfcc83415e944496442e483e";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf = "6fTCIWeDuSjcG2eSIAYmCL82Fgx8ZfpVi6mPSoib4pbyhdgNB2Y4";
    size_t size = strlen(buf);
    std::string expected = "30c21bb67fe46d577757384101063e1e";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf = "WW70i3PlhzudJ9WXfVRvWfAXjcpc0jEK3zBbqenxBFBaClVH6A0Q";
    size_t size = strlen(buf);
    std::string expected = "059bacb359adec284d1997084ce49366";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "pBNrQNfXfPPCeQSj1gIuFJWQssKTiomvPXMuARfDvU5zzMIoQfJlOtZ4L";
    size_t size = strlen(buf);
    std::string expected = "78fcd50dc5c53958e2cc621f7b3ee0b3";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "NSJ0dmLOGctMDOuzeTbK8PPH0r0NmAaXiHLjTnXophYSTifV2ew0T9vHp";
    size_t size = strlen(buf);
    std::string expected = "1fe514003719b3269a5d83a67fce0f05";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "kzJimPPYZzbKNoPB4zHakzcEnWCGrRQCgnKs1oeOLfoot4NmrkmzIm4V6wsob6";
    size_t size = strlen(buf);
    std::string expected = "b0356bb9485d5c0d5ec3fa68ac0e91e3";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "fhox8ACMbFZpXT09abjzJvrssLIGKCkPKwdGXDhY86cTN2SL118ynoRDZp9ASh";
    size_t size = strlen(buf);
    std::string expected = "958fc0b871395eeeba6f26d63f1bbed9";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "qDgUqH1fEVhny767ZV6n8k4B7iyvYFzc9DWn9OsDxxOUvIRiuLvsToSRueaiKxkH16U";
    size_t size = strlen(buf);
    std::string expected = "2b3efeacdc72d39f63d646af45ed8f48";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "Ibr6w3QPCvXW7hcQvSvPXuVvR32GZKuwJJq6D4L5pxRkERZZAkCnClIkeyO369nGIDA";
    size_t size = strlen(buf);
    std::string expected = "762f57adc3a890b371bb7845213bd42c";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "x94LwJV0rKNPTd2loytsU8kO5xkDZIBkIvV43FTifwXYyP8Mbr5VpdxiAIKnebyMuhFnMo"
        "vQ";
    size_t size = strlen(buf);
    std::string expected = "7368a8bb69510267bee3b37bea890cdb";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "iC6VAHWSAF5D3e1zOfBNBe7IHljVEZrNrmwQThyhKrKBtBY5GqI5uEE1PLKhAZSPbfvSmR"
        "ZU";
    size_t size = strlen(buf);
    std::string expected = "1ca0a5da9ccaf942fa13b2b6e9602426";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "xmqZaktqQpIkRzXs75QXNtWQPD0uqLrOXGBVQUcu7KFO8q45jISX2DBF6sZm3h0ONrzraz"
        "L7aeK6v";
    size_t size = strlen(buf);
    std::string expected = "87dbc35bdc15ebbc9ab59b90d6e0c7ae";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "1CbIp1bPw57jhYq6A1lZijnSflWPhfh8IgEV5DAryvBEjPAJHJxNRIvWTgB0lGWRLrBGU1"
        "WjllLs0";
    size_t size = strlen(buf);
    std::string expected = "088b2c6fc3d158fc42f106f7fb22661f";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "0vIn9pTubCAAsK5crGtSccIWjT7U9YTZhpagDTBElZ3BzYEPuVvuX1h4IcOI0vx6LycehB"
        "GrrxSOlkrD6N";
    size_t size = strlen(buf);
    std::string expected = "3285c40e1c8c9aaf9d6439bae9c80607";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "RE3Md5oLUI8QjuSlCiPTzdzboItSE6EjyxTBq6aaE7QLrxWTFBA2EY3TwkzYe37DoP2EL1"
        "DdYjOfEAX7Zl";
    size_t size = strlen(buf);
    std::string expected = "a117c7e3e5a552a1fe694eb5b09f370c";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "s9P9vZyj4pfvDSn5reyu0G868wR6j2TB2yAlmWvgbyBCgMyxPWRFqNzp7gle72GZp4aBRt"
        "FSR4jXGHijrXNGAcV";
    size_t size = strlen(buf);
    std::string expected = "ef2505199de2a55a9e816898f18f93a8";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "h4AeW439W1ADj3k0XtMsYSBdGeJ6fuqmmOo7Gf6s6vWfo44clEu9mTaSYKN121bfFpcbu6"
        "rorbuG5mIgO2d0LcH";
    size_t size = strlen(buf);
    std::string expected = "06ce93a8f5c2e840802c8191fa308ee7";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "KimC9nFECFDWCSbTUtpPDVUhLV5lVCIvKTWH6r9xVChnlg43ziG03q5Fa1QVrmf031x0gx"
        "l1Xsc6z7ZWdwL4KGzIxduP";
    size_t size = strlen(buf);
    std::string expected = "f96fc5a198518c0541d7efebc1066bf3";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "zDfo03ulem9xo3UjTGmdhhNMEm9GEMS1fXf4RzfTJcgW6Y5NtgQylraNBaj3KZUOLXGqlJ"
        "9UMeGG2AjlGXKRcKuEICxh";
    size_t size = strlen(buf);
    std::string expected = "c085574a4d39285efd8d6972c53007d8";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "gV03pgcYgXyir4aRbmlWU2Zult1LO80URPM6TOUZzj5Pb6wdgIZ0yMiH59iI57sMM2GvFr"
        "j2yeHx84yeAm4YYduSaCq6xGI7z";
    size_t size = strlen(buf);
    std::string expected = "5bb1779540494ce0be20745e0225bad5";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "t2uAUQCqdBiAFIMyuABMiBfyxA54ys7Pirf05Fg66owAU8YdzpPFOS4ajX4Fd1klgpb9Ug"
        "5Pssfbq3cNgPjUybSFYM81BiaFv";
    size_t size = strlen(buf);
    std::string expected = "d038c64b23fdaf9f73749f313f3750f7";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "EdfASyQVz6OBKSgRDCSj5GW3vlbvPuujyAHgWn2liEKQnQxOhfXaJH44T3nwoHFM5bQRmI"
        "0ubAaofx0kALk9je306emkKPUFOAl179";
    size_t size = strlen(buf);
    std::string expected = "48db939a3aef1e711c40c926a5714e41";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "8AkkDFaN4LV3S0VIUZS4zwO3aec1bbb7Bjh2MfDGPpyxdj4X6KRw6tn7vpWxqVsQ4AIFFa"
        "bkpxGsGyfD8UX5d80ynMTBychqAOV5MV";
    size_t size = strlen(buf);
    std::string expected = "d18d14f780218c5e459f970a15b7bf91";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "1iIhN6me24ZX7XNtaobzKdF0DhKwTvyKB4Rc01gTV5EQQg7Os8e29JSAQsXzLj7beMd2Di"
        "Jmbe2SiZuAWysV58mJp760e3ZiF1967Ii8K8O";
    size_t size = strlen(buf);
    std::string expected = "fdd41d8fc1bcab672934bb0d7e9ee259";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "Y9gIvytrvDYKyVyDMoJgfIccfj8PhNw3KAB3XTkim7SLSgcsuLyxizxnIw0N7kHFL6yyPH"
        "G2EoBksDCNc18kowvUQmxNu2g5ZErEbXuD9TN";
    size_t size = strlen(buf);
    std::string expected = "bcfb8beb9dade7318405fe3829d54b57";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "kg3n5ZxhlT1Z3mAnfGj29yuamNCjwfzHjqUcgfhpW8fPjD1oa8e9wy7I9zQwDd1KuJLyOS"
        "NzRQeYk5ci3ehqAcWAAAW3ELBWkckWVVlAAooIhoQ9";
    size_t size = strlen(buf);
    std::string expected = "156efa54c62979c87974931cc0261bda";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "VpQV9gly0c2BEOJGWwpHFN7TZD1bjYr2b8OaeXw50ouu04YKociTPdBFHqEOeWFfUhdW4A"
        "RUMacB41bi3hZGjo9OEEqIqVL80PUVdCDPCGeuvgAo";
    size_t size = strlen(buf);
    std::string expected = "c9dc06fd1558ad7e43f5bdd0977274d5";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "nSuCS86kpDA8cyZRiISIbw8HAq0EQeQ2VauB7qLkR9iUx7zDDiaFE6a4l1zZ3dROdbf8qO"
        "i7NrR8mfCQnAjRujJFa6v29cEbeK9soip0x5YHaolnOu29C";
    size_t size = strlen(buf);
    std::string expected = "a458e315845286ac94b97bb03e85d3c7";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "CAwXsvYXu2vukHAxxVsmqqACBdUtamRCNdq5wcQR2b9aJxx4gOgw4FYuIJLITsawvoqSq6"
        "xi6uiDRExViEha94uHB6dkodHIqVoGRLNL5TeKnCvv4Au1u";
    size_t size = strlen(buf);
    std::string expected = "303c1a294622eac87a48214c1939cdf0";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "yVIz4XCBvQkJlZiYBbHFJV52eZsyQNbcwJBqw2PPIZmRNsFerbJ0UDSYs9l9Kmb6TBletY"
        "TZM4HpmatCb0sTt9GM8RJI1ICK7LOoAwecqJrAHI0HyjqQgWqcBZ";
    size_t size = strlen(buf);
    std::string expected = "7041df74971f3b3870953929455f8c03";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "qva1tMDHcZJcdgtCO1slnzB1FmhHL4f2ogTHQmcQaMSbSbDw0UFbj53Nh8iS1oKfsrM6CO"
        "MAouB7v3rjNXiUQ9xX8GDZSc4arE6TiIhv0JslAHsdsAV8AjTwNl";
    size_t size = strlen(buf);
    std::string expected = "fa28cbbd2cd1e209e72a7b9ac01c4cb9";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "vndtEHnmNVt8L0oUqUarayd9WkQiX1rgeszHXMRzv8v4ZIMdsKts8upVC61pXht0zSxlse"
        "KLa5FZBf1TPiaLAnw2jmh5tAVQgg1wiz7itA6UFXEi3CTtPelXqqSJODp";
    size_t size = strlen(buf);
    std::string expected = "834c27730b4d83b88d93b777bec66a96";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "JfeREbZXzTI2EaaxCROfVZ29dKIRbWzI1BntAdhZUNPpNPMdvriee9eiJMXJwnhnMvHdwM"
        "0gpGv0j63En9Jp8NxGnlfKwmV8Fq91006fwr5FnWayWHOUi9qvkt3EEPB";
    size_t size = strlen(buf);
    std::string expected = "d783380ed84265e7ced95f21852f0487";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "3AZUqVXMcRgoDeKpLo8TmmcuG6ZaJq7AOWk3H6DINJUgNuumHs5TC6d8006xe2XTO6Mk2d"
        "QFNyLqQ3Bnlu4Oq6KgWFDZxpI9lihblVGWjfbY9C9iW4UbYthKYJzjW5g7bm6l";
    size_t size = strlen(buf);
    std::string expected = "dd39c8b0d47d7de915a7eb35b06cfc22";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "C5dF61Cw0LjStkGMpfyWCHIwMDxWzGRZAUvwLXTCw0iQ8PslUR8mmEIW84IvyqlY8EjKp0"
        "aMQiqMVIXFnTSyookmiRFF5Qt3kCBAsBa6IqItWuZadFwrREBYl7tgLK8Udzit";
    size_t size = strlen(buf);
    std::string expected = "e5f91e866152cf35ebf85ab163dc57dd";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "ioxwWQieDgi6CxM7XAgURltrjdsIlKxrYSNIxUN00VVrgxm3VqLCB5TK6ahiKCxyj96GTJ"
        "uHsdWzA8qln2LOXvnTvsZ5Snr1mnx3XQAdTlCihTruJ39wmkdFC1ykcPcm2xfNdDRXO";
    size_t size = strlen(buf);
    std::string expected = "8d869788a1a0e17996948c226ade1e50";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "5UYmexddTpnVUNKiYMXYYOl1rns6a5e3P2dTqhV7w6QfKqnw29kONvD2IUZGP3xsTB99GU"
        "50PL5p2hJSeTvRcWHJGwfjnBz50z4whXkWze9pjI5npq2sbz1FU4P5tc0jBTDJGMt3Q";
    size_t size = strlen(buf);
    std::string expected = "51441af911709253da717b22e1fa9abc";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "iZZecfs4vtrmZbeC5yEVF6C7D9JW0pd9c3de6v6rPnBCnD4iZy1vssqVpZGfeJeeAfiwBc"
        "LencEAEyGtUwMdO2W1Ps6R0bVqg1LF3mHhnbFPxa8iuJj6z5XfmTWcSIqXz1qrcYynX12l"
        "10";
    size_t size = strlen(buf);
    std::string expected = "5172256a1545d787abc1520685fe67a8";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "jxCfXv20FKMFsiWdILuXLgjY3aQe0Fx92XfNh7DMHggYm21SBjFdpOZjPGnDbJC1uHFzD8"
        "c8ciWp8M7xVDybhoiUSvnT2QKlldKMcKLcSvrO5naPQyQVKWEsfRb8vKhFNRhNsQQ8a5L3"
        "iL";
    size_t size = strlen(buf);
    std::string expected = "ba694655e030dece933dfb4a6b3765bf";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "W7mGI8a0eR0abyhG9YLNeqrdqmMjtnQfi2LQ1LF5rv5sRaWQYxr1NI21TE9cPPfXFREwq7"
        "pFqiV7iHN535WEBOukitmX6qIB7aWl7bPnkAiq6UlXN7peJJnR0xCWN9mI98U77zifXpwT"
        "9FEMBUO";
    size_t size = strlen(buf);
    std::string expected = "d8b88bab0ffe85804ecb9b3c4a71b688";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "t1Qipg22feBfaja8Ggdrvz9s5D2unHuFwaNJfDCkI1nG8nECsITN5S4YmWixrB2OzDnE5N"
        "PBC07AcC2u8K51sZQCMW03nQFNiThduUEXJBnL1e5ZO0P4Ovxohnft3L6bsbcMUGxt6J2X"
        "NXLpLqj";
    size_t size = strlen(buf);
    std::string expected = "0fb1fbe0ba22bb1bcee9aee181e4c5fd";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "JGBORH5Li1Ky1L8Jhw0b5SXGDyVeM2sjzRVgoRPuGoSxZP44bU66ATC3fl8PdoWA5HFioi"
        "AVwhgjWbcXT8RkPhbSs9vtlhUfOpl1vLMQSQZCP1nzX4HAbIirGDLPItSnG3e1DOHjuvMa"
        "kZx6U2wTyD94";
    size_t size = strlen(buf);
    std::string expected = "f3725b91f80396dd61e989642604e173";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "KID1qOxkQmNuUWMdwKnm5h4VELk5KcZkKsb14w9KJK2ruDuRdF17NVSfw0a53ZfBgfqazp"
        "L8XDni6FX8bM3MvJRRARKrEQSKT9LgmmdaNqgIW1EVDvxY4eDsTeJnSsYzrxFDHIBkXHQJ"
        "wiuZDPNyThQA";
    size_t size = strlen(buf);
    std::string expected = "955d56818b7f5847997eccaa602eac6f";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "qN1GBqVYVmtsOEfjiOGr6vUL7gscXSlbtcFTqqF9CZretwoz8SQ2dBB8FTaszlrTlWCBc5"
        "BDUSHbdVB9Dh2FGtDcbCsANIhXuHovDNYnuvpxfQwGVm9qGBqH3I5EgbrzIEU9hGnBZAW4"
        "ehzZtydXXtsQ2ol6n";
    size_t size = strlen(buf);
    std::string expected = "9bcf032ef822ac205a651b3ba7012e8d";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "vV4dTaJ4zzukryrQlIdnw0GOHy0QtdgOX9QG9pAyOSI6eXKnwNAQC7s9thNMkRp5Q5BPiZ"
        "cVHIPLwpZQ1putmMqET3g2ItXpmn2vc2gKBVjV86BXmTgwvu0dl55UmQ9z3ZS4SYCjHL2D"
        "ItrSavcvQ3wZWpJ84";
    size_t size = strlen(buf);
    std::string expected = "543166fe4df826ce239567c626a5ffce";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "vXwdPcZhluRdYnud5uw7NaY80InxHf423o4GqTOzetA0GS1zanuLojJePVzm0tdRF7oTO0"
        "iShGGNoxaoLu0XBzZhior9GsObp2T2Q1IXwfyKAyZ9RNWgaJnjYDguVUt9Lc1p2xdoCBY3"
        "YL0FmNJnmVu8oAs7iK4RMT";
    size_t size = strlen(buf);
    std::string expected = "1e278fdc14bae07ab937447fb47eb1ac";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "Eh8QJxFAlerOr2oCc9WblkriqZd8CW3431LBmeZwgeav6mX7jJ8sTnz8dA4DkXveM4DY6q"
        "kdvjyrtmmBTiTBwgzxGt0RgjTQemCaCNdXUAdbKnCtwkUQqhdXA1CEalkexLdXmeJ6EK5e"
        "XywhGeXUm0FMP7fOinSDYT";
    size_t size = strlen(buf);
    std::string expected = "5f059023fac5e12a89838b049388e45d";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "aYY4sw0vhmRpSVcC716IG3NkcY1FNKUNwGGP0w88IPloynOucK0HEBPEpE92fSEBmaeduc"
        "90PkecvSwwrm3TLIn0dkRg0jFdhIeBIbrojtqC9KYqUR9vokjpv0tl9WmeuqF3rUfydt1b"
        "3PrNvp6HzfWS4d41Zg6kvzbKie9";
    size_t size = strlen(buf);
    std::string expected = "0973bcb4228da5711462cf0fb22adc85";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "x0koFAZ0PVxcYhVSkPK8TEie3hPblMlGCvU7TJWyuhzgnkZvXztE3zJUGmWPY5loo3j8C5"
        "uUbT1o3OHOd1j4qQMV0wAMrK0EB7A43UM2EBevfL8gCf8TVLCJ70lny9R06hSXZuNtWRN1"
        "tJ6TO4AzF26DTfOhcv76APUp8xH";
    size_t size = strlen(buf);
    std::string expected = "d45a5125860d603e3c8c0e2671aa1c4f";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "diHuRDdvyES3uOubR8jTrePRSx5OVAwWI3gnxjGVLoM6075H5eonh32XrVBalVWRO0499A"
        "SJMvDAsy5lBjwGbnts8SqiDcZf2UdZiVwTgZjwmfGNm2jndADcgTkHT7KJRNzYzVHDJO0V"
        "Rww2mDfq3Jq9qyEaveJbS6XfQsIp6y8M";
    size_t size = strlen(buf);
    std::string expected = "b478825b038ab83cae0f6a1164e47629";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "uE3XHhOgxLvVfvej4fZZ04FiDUfZSPGajzXQGzV1agKdzOmrSagI4LRxtUl9zR9GgUkKj3"
        "Bh7bkwPvMvvS4psJLLrWLQDKkHtuhCoIIlJSGmbiIw0AKi9lSo7t2y1c5kucLIIjShZmr1"
        "uZninXpk67y1oqpfsiqLiZhQ8ZVVbdMt";
    size_t size = strlen(buf);
    std::string expected = "653fe6a645e1e3147362bc2330d10c78";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "YCcJRmGMLv0ZL5gRjRY8YE4MoQLpq5dexfOcsiO1BEQazUSHBGFo8y0meBzuwDxRI9TYfv"
        "PGZuHnepUETnSRJG2N7r6sUt7rqPfvaT1YbybdLTHu4naET2fPhb70s4hIJk3I3Tw4hx6R"
        "eDb6P9Ay1Ed9D8ZW34sAek883u08PUPRoPM3O";
    size_t size = strlen(buf);
    std::string expected = "003dac47602a5738f9c79c755317a7b4";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "pGErD8pqSikaHmkDidW7czRRf5uRW9RaDmr6kGk2Ns0iEbLNcxKeVrU0leH5bo5EykAGRI"
        "ws0nAvo98ovItgXb68dB2fNXJc68ING53xgrSsqOGLkXP7YL40aW5OHCQDAme5f7qlo6DD"
        "KaeSXSPKrHAstt6ZVKskWxf0svbFpD8ZBaFmS";
    size_t size = strlen(buf);
    std::string expected = "7f9098a07570b006f52d962477399993";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "WaQks7DmWnWfxGAAwSTwl8ZjVqkqC0yn0exgaZsWccZxJnV34EpfAcplqxzTnX4e0pk0cB"
        "KcDAzaLk4FMhLckYlAlKhyy9AmpJcpaMsDaPEM0yfADQDLCMaNnhaJfyVs7VH7xZBwF56t"
        "rbTSQkuiVuU8zSHEgqWebsbyhASKtO1IOJruTLAE5i";
    size_t size = strlen(buf);
    std::string expected = "e3a2d608d9c6c7f9ec38885d0ed65025";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "s05X7lH9mZaJ5zpDS4vrG4I0LhoeaxEslAdiJLfUygtrDIVlAgA6a8ULd7PduiwFGxMf8R"
        "ZvVgMoNvydBY8zVQ9YNM27UmBqJbuGQh1CoBO1Xc2mZYMKFLyinoe6ADk8ECEkKtKWSpLF"
        "pBQeqqMV191cn56OyfM0HebhxJ1fWCJc4nekDP3sOU";
    size_t size = strlen(buf);
    std::string expected = "0406a42fe81fc8bd7df098bedc80b390";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "1OpDaud1Zh07CzWGmpdmjqorR3i9H2pxEE0FW2wM9mHAJt4VG75Nlk20daZJ1e6vHUYrMk"
        "1Kuwa4O2NkXJW8ROWUPLrGNlZi6OAIWpghMe9q6KyThkPYZBHEaY8MaVU4ziAkyHr8LooG"
        "YMp6V3UKupcte85cTN6hWwpi3GgDSs9E2myNfhlywlRAjKC";
    size_t size = strlen(buf);
    std::string expected = "b6121ca714b7a67f26ba1b5eee0b4e7d";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "nw67TldMPhfvzcZqpo3utdQPoxew5Enh1heKsgk5noqLqf1DrSYKVEq80suTWF0NM3l49w"
        "ZkKfVYiMsAve8eGmcuEuerZ22BVetSAg38jMUspcQIeOKL1L3t57KV0DmJHGq5Kj3UVLc8"
        "MSEQudpjOjDHebs2EDC97S4HZVrIvtF797Nsa1zM82kc2C5";
    size_t size = strlen(buf);
    std::string expected = "c7e04cf8b11894a5a8c9b5722338da0d";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "3vu0bmyY6Nur5Zo2VZkTOKwMAGPs6INY15O0haMbO6qHUCzFsIm4gIHGckX7SyVHtxxyy9"
        "Aa3QHNj4gzCttIZYf280XQoIlF5I3rFrpz8UafPhChyVOnIRfGH2lTywos3fHyxXVtFUyk"
        "10qnJ4AhLEOguXZTjb9agGxDtiWZ2k7R8l4GftLOXnUhaHYkIXkP";
    size_t size = strlen(buf);
    std::string expected = "42c18ad5ad773d524be3cba862a645a5";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "HiLO3yEbukaFcELvfngt6otDaBaYKPihVRTOgmOAwO5ygESlQYEMaYdbpdXZS35CKMeOYS"
        "cku6HAApMebeQc2UbgXW3EPW4pz82nP4w901ypg8tfcaf5Se9D027FN1TcYLnDDHCuyYHC"
        "W0GZYLSEQR8GH5akVRkJswcT1CbqrIQbzm0lWIQCnO6VH43sLcZ1";
    size_t size = strlen(buf);
    std::string expected = "c7068fa689167b8df475fd6e162aa08a";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "1LnsMBHliIIszRe5xEj9z2HtTX5VNUfEvtU6Urf00NjnuliQQrPdjmw3apML8Sft9YnTfs"
        "I35PgoYp2CEHFMS0FQffrbVuvUiICmZafUNm6BzY43uzFcp8Qtc7uXpNIyk8I96NRJXM8m"
        "y2gSqJSDIyUKtdvJO15YZDVVeBs2bpezhiivSYXonHWEIfdn769UxTECk";
    size_t size = strlen(buf);
    std::string expected = "b74b6225c3f19fc3fd84f8ade86b890c";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }

  {
    const char* buf =
        "ulbwIhDQAlFnxQThkrmmEjgE4Eny4vimEiIcn9RNkk1FYKM81Ziu8pW0R7mLsvXUBtWOtB"
        "rBLg7xOHwEwCYtPIhwFu7VNSFeapQrP5QocLMQj6iDy4WeC2A7mwSXcl1azHreC6qCH2hQ"
        "Ypink2pMUPI69oRayIaVdqXEmd4T6byUpE5xwk7hYDbVSTVepWZrcMVmP";
    size_t size = strlen(buf);
    std::string expected = "cfc0fd653a1737dd9cba45bdd6aef5ba";
    mcppkits::MD5 md5(buf, size);
    std::string result = md5.to_string();
    assert(expected == result);
  }
}

int main() {
  test01();
  return 0;
}
