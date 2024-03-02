#include "mcppkits/core/mcppkits_mtime.h"

namespace mcppkits {
namespace mtime {

CTimestamp CTimestamp::now() {
  std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds>
      current = std::chrono::time_point_cast<std::chrono::microseconds>(
          std::chrono::system_clock::now());
  int64_t microSeconds = current.time_since_epoch().count();
  CTimestamp time(microSeconds);
  return time;
}

std::string CTimestamp::to_string() const {
  char buf[BUFSIZ] = {0};
  int64_t seconds = micro_seconds_since_epoch_ / kMicroSecondsPerSecond;
  int64_t microseconds = micro_seconds_since_epoch_ % kMicroSecondsPerSecond;
  snprintf(buf, sizeof(buf) - 1, "%lld.%06lld", (long long int)seconds,
           (long long int)microseconds);
  return buf;
}

std::string CTimestamp::to_string2() const {
  time_t seconds =
      static_cast<time_t>(micro_seconds_since_epoch_ / kMicroSecondsPerSecond);
  struct tm *ptm = localtime(&seconds);
  struct tm tm_time = *ptm;

  char buf[BUFSIZ] = {0};
  snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d",
           tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
           tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);

  return buf;
}

std::string CTimestamp::to_string3() const {
  time_t seconds =
      static_cast<time_t>(micro_seconds_since_epoch_ / kMicroSecondsPerSecond);
  struct tm *ptm = localtime(&seconds);
  struct tm tm_time = *ptm;

  int microseconds =
      static_cast<int>(micro_seconds_since_epoch_ % kMicroSecondsPerSecond);

  char buf[BUFSIZ] = {0};
  snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d",
           tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
           tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec, microseconds);

  return buf;
}

}  // namespace mtime
}  // namespace mcppkits
