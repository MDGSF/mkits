#ifndef MKITS_APPS_CALC24POINT_NET_THREADPOOL_H_
#define MKITS_APPS_CALC24POINT_NET_THREADPOOL_H_

#include <cstdint>
#include <memory>
#include <thread>
#include <vector>

#include "net/EventLoop.h"

/*
@brief: 线程池，每个线程运行一个 EventLoop。
*/
class ThreadPool final {
 public:
  ThreadPool() = default;
  virtual ~ThreadPool() = default;

  ThreadPool(const ThreadPool&) = delete;
  ThreadPool& operator=(const ThreadPool&) = delete;

  ThreadPool(ThreadPool&&) = delete;
  ThreadPool& operator=(ThreadPool&&) = delete;

 public:
  /*
  @brief: 启动线程池，通过 thread_num 指定线程的数量。
    start 函数返回后，所有的线程被创建并在后台运行。
    每个线程运行一个 EventLoop。
  @param thread_num[in]: 线程的数量。
  */
  void start(int32_t thread_num = 1);

  /*
  @brief: 停止线程池，并等待所有的线程退出。
  */
  void stop();

  /*
  @brief: 从线程池中获取一个 EventLoop 的引用。
  @return: Reference to EventLoop.
  */
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
