#include <cassert>
#include <iostream>
#include <thread>
#include <vector>

#include "mcppkits/mcppkits_count_down_latch.h"

void test01() {
  const int num_workers = 3;
  mcppkits::CountDownLatch latch(num_workers);

  assert(num_workers == latch.get_count());

  latch.count_down();
  assert(2 == latch.get_count());

  latch.count_down();
  assert(1 == latch.get_count());

  latch.count_down();
  assert(0 == latch.get_count());

  // count <= 0, will not wait
  latch.wait();
}

int main() {
  test01();
  return 0;
}
