#ifndef MKITS_MCPPKITS_MCPPKITS_FPS_H_
#define MKITS_MCPPKITS_MCPPKITS_FPS_H_

#include <chrono>
#include <cstdio>
#include <iostream>
#include <string>

namespace mcppkits {
namespace fps {

class CFPS {
 public:
  CFPS() : pre_time_(std::chrono::steady_clock::now()) {}

  explicit CFPS(const std::string &name)
      : name_(name), pre_time_(std::chrono::steady_clock::now()) {}

  virtual ~CFPS() = default;

  /*
  @brief: Call triger() function in loop. It will print fps.
  */
  void triger() {
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

 private:
  int count_ = 0;
  int pre_count_ = 0;
  double fps_ = 0.0;
  std::string name_ = "";
  std::chrono::time_point<std::chrono::steady_clock> pre_time_;
};

}  // namespace fps
}  // namespace mcppkits

#endif
