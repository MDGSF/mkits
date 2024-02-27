#include <cassert>
#include <iostream>
#include <string>

#include "mcppkits/mcppkits_raii_wrapper.h"

class Student {
 public:
  Student(int id, const std::string& name) : id_(id), name_(name) {}
  int id_;
  std::string name_;
};

void test01() {
  mcppkits::RAIIWrapper<Student> stu(new Student(123, "John"));

  assert(stu->id_ == 123);
  assert(stu->name_ == "John");

  assert((*stu).id_ == 123);
  assert((*stu).name_ == "John");
}

int main() {
  test01();
  return 0;
}
