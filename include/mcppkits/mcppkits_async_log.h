#ifndef MKITS_INCLUDE_MCPPKITS_MCPPKITS_ASYNC_LOG_H_
#define MKITS_INCLUDE_MCPPKITS_MCPPKITS_ASYNC_LOG_H_

#include "mckits/core/mckits_mlog.h"

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

 private:
  static int current_log_level_;
};

}  // namespace mcppkits

#endif  // MKITS_INCLUDE_MCPPKITS_MCPPKITS_ASYNC_LOG_H_