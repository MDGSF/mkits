#include "mcppkits/mcppkits_count_down_latch.h"

namespace mcppkits {

CountDownLatch::CountDownLatch(int count) : count_(count) {}

void CountDownLatch::wait() {
  std::unique_lock<std::mutex> lock(mutex_);
  while (count_ > 0) {
    condition_.wait(lock);
  }
}

void CountDownLatch::count_down() {
  std::unique_lock<std::mutex> lock(mutex_);
  --count_;
  if (count_ == 0) {
    condition_.notify_all();
  }
}

int CountDownLatch::get_count() const {
  std::unique_lock<std::mutex> lock(mutex_);
  return count_;
}

}  // namespace mcppkits
