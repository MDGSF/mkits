#include "mcppkits/mcppkits_async_log.h"

#include "mckits/core/mckits_mos.h"
#include "mcppkits/mstl/mcppkits_defer.h"

namespace mcppkits {

std::unique_ptr<std::thread> CAsyncLog::write_thread_;
std::mutex CAsyncLog::mtx_write_;
std::condition_variable CAsyncLog::cv_write_;
int CAsyncLog::current_log_level_ = MKITS_LOG_LEVEL_INFO;
bool CAsyncLog::running_ = false;
std::string CAsyncLog::log_filename_ = "default";
FILE* CAsyncLog::log_file_ = nullptr;
mcppkits::queue::TListQueue<std::string> CAsyncLog::mylist;
std::string CAsyncLog::process_pid_ = "";
bool CAsyncLog::truncate_long_log_ = false;
int64_t CAsyncLog::roll_size_ = 10 * 1024 * 1024;

int CAsyncLog::init(const std::string& log_filename, bool truncate_long_log,
                    int64_t roll_size) {
  log_filename_ = log_filename;
  truncate_long_log_ = truncate_long_log;
  roll_size_ = roll_size;
  process_pid_ = std::to_string(mckits_get_pid());
  write_thread_.reset(new std::thread(write_thread));
  return 0;
}

void CAsyncLog::uninit() {
  cv_write_.notify_one();
  if (write_thread_->joinable()) {
    write_thread_->join();
  }
  if (log_file_ != nullptr) {
    fclose(log_file_);
    log_file_ = nullptr;
  }
}

void CAsyncLog::log(int log_level, const char* filename, int line,
                    const char* format, ...) {
  if (log_level != MKITS_LOG_LEVEL_CRITICAL) {
    if (log_level < current_log_level_) {
      return;
    }
  }
}

void CAsyncLog::set_log_level(int log_level) {
  if (log_level < MKITS_LOG_LEVEL_VERBOSE ||
      log_level > MKITS_LOG_LEVEL_CRITICAL) {
    return;
  }
  current_log_level_ = log_level;
}

void CAsyncLog::write_thread() {
  running_ = true;
  DEFER([]() { running_ = false; });

  while (true) {
  }
}

}  // namespace mcppkits
