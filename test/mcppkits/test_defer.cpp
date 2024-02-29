/*
output:
main start num = 123
Some actions..., num = 456
Deferred executed 1, num = 456
Deferred executed 2
main end num = 789
*/

#include <iostream>

#include "mcppkits/mstl/mcppkits_defer.h"

int num = 123;

void test01() {
  num = 456;

  DEFER([]() {
    num = 789;
    std::cout << "Deferred executed 2" << std::endl;
  });

  DEFER(
      []() { std::cout << "Deferred executed 1, num = " << num << std::endl; });

  std::cout << "Some actions..., num = " << num << std::endl;
}

int main() {
  std::cout << "main start num = " << num << std::endl;
  test01();
  std::cout << "main end num = " << num << std::endl;
  return 0;
}
