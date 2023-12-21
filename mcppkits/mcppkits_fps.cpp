#include "mcppkits_fps.h"

#include <stdio.h>

namespace mcppkits {
namespace fps {

CFPS::CFPS() { pre_time_ = std::chrono::steady_clock::now(); }

CFPS::CFPS(const std::string &name) : name_(name) {
  pre_time_ = std::chrono::steady_clock::now();
}

void CFPS::triger() {
  ++count_;

  auto cur_time = std::chrono::steady_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                     cur_time - pre_time_)
                     .count();
  if (elapsed > 500) {
    fps_ = (count_ - pre_count_) * 1e3 / elapsed;
    pre_time_ = cur_time;
    pre_count_ = count_;
  }

  fprintf(stderr, "[%s] fps = %.2lf", name_.c_str(), fps_);
}

}  // namespace fps
}  // namespace mcppkits
