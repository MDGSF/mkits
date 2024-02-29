#ifndef MKITS_INCLUDE_MCPPKITS_CORE_QUEUE_MCPPKITS_LIST_QUEUE_H_
#define MKITS_INCLUDE_MCPPKITS_CORE_QUEUE_MCPPKITS_LIST_QUEUE_H_

#include <condition_variable>
#include <list>
#include <mutex>

namespace mcppkits {
namespace queue {

/*
@brief: Message queue, thread safe, queue's capacity has no limit.
  Support multi-producer, multi-consumer.
  One message can be comsumed only once.
  push will always success, queue will not be fulll.
  pop behavior when queue is empty: block until queue is not empty.
*/
template <typename T>
class TListQueue {
 public:
  TListQueue() = default;
  ~TListQueue() = default;

  TListQueue(const TListQueue&) = delete;
  TListQueue& operator=(const TListQueue&) = delete;

  TListQueue(TListQueue&&) = delete;
  TListQueue& operator=(TListQueue&&) = delete;

  /*
  @brief: Returns the queue's size (current element count).
  */
  inline size_t size() const noexcept { return list_.size(); }

  /*
  @brief: Check if the queue is empty.
  @return:
    true: means queue is empty.
    false: means queue is not empty.
  */
  inline bool empty() const noexcept { return list_.empty(); }

  /*
  @brief: Push a new value into the queue.
  @param value[in]: input value.
  @return:
    true: means push value success.
    false: means queue is already stoped, can not push value into stoped queue.
  */
  bool push(T value) {
    std::unique_lock<std::mutex> lock(mtx_);

    if (stoped_) {
      return false;
    }

    list_.push_back(value);
    lock.unlock();
    empty_.notify_one();

    return true;
  }

  /*
  @brief: Pop a value from the queue.
  @param output[out]: output value.
  @return:
    true: means push value success.
    false: means queue is already stoped, can not pop value from stoped queue.
  @notes: When queue is empty, pop will block until queue is not empty.
  */
  bool pop(T& output) {
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
    auto value = list_.front();
    list_.pop_front();
    lock.unlock();
    output = std::move(value);

    return true;
  }

  /*
  @brief: Stop the queue. When queue is stoped, push and pop function will
    failed. At the same time, blocked pop function will return
    immediately.
  */
  void stop() {
    std::unique_lock<std::mutex> lock(mtx_);
    stoped_ = true;
    lock.unlock();
    empty_.notify_all();
  }

 private:
  std::list<T> list_{};
  std::mutex mtx_{};
  std::condition_variable empty_{};
  bool stoped_ = false;
};

}  // namespace queue
}  // namespace mcppkits

#endif  // MKITS_INCLUDE_MCPPKITS_CORE_QUEUE_MCPPKITS_LIST_QUEUE_H_
