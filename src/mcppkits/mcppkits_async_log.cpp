#include "mcppkits/mcppkits_async_log.h"

namespace mcppkits {

int CAsyncLog::current_log_level_ = MKITS_LOG_LEVEL_INFO;
bool CAsyncLog::running_ = false;
std::string CAsyncLog::log_filename_ = "default";
FILE* CAsyncLog::log_file_ = nullptr;
mcppkits::queue::TListQueue<std::string> CAsyncLog::mylist;
std::string CAsyncLog::process_pid_ = "";

int CAsyncLog::init(const std::string& log_filename) {
  log_filename_ = log_filename;

  return 0;
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

}  // namespace mcppkits
