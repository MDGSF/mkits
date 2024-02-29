#include <cassert>
#include <iostream>

#include "mcppkits/mstl/mcppkits_singletonp.h"

class MyClass {
 public:
  void add() { num_ += 1; }
  int get_num() { return num_; }

 private:
  int num_ = 0;
};

void test01() {
  assert(mcppkits::SingletonP<MyClass>::Instance().get_num() == 0);

  mcppkits::SingletonP<MyClass>::Instance().add();
  assert(mcppkits::SingletonP<MyClass>::Instance().get_num() == 1);

  mcppkits::SingletonP<MyClass>::Instance().add();
  assert(mcppkits::SingletonP<MyClass>::Instance().get_num() == 2);
}

int main() {
  test01();
  return 0;
}
