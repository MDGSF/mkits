#include <cassert>
#include <iostream>

#include "mcppkits/core/queue/mcppkits_list_queue.h"

void test01() {
  mcppkits::queue::TListQueue<std::string> mylist;
  assert(mylist.size() == 0);
  assert(mylist.empty());

  mylist.push("hello");
  assert(mylist.size() == 1);
  assert(!mylist.empty());

  mylist.push("world");
  assert(mylist.size() == 2);
  assert(!mylist.empty());

  {
    std::string word;
    mylist.pop(word);
    assert("hello" == word);
    assert(mylist.size() == 1);
    assert(!mylist.empty());
  }

  {
    std::string word;
    mylist.pop(word);
    assert("world" == word);
    assert(mylist.size() == 0);
    assert(mylist.empty());
  }

  mylist.stop();
  assert(!mylist.push("hello"));
  std::string word;
  assert(!mylist.pop(word));
}

int main() {
  test01();
  return 0;
}
