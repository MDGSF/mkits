#ifndef MKITS_APPS_CALC24POINT_NET_THREADPOOL_H_
#define MKITS_APPS_CALC24POINT_NET_THREADPOOL_H_

#include <cstdint>
#include <memory>
#include <thread>
#include <vector>

#include "net/EventLoop.h"

class ThreadPool final {
 public:
  ThreadPool() = default;
  virtual ~ThreadPool() = default;

  ThreadPool(const ThreadPool&) = delete;
  ThreadPool& operator=(const ThreadPool&) = delete;

  ThreadPool(ThreadPool&&) = delete;
  ThreadPool& operator=(ThreadPool&&) = delete;

  void start(int32_t thread_num = 1);
  void stop();

  std::shared_ptr<EventLoop> get_next_event_loop();

 private:
  void thread_func(size_t event_loop_index);

 private:
  bool stop_{false};
  size_t last_event_loop_index_{0};
  std::vector<std::shared_ptr<std::thread>> threads_;
  std::vector<std::shared_ptr<EventLoop>> event_loops_;
};

#endif  // MKITS_APPS_CALC24POINT_NET_THREADPOOL_H_
