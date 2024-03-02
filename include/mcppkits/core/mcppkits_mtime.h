#ifndef MKITS_INCLUDE_MCPPKITS_CORE_MCPPKITS_MTIME_H_
#define MKITS_INCLUDE_MCPPKITS_CORE_MCPPKITS_MTIME_H_

#include <chrono>
#include <cstdint>
#include <string>

namespace mcppkits {
namespace mtime {

class CTimestamp {
 public:
  CTimestamp() = default;
  ~CTimestamp() = default;

  CTimestamp(const CTimestamp&) = default;
  CTimestamp& operator=(const CTimestamp&) = default;

  CTimestamp(CTimestamp&&) = default;
  CTimestamp& operator=(CTimestamp&&) = default;

  /*
  @brief: Construct Timestamp with micro seconds.
  */
  explicit CTimestamp(int64_t micro_seconds_since_epoch)
      : micro_seconds_since_epoch_(micro_seconds_since_epoch) {}

  CTimestamp& operator+=(CTimestamp rhs) {
    this->micro_seconds_since_epoch_ += rhs.micro_seconds_since_epoch_;
    return *this;
  }

  CTimestamp& operator+=(int64_t rhs) {
    this->micro_seconds_since_epoch_ += rhs;
    return *this;
  }

  CTimestamp& operator-=(CTimestamp rhs) {
    this->micro_seconds_since_epoch_ -= rhs.micro_seconds_since_epoch_;
    return *this;
  }

  CTimestamp& operator-=(int64_t rhs) {
    this->micro_seconds_since_epoch_ -= rhs;
    return *this;
  }

  /*
  @brief: Get current timestamp.
  */
  static CTimestamp now();

  /*
  @brief: Get format time string.
    "<seconds>.<microseconds>".
  */
  std::string to_string() const;

  /*
  @brief: Get format time string.
    "<year><month><day> <hour>:<minute>:<second>",
    "20240302 21:21:21"
  */
  std::string to_string2() const;

  /*
  @brief: Get format time string.
    "<year><month><day> <hour>:<minute>:<second>.<microseconds>",
    "20240302 21:21:21.012345"
  */
  std::string to_string3() const;

  inline int64_t seconds_since_epoch() const noexcept {
    return micro_seconds_since_epoch_ / kMicroSecondsPerSecond;
  }

  inline int64_t milli_seconds_since_epoch() const noexcept {
    return micro_seconds_since_epoch_ / kMilliSecondsPerSecond;
  }

  inline int64_t micro_seconds_since_epoch() const noexcept {
    return micro_seconds_since_epoch_;
  }

  static const int kMicroSecondsPerSecond = 1000 * 1000;
  static const int kMilliSecondsPerSecond = 1000;

 private:
  int64_t micro_seconds_since_epoch_ = 0;
};

inline bool operator<(CTimestamp lhs, CTimestamp rhs) {
  return lhs.micro_seconds_since_epoch() < rhs.micro_seconds_since_epoch();
}
inline bool operator>(CTimestamp lhs, CTimestamp rhs) { return rhs < lhs; }
inline bool operator<=(CTimestamp lhs, CTimestamp rhs) { return !(lhs > rhs); }
inline bool operator>=(CTimestamp lhs, CTimestamp rhs) { return !(lhs < rhs); }
inline bool operator==(CTimestamp lhs, CTimestamp rhs) {
  return lhs.micro_seconds_since_epoch() == rhs.micro_seconds_since_epoch();
}
inline bool operator!=(CTimestamp lhs, CTimestamp rhs) { return !(lhs == rhs); }

/*
@brief: Get time difference of two timestamps. Result in seconds.
@param high[in]: timestamp.
@param low[in]: timestamp.
@return: (high - low) in seconds.
*/
inline double time_difference(CTimestamp high, CTimestamp low) {
  int64_t diff =
      high.micro_seconds_since_epoch() - low.micro_seconds_since_epoch();
  return static_cast<double>(diff) / CTimestamp::kMicroSecondsPerSecond;
}

/*
@brief: Add microseconds to timestamp, and return an new timestamp.
*/
inline CTimestamp add_time(CTimestamp timestamp, int64_t microseconds) {
  return CTimestamp(timestamp.micro_seconds_since_epoch() + microseconds);
}

}  // namespace mtime
}  // namespace mcppkits

#endif  // MKITS_INCLUDE_MCPPKITS_CORE_MCPPKITS_MTIME_H_
