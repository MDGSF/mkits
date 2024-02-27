#ifndef MKITS_INCLUDE_MCPPKITS_MCPPKITS_COUNT_DOWN_LATCH_H_
#define MKITS_INCLUDE_MCPPKITS_MCPPKITS_COUNT_DOWN_LATCH_H_

#include <condition_variable>
#include <mutex>

namespace mcppkits {

class CountDownLatch {
 public:
  CountDownLatch() = default;
  ~CountDownLatch() = default;

  CountDownLatch(const CountDownLatch&) = delete;
  CountDownLatch& operator=(const CountDownLatch&) = delete;

  CountDownLatch(CountDownLatch&&) = delete;
  CountDownLatch& operator=(CountDownLatch&&) = delete;

  /*
  @brief: Initialize with count.
  */
  explicit CountDownLatch(int count);

  /*
  @brief: Wait block until count reaches zero.
  */
  void wait();

  /*
  @brief: Decrease count, if count reaches zero, notify all.
  */
  void count_down();

  /*
  @brief: Get current count number.
  */
  int get_count() const;

 private:
  mutable std::mutex mutex_;
  std::condition_variable condition_;
  int count_ = 0;
};

}  // namespace mcppkits

#endif  // MKITS_INCLUDE_MCPPKITS_MCPPKITS_COUNT_DOWN_LATCH_H_
