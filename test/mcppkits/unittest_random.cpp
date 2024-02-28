#include <cassert>
#include <iostream>

#include "mcppkits/mcppkits_random.h"

void test01() {
  std::vector<uint8_t> bytes = mcppkits::random_bytes(100);
  assert(bytes.size() == 100);
}

int main() {
  test01();
  return 0;
}
