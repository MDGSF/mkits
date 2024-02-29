#ifndef MKITS_INCLUDE_MCPPKITS_CORE_QUEUE_MCPPKITS_MPMC_H_
#define MKITS_INCLUDE_MCPPKITS_CORE_QUEUE_MCPPKITS_MPMC_H_

#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <vector>

namespace mcppkits {
namespace queue {

/*
@brief: Message queue, thread safe, fixed queue capacity.
  Support multi-producer, multi-consumer.
  One message can be comsumed only once.
  push behavior when queue is full: block until queue is not full.
  pop behavior when queue is empty: block until queue is not empty.
*/
template <typename T>
class TMPMCQueue {
 public:
  /*
  @brief: Disable default constructor.
  */
  TMPMCQueue() = delete;

  /*
  @brief: Default destructor.
  */
  ~TMPMCQueue() = default;

  /*
  @brief: Construct queue with capacity.
  @param capacity[in]: fixed queue capacity.
  */
  explicit TMPMCQueue<T>(size_t capacity)
      : capacity_{capacity},
        buffer_{std::vector<T>(capacity)},
        pread_{0},
        pwrite_{0},
        stoped_{false} {}

  /*
  @brief: Disable copy constructor.
  */
  TMPMCQueue(const TMPMCQueue&) = delete;

  /*
  @brief: Disable copy assignment operator.
  */
  TMPMCQueue& operator=(const TMPMCQueue&) = delete;

  /*
  @brief: Move constructor.
  */
  TMPMCQueue(TMPMCQueue&& q)
      : capacity_{q.capacity_},
        buffer_{std::move(q.buffer_)},
        pread_{q.pread_.load()},
        pwrite_{q.pwrite_.load()},
        mtx_{},
        empty_{},
        full_{},
        stoped_(q.stoped_) {}

  /*
  @brief: Disable move assignment operator.
  */
  TMPMCQueue& operator=(TMPMCQueue&& q) = delete;

  /*
  @brief: Returns the queue's size (current element count).
  */
  size_t size() const noexcept { return pwrite_ - pread_; }

  /*
  @brief: Check if the queue is empty.
  @return:
    true: means queue is empty.
    false: means queue is not empty.
  */
  bool empty() const noexcept { return size() == 0; }

  /*
  @brief: Check if the queue is full.
  @return:
    true: means queue is full.
    false: means queue is not full.
  */
  bool full() const noexcept { return size() >= capacity_; }

  /*
  @brief: Push a new value into the queue.
  @param value[in]: input value.
  @return:
    true: means push value success.
    false: means queue is already stoped, can not push value into stoped queue.
  @notes: When queue is full, push will block until queue is not full.
  */
  bool push(T value);

  /*
  @brief: Pop a value from the queue.
  @param value[out]: output value.
  @return:
    true: means push value success.
    false: means queue is already stoped, can not pop value from stoped queue.
  @notes: When queue is empty, pop will block until queue is not empty.
  */
  bool pop(T& value);

  /*
  @brief: Stop the queue. When queue is stoped, push and pop function will
    failed. At the same time, blocked push and pop function will return
    immediately.
  */
  void stop();

 private:
  size_t capacity_ = 0;
  std::vector<T> buffer_{};

  std::atomic<size_t> pread_{};
  std::atomic<size_t> pwrite_{};

  std::mutex mtx_{};
  std::condition_variable empty_{};
  std::condition_variable full_{};
  bool stoped_ = false;
};

template <typename T>
bool TMPMCQueue<T>::push(T value) {
  std::unique_lock<std::mutex> lock(mtx_);
  for (;;) {
    if (stoped_) {
      return false;
    }
    if (full()) {
      full_.wait(lock);
    } else {
      break;
    }
  }

  buffer_[pwrite_ % capacity_] = std::move(value);
  pwrite_++;

  lock.unlock();
  empty_.notify_one();

  return true;
}

template <typename T>
bool TMPMCQueue<T>::pop(T& out) {
  std::unique_lock<std::mutex> lock(mtx_);
  for (;;) {
    if (stoped_) {
      return false;
    }
    if (empty()) {
      empty_.wait(lock);
    } else {
      break;
    }
  }

  auto value = std::move(buffer_[pread_ % capacity_]);
  pread_++;

  lock.unlock();
  full_.notify_one();

  out = std::move(value);

  return true;
}

template <typename T>
void TMPMCQueue<T>::stop() {
  std::unique_lock<std::mutex> lock(mtx_);
  stoped_ = true;
  lock.unlock();
  empty_.notify_all();
  full_.notify_all();
}

}  // namespace queue
}  // namespace mcppkits

#endif  // MKITS_INCLUDE_MCPPKITS_CORE_QUEUE_MCPPKITS_MPMC_H_
