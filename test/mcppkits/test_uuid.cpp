#include <cassert>
#include <iostream>

#include "mcppkits/mcppkits_uuid.h"

void test01() {
  for (int i = 0; i < 10; ++i) {
    std::cout << mcppkits::UUIDGenerator::uuid() << std::endl;
  }
}

int main() {
  test01();
  return 0;
}
