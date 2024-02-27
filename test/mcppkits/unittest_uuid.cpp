#include <cassert>
#include <iostream>
#include <set>

#include "mcppkits/mcppkits_uuid.h"

void test01() {
  for (int i = 0; i < 10; ++i) {
    std::string uuid = mcppkits::UUIDGenerator::uuid();
    assert(uuid.size() == 36);
  }
}

void test02() {
  std::set<std::string> s;
  for (int i = 0; i < 10000; ++i) {
    std::string uuid = mcppkits::UUIDGenerator::uuid();
    assert(s.find(uuid) == s.end());
    s.insert(uuid);
  }
}

int main() {
  test01();
  test02();
  return 0;
}
