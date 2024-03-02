#ifndef MKITS_INCLUDE_MCPPKITS_MCPPKITS_ASYNC_LOG_H_
#define MKITS_INCLUDE_MCPPKITS_MCPPKITS_ASYNC_LOG_H_

#include <condition_variable>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "mckits/core/mckits_mlog.h"
#include "mcppkits/core/queue/mcppkits_list_queue.h"

#define LOGT(...)                                                      \
  mcppkits::AsyncLog::log(MKITS_LOG_LEVEL_VERBOSE, __FILE__, __LINE__, \
                          __VA_ARGS__)
#define LOGV(...)                                                      \
  mcppkits::AsyncLog::log(MKITS_LOG_LEVEL_VERBOSE, __FILE__, __LINE__, \
                          __VA_ARGS__)
#define LOGD(...)                                                    \
  mcppkits::AsyncLog::log(MKITS_LOG_LEVEL_DEBUG, __FILE__, __LINE__, \
                          __VA_ARGS__)
#define LOGI(...) \
  mcppkits::AsyncLog::log(MKITS_LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define LOGW(...)                                                      \
  mcppkits::AsyncLog::log(MKITS_LOG_LEVEL_WARNING, __FILE__, __LINE__, \
                          __VA_ARGS__)
#define LOGE(...)                                                    \
  mcppkits::AsyncLog::log(MKITS_LOG_LEVEL_ERROR, __FILE__, __LINE__, \
                          __VA_ARGS__)
#define LOGSE(...)                                                      \
  mcppkits::AsyncLog::log(MKITS_LOG_LEVEL_SYSERROR, __FILE__, __LINE__, \
                          __VA_ARGS__)
#define LOGF(...)                                                    \
  mcppkits::AsyncLog::log(MKITS_LOG_LEVEL_FATAL, __FILE__, __LINE__, \
                          __VA_ARGS__)
#define LOGC(...)                                                       \
  mcppkits::AsyncLog::log(MKITS_LOG_LEVEL_CRITICAL, __FILE__, __LINE__, \
                          __VA_ARGS__)

namespace mcppkits {

class CAsyncLog {
 public:
  static int init(const std::string& log_filename, bool truncate_long_log,
                  int64_t roll_size);

  static void uninit();

  static void log(int log_level, const char* filename, int line,
                  const char* format, ...);

  static void set_log_level(int log_level);

 private:
  CAsyncLog() = delete;
  ~CAsyncLog() = delete;

  CAsyncLog(const CAsyncLog&) = delete;
  CAsyncLog& operator=(const CAsyncLog&) = delete;

  CAsyncLog(CAsyncLog&&) = delete;
  CAsyncLog& operator=(CAsyncLog&&) = delete;

  static void write_thread();

 private:
  static std::unique_ptr<std::thread> write_thread_;
  static std::mutex mtx_write_;
  static std::condition_variable cv_write_;
  static int current_log_level_;
  static bool running_;
  static std::string log_filename_;
  static FILE* log_file_;
  static mcppkits::queue::TListQueue<std::string> mylist;
  static std::string process_pid_;
  static bool truncate_long_log_;
  static int64_t roll_size_;
};

}  // namespace mcppkits

#endif  // MKITS_INCLUDE_MCPPKITS_MCPPKITS_ASYNC_LOG_H_
