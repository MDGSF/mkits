#include <iostream>
#include <thread>
#include <vector>

#include "mcppkits/mcppkits_count_down_latch.h"

void worker_function(mcppkits::CountDownLatch& latch, int id) {
  std::cout << "Worker " << id << " is starting..." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout << "Worker " << id << " has finished its work." << std::endl;
  latch.count_down();
}

void test01() {
  const int num_workers = 3;
  mcppkits::CountDownLatch latch(num_workers);

  std::vector<std::thread> workers;
  for (int i = 0; i < num_workers; ++i) {
    workers.emplace_back(worker_function, std::ref(latch), i);
  }

  std::cout << "Main thread is waiting for workers to finish..." << std::endl;
  latch.wait();
  std::cout << "All workers have finished. Main thread can continue."
            << std::endl;

  for (std::thread& worker : workers) {
    worker.join();
  }
}

int main() {
  test01();
  return 0;
}
