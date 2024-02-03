#include <cassert>
#include <iostream>

#include "mcppkits/mcppkits_fixed_size_string.hpp"

using namespace mcppkits::mstl;

void test01() {
  string_255 str("hello");
  assert(strcmp(str.c_str(), "hello") == 0);
}

int main() {
  test01();
  return 0;
}
