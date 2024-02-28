#include <cassert>
#include <iostream>

#include "mcppkits/mcppkits_singleton.h"

class MyClass {
 public:
  void add() { num_ += 1; }
  int get_num() { return num_; }

 private:
  int num_ = 0;
};

void test01() {
  assert(mcppkits::Singleton<MyClass>::Instance().get_num() == 0);

  mcppkits::Singleton<MyClass>::Instance().add();
  assert(mcppkits::Singleton<MyClass>::Instance().get_num() == 1);

  mcppkits::Singleton<MyClass>::Instance().add();
  assert(mcppkits::Singleton<MyClass>::Instance().get_num() == 2);
}

int main() {
  test01();
  return 0;
}
