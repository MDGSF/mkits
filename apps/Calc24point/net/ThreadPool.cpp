#include "net/ThreadPool.h"

#include <functional>

#include "net/EventLoop.h"

static constexpr int32_t MAX_THREAD_NUM = 1024;
static constexpr int32_t DEFAULT_THREAD_NUM = 8;

void ThreadPool::start(int32_t thread_num /* = 1*/) {
  if (thread_num <= 0 || thread_num >= MAX_THREAD_NUM) {
    thread_num = DEFAULT_THREAD_NUM;
  }

  for (int32_t i = 0; i < thread_num; ++i) {
    auto event_loop_ = std::make_shared<EventLoop>();
    event_loop_->init();
    event_loops_.push_back(std::move(event_loop_));

    std::shared_ptr<std::thread> thread = std::make_shared<std::thread>(
        std::bind(&ThreadPool::thread_func, this, i));
    threads_.push_back(std::move(thread));
  }
}

void ThreadPool::stop() {
  stop_ = true;
  size_t thread_num = threads_.size();
  for (size_t i = 0; i < thread_num; ++i) {
    threads_[i]->join();
  }
}

std::shared_ptr<EventLoop> ThreadPool::get_next_event_loop() {
  auto& event_loop = event_loops_[last_event_loop_index_];
  ++last_event_loop_index_;
  if (last_event_loop_index_ >= event_loops_.size()) {
    last_event_loop_index_ = 0;
  }
  return event_loop;
}

void ThreadPool::thread_func(size_t event_loop_index) {
  while (!stop_) {
    event_loops_[event_loop_index]->run();
  }
}
