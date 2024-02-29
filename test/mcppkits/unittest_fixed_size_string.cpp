#include <cassert>
#include <iostream>

#include "mcppkits/mstl/mcppkits_fixed_size_string.h"

using namespace mcppkits::mstl;

void test01() {
  string_255 str("hello");
  assert(strcmp(str.c_str(), "hello") == 0);
}

int main() {
  test01();
  return 0;
}
