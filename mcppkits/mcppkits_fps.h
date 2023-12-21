#ifndef MKITS_MCPPKITS_MCPPKITS_FPS_H_
#define MKITS_MCPPKITS_MCPPKITS_FPS_H_

#include <chrono>
#include <string>

namespace mcppkits {
namespace fps {

class CFPS {
 public:
  CFPS();
  explicit CFPS(const std::string& name);
  virtual ~CFPS() = default;

  /*
  @brief: Call triger() function in loop. It will print fps.
  */
  void triger();

 private:
  std::string name_ = "";
  int count_ = 0;
  int pre_count_ = 0;
  double fps_ = 0.0;
  std::chrono::time_point<std::chrono::steady_clock> pre_time_;
};

}  // namespace fps
}  // namespace mcppkits

#endif
